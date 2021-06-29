#include <bits/stdc++.h>
using namespace std;

const int N = 510;
const int INF = 1e8;

typedef long long LL;

int mp[N][N];

vector<int> G[N];

struct edge {
    int to, next;
} e[N * N];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

int dfn[N], low[N], dfsn, stk[N], top, cnt;

void tarjan(int u, int f) {
    dfn[u] = low[u] = ++dfsn, stk[++top] = u;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            if (!dfn[e[i].to]) {
                tarjan(e[i].to, u), low[u] = min(low[u], low[e[i].to]);
                if (low[u] == dfn[u]) {
                    int v = 0; cnt++;
                    while (v != e[i].to) {
                        v = stk[top--];
                        G[cnt].push_back(v), G[v].push_back(cnt);
                    }
                    G[u].push_back(cnt), G[cnt].push_back(u);
                }
            } else low[u] = min(low[u], dfn[e[i].to]);
        }
} 

struct tcurts {
    int mx; unsigned int ways;
    void reset() { mx = -INF, ways = 0; }
    tcurts operator+ (tcurts b) {
        if (mx == b.mx) return { mx, ways + b.ways };
        return { max(mx, b.mx), mx > b.mx ? ways : b.ways };
    }
    tcurts operator* (tcurts b) {
        return { mx + b.mx, ways * b.ways };
    }
};

tcurts dp[4][11][1 << 11];

int n;

tcurts g[5][N * 2], h[5][N * 2], ans;

void dfs(int u, int f) {
    for (int i = 0; i < 4; i++) g[i][u].reset(), h[i][u].reset();
    h[0][u] = {0, 1};
    for (auto v : G[u]) if (v != f) dfs(v, u);
    if (u <= n) {
        g[0][u] = { 0, 1 };
        for (auto v : G[u]) if (v != f) 
            for (int i = 2; i >= 0; i--)
                for (int j = 1; i + j <= 3; j++)
                    g[i + j][u] = g[i + j][u] + g[i][u] * h[j][v];
        h[1][u] = g[0][u] + g[1][u] + g[2][u];
        ans = ans + h[1][u] + g[3][u];
        return;
    }
    vector<int> p; p.push_back(f);
    for (auto v : G[u]) if (v != f) p.push_back(v);
    int tot = p.size();
    for (int i = 0; i < tot; i++)
        for (int j = 0; j <= 3; j++)
            for (int s = 0; s < 1 << tot; s++) dp[j][i][s].reset();
    for (int i = 1; i < tot; i++) 
        for (int j = 0; j <= 3; j++) 
            dp[j][i][1 << i] = g[j][p[i]];
    dp[0][0][1] = { 0, 1 };
    for (int s = 1; s < 1 << tot; s++) 
        for (int rt = 0; rt < tot; rt++) if (s & (1 << rt)) {
            int nxt = s ^ (1 << rt), low = nxt & -nxt;
            for (int s1 = nxt; s1; s1 = (s1 - 1) & nxt) {
                if (s1 & low) 
                    for (int k = 0; k <= 2; k++)
                        for (int rt1 = 0; rt1 < tot; rt1++) if (s1 & (1 << rt1)) {
                            if (mp[p[rt]][p[rt1]] == -INF) continue;
                            auto t = dp[k][rt1][s1];
                            if (t.ways && t.mx > -INF) for (int j = 1; j <= 3; j++)
                                dp[j][rt][s] = dp[j][rt][s] + dp[j - 1][rt][s ^ s1] * (tcurts){ t.mx + mp[p[rt]][p[rt1]], t.ways };
                        }
            }
        }
    for (int s = 1; s < 1 << tot; s += 2) 
        for (int j = 1; j <= 3; j++)
            h[j][u] = h[j][u] + dp[j][0][s];
    for (int s = 2; s < 1 << tot; s += 2) {
        int rt = __builtin_ctz(s);
        if (s ^ (1 << rt)) for (int j = 1; j <= 3; j++)
            ans = ans + dp[j][rt][s];
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int m; scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) mp[i][j] = -INF;
        for (int i = 1; i <= cnt; i++) G[i].clear();
        ecnt = dfsn = top = 0, ans = {0, 1}, cnt = n;
        for (int i = 1; i <= n; i++) head[i] = dfn[i] = low[i] = 0;
        for (int i = 1; i <= m; i++) {
            int a, b, c; scanf("%d%d%d", &a, &b, &c), adde(a, b);
            mp[a][b] = mp[b][a] = c;
        }
        tarjan(1, 0), dfs(1, 0);
        printf("%d %u\n", ans.mx, ans.ways);
    }
}