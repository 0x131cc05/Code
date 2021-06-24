#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 1000010;

int frac[N], inv[N], mod;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int f[N], g[N], h[N];

int calc(int l, int r) {
    return (LL)(r - l + 1) * (l + r) / 2 % mod;
}

int main() {
    int n; cin >> n >> mod, frac[0] = inv[0] = 1;
    int inv2 = (mod + 1) / 2;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod;
    inv[n] = Pow(frac[n], mod - 2);
    for (int i = n - 1; i >= 1; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % mod;
    for (int i = 3; i <= n; i++) 
        f[i] = (LL)frac[i - 1] * (i + 1) % mod * inv2 % mod * (i - 2) % mod;
    for (int i = 1; i <= n; i++) {
        g[i] = f[i];
        g[i] = (g[i] + (LL)h[i - 1] * 2 * frac[i - 1]) % mod;
        // for (int j = 1; j <= i; j++) {
        //     int left = j - 1, right = i - j;
        //     g[i] = (g[i] + (LL)(h[left] + h[right]) * frac[i - 1]) % mod;
        // }
        h[i] = (h[i - 1] + (LL)g[i] * inv[i]) % mod;
    }
    printf("%d\n", g[n]);
    return 0;
}