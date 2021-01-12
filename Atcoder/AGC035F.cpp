#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int frac[N], inv[N];

inline int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    if (n > m) swap(n, m);
    frac[0] = inv[0] = 1;
    for (int i = 1; i <= m; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    int res = 0;
    for (int i = 0; i <= n; i++) {
        int w = (LL)C(n, i) * C(m, i) % mod * frac[i] % mod * Pow(m + 1, n - i) % mod * Pow(n + 1, m - i) % mod;
        if (i & 1) res = (res + mod - w) % mod;
        else res = (res + w) % mod;
    }
    printf("%d\n", res);
}