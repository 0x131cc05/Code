#include <bits/stdc++.h>
using namespace std;

const int N = 20000010;
const int mod = 998244353;

typedef long long LL;

int inv[N], f[N], pre[N];

int main() {
    int n, k, a, b; scanf("%d%d%d%d", &n, &k, &a, &b), inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (LL)inv[mod % i] * (mod - mod / i) % mod;
    f[1] = k, f[2] = ((LL)a * k + (LL)b * f[1] % mod * f[1]) % mod, pre[1] = (LL)f[1] * f[1] % mod, pre[2] = ((LL)f[1] * f[1] + (LL)f[2] * f[2]) % mod;
    int hh = (a + (LL)2 * k * b) % mod;
    for (int i = 2; i < n; i++) {
        LL tmp = ((LL)(2 * i - 1) * hh % mod * f[i] - (LL)a * a % mod * (i - 2) % mod * f[i - 1]) % mod;
        f[i + 1] = (LL)tmp * inv[i + 1] % mod, pre[i + 1] = (pre[i] + (LL)f[i + 1] * f[i + 1]) % mod;
    }
    int q; scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%d\n", (pre[r] - pre[l - 1] + mod) % mod);
    }
}