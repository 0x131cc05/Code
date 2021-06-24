#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int N = 200010;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N << 2];

int Add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }

void NTT(int a[], int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1)
        for (int i = 0; i < len; i += mid) {
            int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
            for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod) 
                t = (LL)a[j + (mid >> 1)] * w % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
        }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

int init(int n) {
    int len = 1, l = 0;
    while (len <= n * 2) len <<= 1, l++;
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    return len;
}

void Inv(int a[], int b[], int n) {
    if (n == 1) return b[0] = Pow(a[0], mod - 2), void();
    Inv(a, b, (n + 1) >> 1);
    static int tmpA[N << 2], tmpB[N << 2]; 
    for (int i = 0; i < n; i++) tmpA[i] = a[i], tmpB[i] = b[i];
    int len = init(n);
    for (int i = n; i < len; i++) tmpA[i] = tmpB[i] = 0;
    NTT(tmpA, len, 1), NTT(tmpB, len, 1);
    for (int i = 0; i < len; i++) tmpA[i] = (2 - (LL)tmpA[i] * tmpB[i] % mod + mod) * tmpB[i] % mod;
    NTT(tmpA, len, 0);
    for (int i = 0; i < n; i++) b[i] = tmpA[i];
}

int tmp[N << 2], B[N << 2], A[N << 2], frac[N], inv[N], g[N];

int C(int n, int r) {
    if (r < 0 || n < r) return 0;
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int main() {
    int n, m; scanf("%d%d", &n, &m), frac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 1; i <= n; i++) tmp[i - 1] = inv[i];
    Inv(tmp, B, n);
    for (int i = 0; i < n; i++) A[i] = (LL)inv[i + 1] * Pow(m, i + 1) % mod;
    int len = init(n);
    NTT(B, len, 1), NTT(A, len, 1);
    for (int i = 0; i < len; i++) B[i] = (LL)B[i] * A[i] % mod;
    NTT(B, len, 0), memset(A, 0, sizeof(A));
    for (int i = 1; i < n; i++) 
        A[n - i] = (LL)C(n, i + 1) * Pow(m, n - i - 1) % mod * B[i] % mod * frac[i] % mod * frac[i] % mod;
    memset(B, 0, sizeof(B));
    for (int i = 0; i < n; i++) B[i] = i & 1 ? mod - inv[i] : inv[i];
    NTT(A, len, 1), NTT(B, len, 1);
    for (int i = 0; i < len; i++) A[i] = (LL)A[i] * B[i] % mod;
    NTT(A, len, 0);
    for (int i = 1; i < n; i++) g[i] = (LL)A[n - i] * inv[i] % mod;
    for (int i = n - 1; i >= 1; i--) g[i] = (g[i] + g[i + 1]) % mod;
    for (int i = 1; i <= n; i++) printf("%d ", g[i]);
}