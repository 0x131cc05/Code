#include <bits/stdc++.h>
using namespace std;

int dp[11][50], C[51][51];

typedef long long LL;

const int mod = 1e9 + 7;

int main() {
    int n; scanf("%d", &n);
    dp[1][0] = 1;
    for (int i = 0; i <= 50; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    for (int i = 2; i <= n; i++) 
        for (int j = 0; j <= i * (i - 1) / 2; j++) {
            dp[i][j] = C[i * (i - 1) / 2][j];
            for (int k = 1; k < i; k++) {
                for (int l = 0; l <= j; l++) if (dp[k][l]) {
                    int w = (LL)C[i - 1][k - 1] * dp[k][l] % mod * C[(i - k) * (i - k - 1) / 2][j - l] % mod;
                    dp[i][j] = (dp[i][j] - w + mod) % mod;
                }
            }
        }
    for (int i = 1; i <= n; i++, puts(""))
        for (int j = 0; j <= i * (i - 1) / 2; j++)
            printf("%d, ", dp[i][j]); 
} 
