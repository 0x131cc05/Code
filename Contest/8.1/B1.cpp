#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int k, n, frac[65], inv[65];

int A(int n, int r) {
    assert(r <= n && r >= 0);
    return (LL)frac[n] * inv[n - r] % mod;
}

int dp[65][65];

int main() {
    int T; scanf("%d", &T), frac[0] = inv[0] = 1;
    for (int i = 1; i <= 60; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    while (T--) {
        memset(dp, 0, sizeof(dp)); int n, k; scanf("%d%d", &n, &k);
        for (int i = 1; i <= k; i++) dp[0][i] = n < i ? A(k, n) : A(k, i);
        for (int t = 0; t < k; t++)
            for (int s = 1; s <= k; s++) if (dp[t][s])
                for (int j = 1; t + j <= k; j++) {
                    if (t + j == k) {
                        if (j < s) continue;
                    } else if (k - t - j < s) continue;
                    int res = mod - dp[t][s];
                    if (n < s) {
                        dp[t + j][s] = (dp[t + j][s] + res) % mod;
                        continue;
                    }
                    int l = t + s + 1, r = l + j - 1, tmp = floor((n - r) / (double)k);
                    int w = t + j == k ? frac[r - l + 1] : A(k - s - (l - s - 1), r - l + 1);
                    if (tmp >= 0) res = (LL)res * w % mod * Pow(frac[r - l + 1], tmp) % mod;
                    if (l + (tmp + 1) * k <= n) {
                        int remain = n - l - (tmp + 1) * k + 1;
                        if (tmp < 0) res = (LL)res * (t + j == k ? A(r - l + 1, remain) : A(k - s - (l - s - 1), remain)) % mod;
                        else res = (LL)res * A(r - l + 1, remain) % mod;
                    }
                    dp[t + j][s] = (dp[t + j][s] + res) % mod;
                }
        int res = 0;
        for (int i = 1; i <= k; i++) res = (res + dp[k][i]) % mod;
        printf("%d\n", mod - res);
        
    }
}
