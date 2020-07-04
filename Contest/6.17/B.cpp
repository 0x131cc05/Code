#include <bits/stdc++.h>
using namespace std;

const int N = 50010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N << 2];

inline int Sub(int x, int y) {
    return x - y < 0 ? x - y + mod : x - y;
}

inline void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

inline void NTT0(int a[], int len, int type) {
    for (int i = 1; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0; i < len; i += mid) 
            for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod)
                t = (LL)w * a[j + (mid >> 1)] % mod, a[j + (mid >> 1)] = Sub(a[j], t), Inc(a[j], t);
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++) a[i] = (LL)a[i] * inv % mod; 
}

int Wn[2][19][N << 2];

inline void pre(int len) {
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) {
        Wn[1][step][0] = Wn[0][step][0] = 1;
        int a = Pow(3, (mod - 1) / mid), b = Pow(a, mod - 2);
        for (int i = 1; i < (mid >> 1); i++) {
            Wn[1][step][i] = (LL)Wn[1][step][i - 1] * a % mod;
            Wn[0][step][i] = (LL)Wn[0][step][i - 1] * b % mod;
        }
    }
}

inline void NTT1(int a[], int len, int type) {
    for (int i = 1; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) 
        for (int i = 0; i < len; i += mid) 
            for (int j = i, t; j < i + (mid >> 1); j++)
                t = (LL)Wn[type][step][j - i] * a[j + (mid >> 1)] % mod, a[j + (mid >> 1)] = Sub(a[j], t), Inc(a[j], t);
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++) a[i] = (LL)a[i] * inv % mod; 
}

int frac[N], inv[N];

inline int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int n[N * 2], k[N * 2], S[21][21], A[N << 2], B[N << 2], ans[N * 2], fuck;

inline void NTT(int a[], int len, int type) {
    if (fuck) NTT1(a, len, type);
    else NTT0(a, len, type);
}

inline char gc() {
    static char buf[1000000], *p1, *p2;
    if (p1 == p2) p2 = buf + fread(p1 = buf, 1, 1000000, stdin);
    return p1 == p2 ? EOF : *p1++;
}

template<class T> inline void read(T &x) {
    x = 0; char c = gc();
    while (!isdigit(c)) c = gc();
    while (isdigit(c)) x = x * 10 + c - '0', c = gc();
}

inline void print(int x) {
    if (!x) return;
    print(x / 10), putchar(x % 10 + '0');
}

int main() {
    int T, mx = 0, t = 0; read(T);
    for (int i = 1; i <= T; i++) read(n[i]), read(k[i]), t = max(t, n[i]), mx = max(mx, k[i]);
    frac[0] = inv[0] = 1;
    for (int i = 1; i <= t; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    S[0][0] = 1;
    for (int i = 1; i <= mx; i++) 
        for (int j = 1; j <= i; j++)
            S[i][j] = (S[i - 1][j - 1] + (LL)S[i - 1][j] * j) % mod;
    int len = 1, l = 0;
    while (len <= 2 * t) len <<= 1, l++;
    if (mx > 5) fuck = 1, pre(len);
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    for (int i = 0; i <= t; i++) {
        B[i] = (LL)Pow(2, (LL)i * (i - 1) / 2) * inv[i] % mod;
        if (i) A[i] = i <= 2 ? 1 : Pow(i, i - 2); A[i] = (LL)A[i] * inv[i] % mod; 
    }
    NTT(A, len, 1);
    for (int l = 0; l <= mx; l++) {
        for (int i = 1; i <= T; i++) if (k[i] >= l)
            ans[i] = (ans[i] + (LL)S[k[i]][l] * B[n[i]] % mod * frac[n[i]]) % mod;
        NTT(B, len, 1);
        for (int i = 0; i < len; i++) B[i] = (LL)B[i] * A[i] % mod;
        NTT(B, len, 0);
        for (int i = t + 1; i < len; i++) B[i] = 0;
    }
    for (int i = 1; i <= T; i++) print(ans[i]), puts("");
}
