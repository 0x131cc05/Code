#include <bits/stdc++.h>
using namespace std;

const int N = 10010;
const int M = 510;
const int mod = 998244353;

typedef long long LL;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int dp[N][2][M], sz[N], k;

void dfs(int u, int f) {
    sz[u] = 1, dp[u][0][0] = dp[u][1][1] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u); static int g[2][M];
            for (int j = 0; j <= min(sz[u] + sz[e[i].to], k); j++) g[0][j] = g[1][j] = 0;
            for (int j = 0; j <= min(sz[u], k); j++) if (dp[u][0][j] || dp[u][1][j])
                for (int t = 0; t <= sz[e[i].to] && t + j <= k; t++) {
                    g[0][j + t] = (g[0][j + t] + (LL)dp[u][0][j] * (dp[e[i].to][1][t] - (t == 1))) % mod;
                    g[1][j + t] = (g[1][j + t] + (LL)dp[u][1][j] * (dp[e[i].to][1][t] - (t == 1))) % mod;
                    if (t) g[1][j + t] = (g[1][j + t] + (LL)dp[u][0][j] * dp[e[i].to][1][t]) % mod;
                }
            for (int j = 0; j <= min(sz[u] + sz[e[i].to], k); j++)
                dp[u][0][j] = g[0][j], dp[u][1][j] = g[1][j];
            sz[u] += sz[e[i].to];
        }
    dp[u][1][0] = 1;
}

int main() {
    freopen("test2.in", "r", stdin);
    int n; scanf("%d%d", &n, &k);
    for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), adde(a, b);
    dfs(1, 0); int res = 0;
    for (int i = 1; i <= k; i++) res = (res + dp[1][1][i]) % mod;
    printf("%d\n", res);
}
