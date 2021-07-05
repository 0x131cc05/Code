#include <bits/stdc++.h>
using namespace std;

const int N = 35;

typedef long long LL;

char G[N][N];

int rgt[N][N];

LL dp[2][3][N * N][N][N];

int main() {
    freopen("logo.in", "r", stdin), freopen("logo.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) 
        scanf("%s", G[i] + 1);
    for (int i = m; i >= 1; i--)
        for (int j = 1; j <= n; j++)
            if (G[j][i] != '#') rgt[j][i] = rgt[j][i + 1] + 1;
    for (int j = 0; j <= m; j++) rgt[0][j] = 1;
    dp[0][0][0][0][0] = 1;
    int cur = 0;
    LL ans = 0;
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            cur++;
            for (int a = 0; a <= 1; a++) if (!(a == 1 && i == 1)) {
                if (a && G[i][j] == '#') continue;
                for (int b = 0; b <= 2; b++) 
                    for (int c = 0; c <= n; c++)
                        for (int d = c; d <= n; d++) if (dp[a][b][cur - 1][c][d]) {
                            LL w = dp[a][b][cur - 1][c][d];
                            if (c == i || d == i) {
                                if (a) continue;
                                if (j != m && G[i][j + 1] != '#') dp[0][b][cur][c][d] += w;
                                int tc = c == i ? 0 : c;
                                int td = d == i ? 0 : d;
                                if (tc > td) swap(tc, td);
                                dp[0][b][cur][tc][td] += w;
                            } else {
                                if (a) {
                                    dp[a][b][cur][c][d] += w;
                                    if (j == m || G[i][j + 1] == '#') continue;
                                    if (b != 2) dp[0][b + 1][cur][min(i, d)][max(i, d)] += w;
                                    else ans += w * rgt[c][j + (c <= i)] * rgt[d][j + (d <= i)] * rgt[i][j + 1];
                                } else {
                                    if (G[i][j] != '#') dp[1][b][cur][c][d] += w;
                                    dp[0][b][cur][c][d] += w;
                                }
                            }
                        }
            }   
        }
    }
    printf("%lld\n", ans);
}