// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 998244353, N = 600010;
inline int Pow(int x, int y) {
    int res = 1;
    for (;y;y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}
int r[N], inv[N];
inline void NTT(int a[], int len, int type) {
    for (int i = 0;i < len;i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2;mid <= len;mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0;i < len;i += mid)
            for (int j = i, w = 1, t;j < i + (mid >> 1);j++, w = (LL)w * Wn % mod)
                t = (LL)w * a[j + (mid >> 1)] % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2);i < len;i++) a[i] = (LL)a[i] * inv % mod;
}
inline void Inv(const int A[], int B[], int n) {
    if (n == 1) return void(B[0] = Pow(A[0], mod - 2));
    Inv(A, B, (n + 1) >> 1); static int tmpa[N]; int len = 1, l = 0;
    while (len <= 2 * n) len <<= 1, l++;
    for (int i = 0;i < len;i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    for (int i = 0;i < n;i++) tmpa[i] = A[i];
    for (int i = n;i < len;i++) tmpa[i] = 0;
    NTT(tmpa, len, 1), NTT(B, len, 1);
    for (int i = 0;i < len;i++) B[i] = (2 - (LL)tmpa[i] * B[i] % mod + mod) * B[i] % mod;
    NTT(B, len, 0);
    for (int i = n;i < len;i++) B[i] = 0;
}
inline void Ln(const int A[], int B[], int n) {
    static int tmpa[N], inva[N]; memset(tmpa, 0, sizeof(tmpa)), memset(inva, 0, sizeof(inva));
    for (int i = 0;i < n;i++) tmpa[i] = (LL)A[i + 1] * (i + 1) % mod;
    Inv(A, inva, n); int len = 1, l = 0;
    while (len <= 2 * n) len <<= 1, l++;
    for (int i = 0;i < len;i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    NTT(tmpa, len, 1), NTT(inva, len, 1);
    for (int i = 0;i < len;i++) tmpa[i] = (LL)tmpa[i] * inva[i] % mod;
    NTT(tmpa, len, 0);
    for (int i = 1;i < n;i++) B[i] = (LL)tmpa[i - 1] * inv[i] % mod;
}
inline void Exp(const int A[], int B[], int n) {
    if (n == 1) return void(B[0] = 1); Exp(A, B, (n + 1) >> 1);
    static int lnb[N]; memset(lnb, 0, sizeof(lnb));
    Ln(B, lnb, n); int len = 1, l = 0;
    for (int i = 0;i < n;i++) lnb[i] = (A[i] - lnb[i] + mod) % mod;
    lnb[0]++;
    while (len <= 2 * n) len <<= 1, l++;
    for (int i = 0;i < len;i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    NTT(B, len, 1), NTT(lnb, len, 1);
    for (int i = 0;i < len;i++) B[i] = (LL)B[i] * lnb[i] % mod;
    NTT(B, len, 0);
    for (int i = n;i < len;i++) B[i] = 0;
}
int A[N], B[N];
int main() {
    int n; scanf("%d", &n), inv[0] = 1;
    for (int i = 1;i <= n;i++) inv[i] = Pow(i, mod - 2);
    for (int i = 0;i < n;i++) scanf("%d", &A[i]);
    Exp(A, B, n);
    for (int i = 0;i < n;i++) printf("%d ", B[i]);
}