#include <bits/stdc++.h>
using namespace std;

const int N = 30010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int Wn[2][17][N << 1], r[N << 2];

inline void Inc(int &x, int y) { x += y, x -= x >= mod ? mod : 0; }
inline int Sub(int x, int y) { int t = x - y; return t < 0 ? t + mod : t; }

inline void Pre(int len) {
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) {
        int t1 = Pow(3, (mod - 1) / mid), t2 = Pow(t1, mod - 2);
        Wn[0][step][0] = Wn[1][step][0] = 1, Wn[1][step][1] = t1, Wn[0][step][1] = t2;
        for (int i = 2; i < (mid >> 1); i++) {
            Wn[1][step][i] = (LL)Wn[1][step][i - 1] * t1 % mod;
            Wn[0][step][i] = (LL)Wn[0][step][i - 1] * t2 % mod;
        }
    }
}

inline void NTT(vector<int> &a, int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++) {
                int t = (LL)Wn[type][step][j - i] * a[j + (mid >> 1)] % mod;
                a[j + (mid >> 1)] = Sub(a[j], t), Inc(a[j], t);
            }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

inline void GetR(int len, int l) {
    for (int i = 1; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
}

int n, m;

inline vector<int> mul(vector<int> a, vector<int> b) { 
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

int inv[N];

inline vector<int> Ln(const vector<int> &a, int n) {
    vector<int> a1, inva = Inv(a, n);
    for (int i = 1; i < n && i < a.size(); i++) a1.push_back((LL)a[i] * i % mod);
    a1 = mul(a1, inva), a1.resize(n);
    for (int i = n - 1; i >= 1; i--) a1[i] = (LL)a1[i - 1] * inv[i] % mod, assert(inv[i]);
    return a1[0] = 0, a1;
}

vector<int> Exp(const vector<int> &a, int n) {
    if (n == 1) return {1};
    vector<int> tmp = Exp(a, (n + 1) / 2), ln = Ln(tmp, n), tmp1;
    for (int i = 0; i < n; i++) tmp1.push_back((a[i] - ln[i] + mod) % mod);
    tmp1[0]++, tmp = mul(tmp, tmp1), tmp.resize(n);
    return tmp;
}

int a[N];

vector<int> solve(int l, int r) {
    if (l == r) return {1, mod - a[l]};
    int mid = (l + r) >> 1; 
    return mul(solve(l, mid), solve(mid + 1, r));
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    int len = 1; inv[1] = 1;
    while (len <= 2 * (n + 1)) len <<= 1;
    for (int i = 2; i <= n; i++) inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
    Pre(len); vector<int> tmp = Ln(solve(1, n), n + 1);
    for (int i = 1; i <= n; i++) tmp[i] = mod - (LL)tmp[i] * i % mod;
    tmp[0] = n;
    vector<int> A(n + 1), B(n + 1);
    for (int i = 0, f = 1; i <= n; i++, f = (LL)f * inv[i] % mod) {
        A[i] = (LL)Pow(i + 1, 2 * m) * f % mod;
        B[i] = (LL)Pow(i + 1, m) * f % mod;
    }
    vector<int> lnB = Ln(B, n + 1), invb = Inv(B, n + 1), T = mul(A, invb);
    for (int i = 0; i <= n; i++) {
        lnB[i] = (LL)lnB[i] * tmp[i] % mod;
        T[i] = (LL)T[i] * tmp[i] % mod;
    }
    vector<int> F = mul(Exp(lnB, n + 1), T);
    int res = F[n - 2];
    for (int i = 1; i <= n - 2; i++) res = (LL)res * i % mod;
    for (int i = 1; i <= n; i++) res = (LL)res * a[i] % mod;
    printf("%d\n", res);
    return 0; 
}