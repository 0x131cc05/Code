#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int N = 50010;
const int SZ = 700;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N << 2];

void NTT(int a[], int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0; i < len; i += mid)
            for (int j = i, w = 1, t = 0; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod) 
                t = (LL)w * a[j + (mid >> 1)] % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

int a[N], inv[N], f[N], A[N << 2], B[N / SZ + 1][N << 2];

int main() {
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), A[n - i] = a[i];
    for (int i = 1; i <= n + 3; i++) inv[i] = Pow(i, mod - 2);
    for (int i = 0; i <= n; i++) f[i] = (LL)(i + 1) * inv[i + 2] % mod * inv[i + 3] % mod;
    int len = 1, l = 0;
    while (len <= n * 2) len <<= 1, l++;
    for (int i = 0; i < len; i++) r[i] = r[i >> 1] >> 1 | ((i & 1) << l - 1);
    NTT(A, len, 1);
    for (int l = 0, r = SZ - 1, id = 1; r <= n; l += SZ, r += SZ, id++) {
        for (int i = l; i <= r; i++) B[id][i] = f[i];
        NTT(B[id], len, 1);
        for (int i = 0; i < len; i++) B[id][i] = (LL)B[id][i] * A[i] % mod;
        NTT(B[id], len, 0);
    }
    while (q--) {
        int l, r, t, wkr, res = 0; 
        scanf("%d%d", &l, &r), t = r - l, wkr = (t + 1) / SZ;
        for (int i = 1; i <= wkr; i++) 
            res = (res + B[i][n - l]) % mod;
        for (int i = wkr * SZ; i <= t; i++) 
            res = (res + (LL)f[i] * a[i + l]) % mod;
        printf("%d\n", (LL)res * (r - l + 2) % mod * (r - l + 3) % mod);
    }
}