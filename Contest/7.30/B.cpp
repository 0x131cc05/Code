#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N << 2];

int getlen(int n) {
    int len = 1, l = 0;
    while (len <= n) len <<= 1, l++;
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    return len;
}

int Wn[2][18][N << 1];

void getwn(int len) {
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) {
        int w0 = Pow(3, (mod - 1) / mid), w1 = Pow(3, mod - 1 - (mod - 1) / mid);
        Wn[1][step][0] = Wn[0][step][0] = 1;
        for (int i = 1; i < (mid >> 1); i++) {
            Wn[1][step][i] = (LL)Wn[1][step][i - 1] * w0 % mod;
            Wn[0][step][i] = (LL)Wn[0][step][i - 1] * w1 % mod;
        } 
    }
}

void NTT(int a[], int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) 
        for (int i = 0; i < len; i += mid)
            for (int j = i, t; j < i + (mid >> 1); j++)
                t = (LL)Wn[type][step][j - i] * a[j + (mid >> 1)] % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
    if (!type) for (int inv = Pow(len, mod - 2), i = 0; i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

void Mul(int A[], int B[], int n) {
    int len = getlen(n);
    NTT(A, len, 1), NTT(B, len, 1);
    for (int i = 0; i < len; i++) A[i] = (LL)A[i] * B[i] % mod;
    NTT(A, len, 0);
}

int frac[N], inv[N];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

void Shift(int A[], int n) {
    static int B[N << 1]; memset(B, 0, sizeof(B));
    for (int i = 0; i <= n; i++) A[i] = (LL)A[i] * frac[i] % mod;
    for (int i = 0; i <= n; i++) 
        B[n - i] = i & 1 ? mod - inv[i] : inv[i];
    Mul(A, B, n * 2);
    for (int i = 0; i <= n; i++) A[i] = (LL)A[n + i] * inv[i] % mod;
}

int a[N], b[N];

int main() {
    freopen("test1.in", "r", stdin), freopen("out.out", "w", stdout);
    int n, mx = 0; scanf("%d", &n), frac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]), a[i]++, mx = max(mx, a[i]);
    for (int i = 1; i <= n; i++) a[i] += b[i], b[i] = mx - (a[i] - b[i]);
    for (int i = 1; i <= n * 2; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    int len = 1;
    while (len <= n * 4) len <<= 1;
    getwn(len);
    int step = 1500;
    static int wkr[N << 2]; memset(wkr, 0, sizeof(wkr));
    for (int l = 0; l <= n * 2; l += step) {
        int r = l + step - 1;
        static int A[N << 1]; memset(A, 0, sizeof(A));
        bool flag = false;
        for (int i = 1; i <= n; i++) if (l <= a[i] && a[i] <= r) {
            int t = a[i] - l; flag = true;
            for (int j = 0; j <= t; j++) 
                A[j + b[i]] = (A[j + b[i]] + C(t, j)) % mod;
        }
        if (!flag) continue;
        static int B[N << 1]; memset(B, 0, sizeof(B));
        for (int i = 0; i <= l; i++) B[i] = C(l, i);
        Mul(A, B, n * 2);
        for (int i = mx; i <= n + mx; i++) wkr[i - mx] = (wkr[i - mx] + A[i]) % mod;
    }
    Shift(wkr, n);
    for (int i = 0; i < n; i++) printf("%d ", wkr[i]);
}
