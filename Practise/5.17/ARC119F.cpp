#include <bits/stdc++.h>
using namespace std;

const int N = 4010;
const int mod = 1e9 + 7;

char s[N];

int dp[2][2][3][N], g[2][2][4][N];

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int main() {
    int n, k; scanf("%d%d%s", &n, &k, s + 1);
    if (s[1] != 'A') dp[0][0][2][0] = 1;
    if (s[1] != 'B') dp[0][1][2][0] = 1;
    int cur = 0;
    for (int i = 1; i < n; i++) {
        cur ^= 1, memset(dp[cur], 0, sizeof(dp[cur])), memset(g[cur], 0, sizeof(g[cur]));
        for (int t = 0; t <= 1; t++) if (s[i] != 'A' + t)
            for (int d = 0; d <= 3; d++)
                for (int j = 0; j <= k + 1; j++) {
                    Inc(g[cur][t][min(3, d + 1)][j], g[cur ^ 1][t][d][j]);
                } 
        for (int t = 0; t <= 1; t++) 
            for (int d = 0; d <= 2; d++)
                for (int j = 0; j <= k + 1; j++) if (dp[cur ^ 1][t][d][j]){
                    int d1 = d - 1;
                    Inc(g[cur][t][d1 + 1][j], dp[cur ^ 1][t][d][j]);
                }
        for (int t = 0; t <= 1; t++) if (s[i + 1] != 'A' + (t ^ 1)) 
            for (int d = 0; d <= 3; d++)
                for (int j = 0; j <= k + 1; j++) {
                    int d1 = d - 1, d2 = min(d1 + 1, 1);
                    Inc(dp[cur][t ^ 1][d2 - d1 + 1][j + d1], g[cur][t][d][j]);
                }
    }
    int res = 0;
    for (int t = 0; t <= 1; t++)
        for (int d = 0; d <= 2; d++) {
            int tmp = k - (d - 1);
            for (int l = 0; l <= tmp; l++)
                Inc(res, dp[cur][t][d][l]);
        }
    printf("%d\n", res);
}