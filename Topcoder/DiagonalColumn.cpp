#include <bits/stdc++.h>
using namespace std;

const int N = 50;
const int mod = 1e9 + 7;

typedef long long LL;

int pw[N], dp[N][N][N * 2];

// dp[i][j][k] 由第k条对角线以及第i列（包含）围成的区域，其中第j到第i列选择方案不同则视为最终方案不同

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

struct DiagonalColumn {
    int countGrids(int n, int m) {
        pw[0] = 1;
        for (int i = 1; i <= max(n, m); i++) pw[i] = pw[i - 1] * 2 % mod;
        dp[0][1][0] = dp[0][0][0] = 1;
        for (int t = 1; t <= n + m - 1; t++) {
            dp[0][1][t] = 1;
            int tmp = max(1, t - n + 1);
            for (int i = tmp; i <= min(m, t); i++) {
                if (i == t) Inc(dp[i][i + 1][t], dp[i - 1][tmp][t - 1] * 2 % mod);
                else Inc(dp[i][i + 1][t], dp[i][tmp][t - 1]);
                Inc(dp[i][i + 1][t], dp[min(i, t - 1)][min(i, t - 1) + 1][t - 1]);
                dp[i][i + 1][t] = (dp[i][i + 1][t] - dp[tmp - 1][tmp][t - 1] + mod) % mod;
                for (int j = tmp; j <= i; j++) {
                    Inc(dp[i][j][t], dp[j - 1][j][t]);
                    for (int k = j; k <= i; k++) {
                        Inc(dp[i][j][t], (LL)dp[j - 1][j][k - 1] * pw[i - k] % mod);
                        for (int l = k; l <= t; l++) 
                            Inc(dp[i][j][t], (LL)dp[j - 1][max(1, l - n + 1)][k - 1] * pw[i - k] % mod * pw[t - l] % mod);
                    }
                }
            }
        }
        return dp[m][m + 1][n + m - 1];
    }
};

// int main() {
//     DiagonalColumn solver;
//     cout << solver.countGrids(38, 38) << endl;
// }
