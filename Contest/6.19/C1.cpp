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

int r[N << 2];

inline void Inc(int &x, int y) { x += y, x -= x >= mod ? mod : 0; }

inline int Sub(int x, int y) { return x - y < 0 ? x - y + mod : x - y; }

inline void NTT(int a[], int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0; i < len; i += mid)
            for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod) 
                t = (LL)a[j + (mid >> 1)] * w % mod, a[j + (mid >> 1)] = Sub(a[j], t), Inc(a[j], t);
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++) a[i] = (LL)a[i] * inv % mod;
}

int frac[N], inv[N];

inline int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int A[N << 2], B[N << 2];

int main() {
    int n, m; scanf("%d%d", &n, &m), frac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    int len1 = (n - 1) / m + 1, len2 = len1 - 1, a = (n - 1) % m + 1, b = (n - len1 * a) / len2;
    int len = 1, l = 0;
    while (len <= n * 2) len <<= 1, l++;
    for (int i = 1; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    for (int i = 0; i <= len1 / 2; i++) A[i] = C(len1 - i, i);
    for (int i = 0; i <= len2 / 2; i++) B[i] = C(len2 - i, i);
    NTT(A, len, 1), NTT(B, len, 1);
    for (int i = 0; i < len; i++) A[i] = (LL)Pow(A[i], 2 * a) * Pow(B[i], 2 * b) % mod;
    NTT(A, len, 0);
    for (int i = 0; i <= n; i++) A[i] = (LL)A[i] * frac[n - i] % mod;
    memset(B, 0, sizeof(B));
    for (int i = n + 1; i < len; i++) A[i] = 0;
    for (int i = 0; i <= n; i++) A[i] = (LL)A[i] * frac[i] % mod;
    for (int i = 0; i <= n; i++) {
        B[n - i] = inv[i];
        if (i & 1) B[n - i] = mod - B[n - i];
    }
    NTT(A, len, 1), NTT(B, len, 1);
    for (int i = 0; i < len; i++) A[i] = (LL)A[i] * B[i] % mod;
    NTT(A, len, 0);
    for (int i = 0; i <= n; i++) printf("%d\n", (LL)A[n + i] * inv[i] % mod);
}

