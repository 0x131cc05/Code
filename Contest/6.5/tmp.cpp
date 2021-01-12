#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N << 2], wn[2][20][N << 1];

inline void pre(int len) {
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) {
        int a = Pow(3, (mod - 1) / mid), b = Pow(a, mod - 2);
        wn[1][step][0] = wn[0][step][0] = 1;
        for (int i = 1; i < (mid >> 1); i++) {
            wn[1][step][i] = (LL)wn[1][step][i - 1] * a % mod;
            wn[0][step][i] = (LL)wn[0][step][i - 1] * b % mod;
        }
    }
}

inline void GetR(int len, int l) {
    for (int i = 1; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
}

inline int Sub(int a, int b) {
    a -= b; return a < 0 ? a + mod : a;
}

inline void Inc(int &a, int b) {
    a += b, a -= a >= mod ? mod : 0;
}

inline void NTT(vector<int> &a, int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) {
        for (int i = 0; i < len; i += mid)
            for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = wn[type][step][j - i])
                t = (LL)a[j + (mid >> 1)] * w % mod, a[j + (mid >> 1)] = Sub(a[j], t), Inc(a[j], t);
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

int m;

inline vector<int> mul(vector<int> a, vector<int> b) {
    int n = a.size() + b.size() - 2, len = 1, l = 0;
    while (len <= n) len <<= 1, l++;
    GetR(len, l), a.resize(len), b.resize(len);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = (LL)a[i] * b[i] % mod;
    NTT(a, len, 0), a.resize(min(n + 1, m + 1));
    return a;
}

inline vector<int> Pow(vector<int> base, int y) {
    vector<int> res = {1};
    for (; y; y >>= 1, base = mul(base, base)) if (y & 1) res = mul(res, base);
    return res;
}

int frac[N], inv[N];

int main() {
    int n; scanf("%d%d", &n, &m); vector<int> base = {2}; frac[0] = inv[0] = 1;
    int len = 1;
    while (len <= m * 2) len <<= 1;
    pre(len);
    for (int i = 1; i <= m; i++) {
        frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
        base.push_back(inv[i]);
    }
    base = Pow(base, n); int res = 0;
    for (int i = 0; i <= m; i++) {
        int a; scanf("%d", &a);
        res = (res + (LL)a * base[i] % mod * frac[i]) % mod;
    }
    printf("%d\n", res);
}
