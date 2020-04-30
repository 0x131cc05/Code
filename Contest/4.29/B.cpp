#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, LL y) {
    if (x < 0) x += mod;
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N << 2];

inline void NTT(int a[], int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0; i < len; i += mid)
            for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod) 
                t = (LL)a[j + (mid >> 1)] * w % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++) 
        a[i] = (LL)a[i] * inv % mod;
}

int frac[N], inv[N], A[N << 2], B[N << 2], D[N << 2], inv2[N]; LL q;

inline int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

inline int GetG(int n, int G[]) {
    int len = 1, l = 0;
    while (len <= n * 2) len <<= 1, l++;
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    for (int i = 0; i < len; i++) A[i] = B[i] = 0;
    for (int i = 0; i <= n; i++) {
        A[i] = (LL)Pow(n - 2 * i, q) * inv[i] % mod;
        if (i & 1) A[i] = mod - A[i];  
    }
    for (int i = 0; i <= n; i++) B[i] = inv[i];
    NTT(A, len, 1), NTT(B, len, 1);
    for (int i = 0; i < len; i++) A[i] = (LL)A[i] * B[i] % mod;
    NTT(A, len, 0);
    for (int i = 0; i <= n; i++) A[i] = (LL)A[i] * inv2[i] % mod * frac[i] % mod * C(n, i) % mod;
    for (int i = 0; i <= len; i++) B[i] = D[i] = 0;
    for (int i = 0; i <= n; i++) {
        B[i] = inv[i], D[n - i] = (LL)A[i] * frac[i] % mod;
        if (i & 1) B[i] = mod - B[i];
    }
    NTT(B, len, 1), NTT(D, len, 1);
    for (int i = 0; i < len; i++) B[i] = (LL)B[i] * D[i] % mod;
    NTT(B, len, 0);
    for (int i = 0; i <= n; i++) G[i] = (LL)inv[i] * B[n - i] % mod, cout << G[i] << ' ';
    cout << endl;
    
} 

int F[N], G[N], sum[N];

int main() {
    int n, m; LL k; scanf("%d%d%lld%lld", &n, &m, &q, &k), q %= (mod - 1);
    frac[0] = inv[0] = inv2[0] = 1; int t = max(n, m);
    for (int i = 1; i <= t; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv2[i] = (LL)inv2[i - 1] * (mod + 1) / 2 % mod;
    inv[t] = Pow(frac[t], mod - 2);
    for (int i = t - 1; i >= 1; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % mod;
    GetG(n, F), GetG(m, G);
    for (int i = 0; i <= m; i++) 
        sum[i] = (sum[max(0, i - 1)] + G[i]) % mod;
    int res = 0;
    for (int i = 0; i <= n; i++) {
        LL tmp = k - (LL)i * m; int t = 0;
        if (i * 2 == n) {
            if (tmp >= 0) t = (t + sum[m]) % mod;
        } else if (n - 2 * i > 0) {
            if (tmp < 0) continue;
            LL pos = min((LL)m, tmp / (n - 2 * i));
            if (pos >= 0) t = (t + sum[pos]) % mod;
        } else {
            LL pos = max(0ll, (-tmp + i * 2 - n - 1) / (i * 2 - n));
            if (pos <= m) {
               t = (t + sum[m]) % mod;
                if (pos >= 1) t = (t + mod - sum[pos - 1]) % mod; 
            }
        }
        res = (res + (LL)t * F[i]) % mod;
    }
    printf("%d\n", (res + mod) % mod);
}
