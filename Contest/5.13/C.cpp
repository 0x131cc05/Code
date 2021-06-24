#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int mod = 1e9 + 7;

typedef long long LL;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
} 

int afs(int u, int f) {
    int res = 0;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) 
            res = max(res, afs(e[i].to, u) + 1);
    return res;
}

inline void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int lim, len[N];

namespace FUCK {
    
int dp[310][310][310];

void dfs(int u, int f) {
    len[u] = 0, dp[u][0][0] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            int v = e[i].to; dfs(v, u); static int tmp[N][N];
            int fuck = max(len[u], len[v] + 1);
            for (int j = 0; j <= fuck; j++)
                for (int k = 0; k <= fuck; k++) tmp[j][k] = 0;
            for (int j = 0; j <= len[u]; j++)
                for (int k = 0; k <= len[u]; k++) if (dp[u][j][k]) {
                    for (int l = 0; l <= len[v] && k + l <= lim; l++) 
                        for (int t = 0; t <= len[v] && j + t <= lim; t++) if (dp[v][l][t]) {
                            LL w = (LL)dp[u][j][k] * dp[v][l][t] % mod;
                            if (t + j + 1 <= lim) Inc(tmp[max(j, l)][max(k, t + 1)], w);
                            if (k + l + 1 <= lim) Inc(tmp[max(j, l + 1)][max(k, t)], w);
                        }
                }
            for (int j = 0; j <= fuck; j++)
                for (int k = 0; k <= fuck; k++) dp[u][j][k] = tmp[j][k];
            len[u] = fuck;
        }
}

};

namespace FUCK1 {
    
int dp[N][81][81];

void dfs(int u, int f) {
    len[u] = 0, dp[u][0][0] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            int v = e[i].to; dfs(v, u); static int tmp[N][N];
            int fuck = min(lim, max(len[u], len[v] + 1));
            for (int j = 0; j <= fuck; j++)
                for (int k = 0; k <= fuck; k++) tmp[j][k] = 0;
            for (int j = 0; j <= len[u] && j <= lim; j++)
                for (int k = 0; k <= len[u] && k <= lim; k++) if (dp[u][j][k]) {
                    for (int l = 0; l <= len[v] && k + l <= lim; l++) 
                        for (int t = 0; t <= len[v] && j + t <= lim; t++) if (dp[v][l][t]) {
                            LL w = (LL)dp[u][j][k] * dp[v][l][t] % mod;
                            if (t + j + 1 <= lim) Inc(tmp[max(j, l)][max(k, t + 1)], w);
                            if (k + l + 1 <= lim) Inc(tmp[max(j, l + 1)][max(k, t)], w);
                        }
                }
            for (int j = 0; j <= fuck; j++)
                for (int k = 0; k <= fuck; k++) dp[u][j][k] = tmp[j][k];
            len[u] = fuck;
        }
}

};

int main() {
    int n; scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), adde(a, b);
    for (int i = 1; i <= n; i++) lim = max(lim, (afs(i, 0) + 1) / 2);
    if (n <= 300) FUCK::dfs(1, 0);
    else FUCK1::dfs(1, 0);
    int res = 0;
    for (int i = 0; i <= len[1] && i <= lim; i++)
        for (int j = 0; j <= len[1] && j <= lim; j++) {
            if (n <= 300) Inc(res, FUCK::dp[1][i][j]);
            else Inc(res, FUCK1::dp[1][i][j]);
        }
    printf("%d\n", res);
}
