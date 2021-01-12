#include <bits/stdc++.h>
using namespace std;

int dp[2][6][1 << 15];

int G[51][21], v[51][21];

void check(int &x, int y) {
    x = max(x, y);
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) scanf("%d", &G[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) scanf("%d", &v[i][j]);
    memset(dp, -1, sizeof(dp)), dp[0][2][0] = 0; int cur = 0, mask = (1 << m) - 1;
    for (int j = 1; j <= n; j++)
        for (int i = 1; i <= m; i++) {
            cur ^= 1, memset(dp[cur], -1, sizeof(dp[cur]));
            for (int s = 0; s < 1 << m; s++) {
                for (int ls = 0; ls < 6; ls++) if (dp[cur ^ 1][ls][s] >= 0) {
                    if (G[j][i] == 1) {
                        if (ls == 0 || ls == 4 || ls == 5) continue;
                        if (s & (1 << m - 1)) continue;
                        check(dp[cur][2][(s << 1) & mask], dp[cur ^ 1][ls][s]);
                    } else {
                        for (int nw = 0; nw < 6; nw++) {
                            if (s & (1 << m - 1)) {
                                if (nw == 0 || nw == 3 || nw == 5) continue;
                            } else {
                                if (nw != 0 && nw != 3 && nw != 5) continue;
                            }
                            if (i == 1 && (nw == 0 || nw == 2 || nw == 3)) continue;
                            if (i == m && (nw == 0 || nw == 4 || nw == 5)) continue;
                            if (ls == 0 || ls == 4 || ls == 5) {
                                if (nw != 0 && nw != 2 && nw != 3) continue;
                            } else {
                                if (nw == 0 || nw == 2 || nw == 3) continue;
                            }
                            check(dp[cur][nw][(s << 1) & mask | (nw == 1 || nw == 3 || nw == 5)], dp[cur ^ 1][ls][s] + (nw > 1) * v[j][i]);
                        }
                    }
                }
            }
        }
    if (dp[cur][2][0] < 0) puts("-1");
    else printf("%d\n", dp[cur][2][0]);
}
