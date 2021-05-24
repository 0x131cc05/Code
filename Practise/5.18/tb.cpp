#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int dp[N][N * N];

int main() {
    int n, q, c; scanf("%d%d%d", &n, &q, &c);
    memset(dp, -0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        for (int j = 0; j <= 10000; j++) if (dp[i - 1][j] >= 0)
            for (int k = 0; k <= a; k++) {
                if (a - k > dp[i - 1][j]) continue;
                dp[i][j + k] = max(dp[i][j + k], dp[i - 1][j] - (a - k) + k / c);
            }
    }
    int res = 0;
    for (int j = 0; j <= 10000; j++) if (dp[n][j] >= 0) {
        res = j; break;
    }
    printf("%d\n", res);
}
