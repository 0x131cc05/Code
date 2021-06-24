#include <bits/stdc++.h>
using namespace std;

const int N = 90;

typedef long long LL;

int C[N][N];

int dp[N][N];

int main() {
    int mod; scanf("%d", &mod);
    for (int i = 0; i <= N - 10; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) 
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    dp[0][0] = 1;
    for (int i = 1; i <= N - 10; i++) 
        for (int j = 1; j <= i; j++) 
            for (int k = 0; k <= (j - 1) * (j - 1) && k <= N - 10; k++) if (dp[j - 1][k])
                for (int l = 0; l <= (i - j) * (i - j) && k + l + min(j, i - j + 1) <= N - 10; l++) if (dp[i - j][l])  
                    dp[i][k + l + min(j, i - j + 1)] = (dp[i][k + l + min(j, i - j + 1)] + (LL)dp[j - 1][k] * dp[i - j][l] % mod * C[i - 1][j - 1]) % mod;
    int n, x; 
    while (~scanf("%d%d", &n, &x)) {
        if (x > n * n) puts("0");
        else printf("%d\n", dp[n][x]);
    }
}
