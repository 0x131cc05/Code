#include <bits/stdc++.h>
using namespace std;

const int N = 210;

int mod;

typedef long long LL;

int C[N][N], dp[N][N], sum[N];

int main() {
    int n, d, type; scanf("%d%d%d%d", &n, &d, &mod, &type);
    if (type == 0) {
        if (d >= 2) printf("%d\n", 1 % mod);
        else if (n <= 2) printf("%d\n", 1 % mod);
        else puts("0");
        return 0;
    }
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = ((LL)C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    dp[1][0] = 1, sum[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= d; j++) {
            for (int k = 1; k < i; k++)
                dp[i][j] = (dp[i][j] + (LL)sum[k] * dp[i - k][j - 1] % mod * C[i - 2][k - 1]) % mod;
        }
        for (int k = 0; k < d; k++)
            sum[i] = ((LL)sum[i] + dp[i][k]) % mod;
    }
    int res = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= d; j++)
            for (int k = 0; j + k <= d; k++)
                res = (res + (LL)dp[i][j] * dp[n - i + 1][k]) % mod;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < d; j++)
            for (int k = 0; k < d; k++)
                res = (res - (LL)dp[i][j] * dp[n - i][k] % mod + mod) % mod;
    printf("%d\n", res);
}
