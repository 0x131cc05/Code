#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 250010, mod = 998244353;
inline int Pow(int x, int y) {
    int res = 1;
    for (;y;y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}
int r[N * 4];
inline void NTT(int a[], int len, int type) {
    for (int i = 1;i < len;i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2;mid <= len;mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0;i < len;i += mid)
            for (int j = i, t, w = 1;j < i + (mid >> 1);j++, w = (LL)w * Wn % mod)
                t = (LL)w * a[j + (mid >> 1)] % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2);i < len;i++)
        a[i] = (LL)a[i] * inv % mod;
}
int frac[N], inv[N], A[N * 4], B[N * 4];
int main() { 
    freopen("in1.in", "r", stdin), freopen("in1.out", "w", stdout); 
    int n; LL m; scanf("%d%lld", &n, &m), frac[0] = 1, m %= mod - 1;
    for (int i = 1;i <= n;i++) frac[i] = (LL)frac[i - 1] * i % mod;
    inv[n] = Pow(frac[n], mod - 2);
    for (int i = n - 1;i >= 0;i--) inv[i] = (LL)inv[i + 1] * (i + 1) % mod;
    for (int i = 0;i <= n;i++) scanf("%d", &A[i]), A[i] = (LL)A[i] * frac[i] % mod;
    for (int i = 0;i <= n;i++) B[n - i] = inv[i];
    int len = 1, l = 0;
    while (len <= n * 2) len <<= 1, l++;
    for (int i = 1;i < len;i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    NTT(A, len, 1), NTT(B, len, 1);
    for (int i = 0;i < len;i++) A[i] = (LL)A[i] * B[i] % mod;
    NTT(A, len, 0);
    for (int i = 0;i <= n;i++) A[i] = A[i + n];
    for (int i = n + 1;i < len;i++) A[i] = 0;
    for (int i = 0;i <= n;i++) A[i] = (LL)A[i] % mod * Pow(Pow(i + 1, m), mod - 2) % mod;
    for (int i = n + 1;i < len;i++) B[i] = 0;
    for (int i = 0;i <= n;i++) B[n - i] = i & 1 ? mod - inv[i] : inv[i];
    NTT(A, len, 1), NTT(B, len, 1);
    for (int i = 0;i < len;i++) A[i] = (LL)A[i] * B[i] % mod;
    NTT(A, len, 0);
    for (int i = 0;i <= n;i++) printf("%d ", (LL)A[i + n] * inv[i] % mod);
}
