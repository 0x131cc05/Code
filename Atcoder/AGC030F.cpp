#include <bits/stdc++.h>
using namespace std;

const int N = 610;
const int mod = 1e9 + 7;

typedef long long LL;

int num[N], vis[N], dp[N][N][N];

int main() {
    int n, ct = 0; scanf("%d", &n), n *= 2;
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    for (int i = 1; i <= n; i += 2) {
        int A = num[i] != -1, B = num[i + 1] != -1;
        if (A && B) vis[num[i]] = vis[num[i + 1]] = 2;
        else if (A || B) vis[num[i] + num[i + 1] + 1] = 1;
        else ct++;
    } 
    int tp = n + 1; dp[tp][0][0] = 1;
    for (int i = n; i >= 1; i--) if (vis[i] != 2) {
        tp--; int remain = n - tp;
        for (int j = 0; j <= remain; j++)
            for (int k = 0; j + k <= remain; k++) if (dp[tp + 1][j][k]) {
                if (!vis[i]) {
                    dp[tp][j + 1][k] = (dp[tp][j + 1][k] + dp[tp + 1][j][k]) % mod;
                    if (j) dp[tp][j - 1][k] = (dp[tp][j - 1][k] + dp[tp + 1][j][k]) % mod;
                    if (k) dp[tp][j][k - 1] = (dp[tp][j][k - 1] + (LL)dp[tp + 1][j][k] * k) % mod;
                } else {
                    dp[tp][j][k + 1] = (dp[tp][j][k + 1] + dp[tp + 1][j][k]) % mod;
                    if (j) dp[tp][j - 1][k] = (dp[tp][j - 1][k] + dp[tp + 1][j][k]) % mod;
                }
            }
    }
    int res = dp[tp][0][0];
    for (int i = 1; i <= ct; i++) res = (LL)res * i % mod;
    printf("%d\n", res);
}
