#include <bits/stdc++.h>
using namespace std;

int dp[18][1 << 17][2][2], num[1 << 17], fuck[1 << 17];

int main() {
    int n, k, res = 0; scanf("%d%d", &n, &k);
    if (n == 1) return printf("%d\n", k > 0), 0;
    for (int i = 1; i <= k; i++) scanf("%d", &num[i]), num[i]--;
    sort(num + 1, num + k + 1);
    for (int i = 1; i <= k; i++) {
        if (num[i] / 2 != num[i - 1] / 2 || i == 1) res++;
        fuck[num[i] / 2]++;
    }
    memset(dp, -0x3f, sizeof(dp));
    for (int i = 0; i < 1 << n - 1; i++) {
        if (!fuck[i]) dp[1][i][0][0] = 0;
        else if (fuck[i] == 1) dp[1][i][1][0] = dp[1][i][0][1] = 0;
        else dp[1][i][1][1] = 0;
    }
    int all = 1 << n - 1;
    for (int i = 2; i <= n; i++) {
        all /= 2;
        for (int j = 0; j < all; j++) {
            for (int a = 0; a <= 1; a++)
                for (int b = 0; b <= 1; b++)
                    for (int c = 0; c <= 1; c++)
                        for (int d = 0; d <= 1; d++) {
                            int tmp = dp[i - 1][j << 1][a][b] + dp[i - 1][j << 1 | 1][c][d];
                            if (tmp < 0) continue;
                            int A = a + c, B = b + d;
                            dp[i][j][A > 0][B > 0] = max(dp[i][j][A > 0][B > 0], tmp + 2 * (B > 0) + (A > 0));
                            if (A) dp[i][j][A - 1][1] = max(dp[i][j][A - 1][1], tmp + (B > 0) + 2);
                        }
        }
    }
    if (k) res++;
    int t = 0;
    for (int i = 0; i < 4; i++) t = max(t, dp[n][0][i & 1][i >> 1]);
    printf("%d\n", t + res);
}
