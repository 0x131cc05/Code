#include <bits/stdc++.h>
using namespace std;

const int N = 110;

struct edge {
    int to, next, w;
} e[N * N];

int head[N], ecnt;

void adde(int from, int to, int w) {
    e[++ecnt] = { to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = { from, head[to], 0 }, head[to] = ecnt;
}

int dep[N];

bool BFS(int s, int t) {
    memset(dep, -1, sizeof(dep)), dep[s] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next)
            if (dep[e[i].to] == -1 && e[i].w) {
                dep[e[i].to] = dep[u] + 1, q.push(e[i].to);
                if (e[i].to == t) return true;
            }
    }
    return false;
}

int cur[N];

int DFS(int u, int f, int t) {
    if (u == t || !f) return f;
    int res = 0;
    for (int &i = cur[u], tmp; i; i = e[i].next)
        if (dep[e[i].to] == dep[u] + 1 && e[i].w && (tmp = DFS(e[i].to, min(f, e[i].w), t))) {
            e[i].w -= tmp, e[i ^ 1].w += tmp, res += tmp, f -= tmp;
            if (!f) break;
        }
    return res;
}

int dinic(int s, int t) {
    int res = 0;
    while (BFS(s, t)) memcpy(cur, head, sizeof(cur)), res += DFS(s, 1e9, t);
    return res;
}

int vis[N];

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].w) dfs(e[i].to);
}

struct Farmville {
    int minTime(vector<string> G, vector<int> t, vector<int> c, int budget) {
        int n = G.size();
        while (233) {
            ecnt = 1; memset(head, 0, sizeof(head));
            static int dp[N]; memset(dp, 0, sizeof(dp));
            int mx = 0;
            for (int i = 1; i <= n; i++) dp[i] = t[i - 1], mx = max(mx, t[i - 1]);
            for (int k = 1; k <= n; k++)
                for (int i = 1; i <= n; i++)
                    for (int j = 1; j <= n; j++)
                        if (G[i - 1][j - 1] == '1')
                            dp[i] = max(dp[i], dp[j] + t[i - 1]), mx = max(mx, dp[i]);
            if (!mx) return 0;
            int S = n * 2 + 1, T = S + 1;
            for (int i = 1; i <= n; i++) 
                adde(i, i + n, t[i - 1] ? c[i - 1] : 1e9);
            for (int i = 1; i <= n; i++) {
                if (dp[i] == t[i - 1]) adde(S, i, 1e9);
                if (dp[i] == mx) adde(i + n, T, 1e9);
            }
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++) if (G[i - 1][j - 1] == '1' && dp[i] == dp[j] + t[i - 1])
                    adde(j + n, i, 1e9);
            int res = dinic(S, T);
            if (res > budget) return mx;
            budget -= res, memset(vis, 0, sizeof(vis)), dfs(S);
            for (int i = 1; i <= n; i++) if (vis[i] && !vis[i + n]) 
                t[i - 1]--;
        }           
    }
};
