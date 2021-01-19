#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N << 2];

void Inc(int &x, int y) { x += y, x -= x >= mod ? mod : 0; }
int Sub(int x, int y) { int t = x - y; return t < 0 ? t + mod : t; }

void NTT(vector<int> &a, int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0; i < len; i += mid)
            for (int j = i, w = 1; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod) {
                int t = (LL)w * a[j + (mid >> 1)] % mod;
                a[j + (mid >> 1)] = Sub(a[j], t), Inc(a[j], t);
            }
    }   
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

void GetR(int len, int l) {
    for (int i = 1; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
}

int n, m;

vector<int> mul(vector<int> a, vector<int> b) { 
    int t = a.size() + b.size() - 2, len = 1, l = 0;
    while (len <= t) len <<= 1, l++;
    GetR(len, l), a.resize(len + 1), b.resize(len + 1);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = (LL)a[i] * b[i] % mod;
    NTT(a, len, 0), a.resize(min(n + 1, t + 1));
    return a;
}

vector<int> Inv(const vector<int> &a, int n) {
    if (n == 1) return {Pow(a[0], mod - 2)};
    vector<int> b = Inv(a, (n + 1) / 2);
    int len = 1, l = 0;
    while (len <= n * 2) len <<= 1, l++;
    GetR(len, l), b.resize(len); vector<int> tmp(len);
    for (int i = 0; i < n && i < a.size(); i++) tmp[i] = a[i];
    NTT(tmp, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) b[i] = (2 - (LL)tmp[i] * b[i] % mod + mod) * b[i] % mod;
    NTT(b, len, 0), b.resize(n); 
    return b;
}

int main() {
    int n; scanf("%d", &n);
    vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) {
        if (i % 3 == 1) continue;
        A[i] = i % 6 == 5 || i % 6 == 0 ? mod - 1 : 1;
        A[i] = (LL)A[i] * i % mod * n % mod; 
        A[i] = mod - A[i];
    }
    A[0] = 1;
    vector<int> res = Inv(A, n + 1);
    int inv = Pow(n, mod - 2);
    int ans = (LL)res[n] * inv % mod * inv % mod;
    printf("%d\n", ans);
}
