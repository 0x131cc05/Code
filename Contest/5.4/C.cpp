#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (;y;y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

const int N = 4000010, inv2 = (mod + 1) / 2;

int r[N];

inline void NTT(int a[], int len, int type) {
    for (int i = 0;i < len;i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2;mid <= len;mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0;i < len;i += mid)
            for (int j = i, w = 1, t;j < i + (mid >> 1);j++, w = (LL)w * Wn % mod)
                t = (LL)a[j + (mid >> 1)] * w % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2);i < len;i++) a[i] = (LL)a[i] * inv % mod;
}

inline void Get(int len, int l) {for (int i = 0;i < len;i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);}

inline void Inv(const int A[], int B[], int n) {
    if (n == 1) return void(B[0] = Pow(A[0], mod - 2));
    Inv(A, B, (n + 1) >> 1); static int tmpa[N]; int len = 1, l = 0;
    while (len <= n * 2) len <<= 1, l++;
    for (int i = 0;i < n;i++) tmpa[i] = A[i];
    fill(tmpa + n, tmpa + len, 0);
    Get(len, l), NTT(tmpa  , len, 1), NTT(B, len, 1);
    for (int i = 0;i < len;i++) B[i] = (2 - (LL)tmpa[i] * B[i] % mod + mod) * B[i] % mod;
    NTT(B, len, 0), fill(B + n, B + len, 0);
}

inline void Sqrt(const int A[], int B[], int n) {
    if (n == 1) return void(B[0] = 1);
    Sqrt(A, B, (n + 1) >> 1); static int tmpa[N], invb[N]; int len = 1, l = 0;
    for (int i = 0;i < n;i++) tmpa[i] = A[i];
    while (len <= n * 2) len <<= 1, l++;
    memset(invb, 0, sizeof(invb));
    Inv(B, invb, n), Get(len, l);
    for (int i = n; i < len; i++) tmpa[i] = 0;
    NTT(tmpa, len, 1), NTT(invb, len, 1);
    for (int i = 0;i < len;i++) tmpa[i] = (LL)tmpa[i] * invb[i] % mod;
    NTT(tmpa, len, 0);
    for (int i = 0;i < n;i++) B[i] = (LL)(B[i] + tmpa[i]) * inv2 % mod;
}

int A[N * 2], B[N * 2], F[N], pre[N];

int main() {
    int n, k, a, b; scanf("%d%d%d%d", &n, &k, &a, &b);
    A[0] = 1, A[1] = (-2 * a - (LL)4 * k * b) % mod, A[1] = (A[1] + mod) % mod, A[2] = (LL)a * a % mod;
    Sqrt(A, B, n + 1);
    int inv = Pow(2 * b % mod, mod - 2);
    for (int i = 1; i <= n; i++) F[i] = mod - B[i];
    F[0]++, F[1] = (F[1] + mod - a) % mod;
    for (int i = 1; i <= n; i++) {
        F[i] = (LL)F[i] * inv % mod;
        pre[i] = (pre[i - 1] + (LL)F[i] * F[i]) % mod;
    }
    int q; scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%d\n", (pre[r] - pre[l - 1] + mod) % mod);
    }

}
