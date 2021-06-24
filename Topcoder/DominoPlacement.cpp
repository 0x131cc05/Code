#include <bits/stdc++.h>
using namespace std;

const int N = 310;
const int mod = 1e9 + 7;

int n, m;

int dp[310][1 << 17], G[N][N];

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int DP() {
    int all = (1 << m) - 1, cur = 0;
    dp[0][all] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cur++;
            for (int s = 0; s <= all; s++) {
                int nxt = (s << 1) & all, c = (s >> (m - 1)) & 1;
                if (G[i][j]) {
                    if (c) Inc(dp[cur][nxt | 1], dp[cur - 1][s]);
                    continue;
                }
                if (!c) Inc(dp[cur][nxt | 1], dp[cur - 1][s]);
                for (int k = 1; k <= j; k++) {
                    if (G[i][j - k + 1] || !(s & (1 << (m - k)))) break;
                    Inc(dp[cur][((s << k) & all) | ((1 << k) - 1)], dp[cur - k][s]);
                }
                Inc(dp[cur][nxt], dp[cur - 1][s]);
            }
        }
    return dp[cur][all];
}

struct DominoPlacement {
    int countWays(vector<string> T) {
        int n = T.size(), m = T[0].size();
        int type = n < m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (type) G[j][i] = T[i - 1][j - 1] == '#';
                else G[i][j] = T[i - 1][j - 1] == '#';
            }
        if (type) swap(n, m);
        ::n = n, ::m = m;
        return DP();
    }
};

