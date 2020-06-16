#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
const int mod = 998244353;

typedef long long LL;

int f[N << 1], g[N << 1];

int frac[N], inv[N];

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int r[N << 1];

inline void NTT(int a[], int len, int type) {
    for (int i = 1; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid); 
        for (int i = 0; i < len; i += mid)
            for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod)
                t = (LL)a[j + (mid >> 1)] * w % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
    } 
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

int main() {
    int n; scanf("%d", &n), frac[0] = inv[0] = 1;
    for (int i = 1; i <= n * 2; i++) 
        frac[i] = (LL)frac[i - 1] * i % mod;
    inv[n * 2] = Pow(frac[n * 2], mod - 2);
    for (int i = n * 2 - 1; i >= 1; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % mod;
    for (int i = 1; i <= n; i++) 
        f[i] = (LL)C(n + i - 1, i * 2 - 1) * Pow(n, i == 1 ? mod - 2 : i - 2) % mod;
    for (int i = 1; i <= n; i++) f[i] = (LL)f[i] * frac[n - i] % mod;
    for (int i = 0; i <= n; i++) g[i] = i & 1 ? mod - inv[i] : inv[i];
    int len = 1, l = 0;
    while (len <= n * 2) len <<= 1, l++;
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    NTT(f, len, 1), NTT(g, len, 1);
    for (int i = 0; i < len; i++) f[i] = (LL)f[i] * g[i] % mod;
    NTT(f, len, 0);
    for (int i = 1; i <= n; i++) f[i] = (LL)f[i] * inv[n - i] % mod;
    int res = 0;
    for (int i = 1, pw = 1; i < n; i++) {
        pw = pw * 2 % mod;
        res = (res + (LL)pw * f[n - i] % mod * i) % mod;
    }
    printf("%d\n", res);
} 
