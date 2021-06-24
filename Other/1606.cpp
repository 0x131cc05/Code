#include <bits/stdc++.h>
using namespace std;

const int N = 10000010;

typedef long long LL;

//int dp[N][N];

int f[N], g[N];

int main() {
    int n, mod; cin >> n >> mod;
//    dp[0][0] = 1;
//    for (int i = 1; i <= n / 2; i++)
//        for (int j = 0; j <= (i - 1) * 2; j++) {
//            dp[i][j] = (dp[i][j] + (LL)2 * dp[i - 1][j]) % mod;
//            dp[i][j + 1] = (dp[i][j + 1] + (LL)(mod - 4) * dp[i - 1][j] % mod * (j + 1)) % mod;
//            dp[i][j + 2] = (dp[i][j + 2] + (LL)dp[i - 1][j] * (j + 1) % mod * (j + 2)) % mod;
//        }
//    for (int i = 1; i <= n; i++) {
//        if (i & 1) {
//            for (int j = 0; j <= n; j++) 
//                f[i] = (f[i] + (LL)dp[i / 2][j] * j) % mod;
//        } else for (int j = 0; j <= n; j++) 
//            f[i] = (f[i] + dp[i / 2][j]) % mod;
//    }
    f[0] = 1;
    for (int i = 4; i <= n; i++) { // thanks oeis
        f[i] = (LL)(i - 1) * f[i - 1] % mod;
        if (i & 1) f[i] = (f[i] + (LL)2 * (i - 1) * f[i - 2]) % mod;
        else f[i] = (f[i] + (LL)2 * (i - 2) * f[i - 4]) % mod;
    }
    g[2] = 1;
    for (int i = 3; i <= n; i++)
        g[i] = (LL)(i - 1) * (g[i - 2] + g[i - 1]) % mod;
    int res = 0, all = 1;
    for (int i = 1; i <= n; i++) {
        int delta = g[i] - f[i];
        if (delta < 0) delta += mod;
        all = (LL)all * i % mod;
        int ans = (all - f[i] - (LL)delta * 2) % mod;
        if (ans < 0) ans += mod;
        res ^= ans;
    }   
    cout << res << endl;
}
