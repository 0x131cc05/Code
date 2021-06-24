#include <bits/stdc++.h>
using namespace std;

const int N = 90;
const int mod = 1e9 + 7;

typedef long long LL;

int ct[N], a[6410], dp[2][N][N][N], C[N][N], match[N], frac[N], f[N][N];

int main() {
    int n, mx = 0; scanf("%d", &n);
    for (int i = 1, a; i <= n; i++) scanf("%d", &a), ct[a]++, mx = max(mx, a);
    for (int i = 1; i <= mx; i++) a[ct[i]]++;
    for (int i = 0; i <= N - 10; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    LL fuck = 0;
    for (int i = 1; i <= n; i++) fuck += i * (i + 1) / 2 * a[i];
    printf("%lld ", fuck);
    frac[0] = match[0] = 1;
    for (int i = 1; i <= N - 10; i++) frac[i] = (LL)frac[i - 1] * i % mod;
    for (int i = 2; i <= N - 10; i += 2) 
        match[i] = (LL)match[i - 2] * (i - 1) % mod * 2 % mod;
    dp[0][0][0][0] = 1; int cur = 0;
    for (int i = n; i >= 3; i--) {
        cur ^= 1, memset(dp[cur], 0, sizeof(dp[cur]));
        for (int j = 0; j <= a[i + 1] && j <= a[i]; j++) 
            for (int k = 0; k <= mx; k++) for (int b = 0; b <= k; b++) if (dp[cur ^ 1][j][k][b]) {
                int remain = a[i] - j, w1 = (LL)C[a[i]][j] * dp[cur ^ 1][j][k][b] % mod * frac[j] % mod;
                for (int t = 0; t <= remain; t += 2) {
                    int c = t / 2 + remain - t, w = (LL)w1 * C[remain][t] % mod * match[t] % mod;
                    for (int l = 0; l <= remain - t; l++) 
                        dp[cur][l][c + k][b + remain - t] = (dp[cur][l][c + k][b + remain - t] + (LL)C[remain - t][l] * w) % mod;
                }
            }
    }
    f[0][0] = 1;
    for (int i = 1; i <= mx; i++)
        for (int j = 0; j <= mx; j++) if (f[i - 1][j]) 
            for (int k = 0; k <= mx - j; k++)
                f[i][j + k] = (f[i][j + k] + (LL)f[i - 1][j] * C[j + k][k] % mod * frac[k]) % mod;
    int res = 0;
    for (int i = 0; i <= mx && i <= a[2]; i++)
        for (int j = 0; j <= mx; j++) for (int b = 0; b <= j; b++) if (dp[cur][i][j][b]) {
            int remain = a[2] - i, w1 = (LL)C[a[2]][i] * dp[cur][i][j][b] % mod * frac[i] % mod;
            for (int k = 0; k <= remain; k++) 
                for (int l = 0; k + l <= remain; l += 2) {
                    int c = a[1] + j + l / 2 + k;
                    res = (res + (LL)w1 * C[remain][k] % mod * match[l] % mod * f[b + a[1] + k][remain - l - k] % mod * C[remain - k][l] % mod * frac[c]) % mod;
                }
        }
    printf("%d\n", res);
                
}
