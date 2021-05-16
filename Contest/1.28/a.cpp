#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int dfn[N], dep[N], dfsn, sz[N], fa[18][N];

void dfs(int u, int f) {
    dep[u] = dep[f] + 1, fa[0][u] = f, dfn[u] = ++dfsn, sz[u] = 1;
    for (int i = 1; i <= 17; i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u), sz[u] += sz[e[i].to];
}

int LCA(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 17; i >= 0; i--) 
        if (dep[fa[i][a]] >= dep[b]) a = fa[i][a];
    if (a == b) return a;
    for (int i = 17; i >= 0; i--)
        if (fa[i][a] != fa[i][b]) a = fa[i][a], b = fa[i][b];
    return fa[0][a];
}

vector<int> G[N];

void push(int a, int b) {
    G[a].push_back(b), G[b].push_back(a);
}

int ok[N], dp[2][N], fuck[N], n;

void dfs1(int u, int f) {
    dp[1][u] = 0, dp[0][u] = fuck[u] ? 1e9 : 0; 
    int tmp = 0;
    for (auto v : G[u]) if (v != f) {
        dfs1(v, u);
        tmp += min(dp[0][v], dp[1][v]);
        dp[1][u] = min(dp[0][u] + dp[1][v], dp[1][u] + dp[0][v]);
        dp[0][u] += dp[0][v];
        dp[0][u] = min(dp[0][u], n + 1), dp[1][u] = min(dp[1][u], n + 1);
    }
    if (ok[u]) dp[0][u] = min(dp[0][u], dp[1][u] + 1);
    if (!fuck[u]) dp[0][u] = min(dp[0][u], tmp + 1);
    G[u].clear(), ok[u] = 0;
}

int main() {
    freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
    int m; scanf("%d%d", &n, &m);
    for (int i = 1, a, b; i < n; i++) 
        scanf("%d%d", &a, &b), adde(a, b);
    dfs(1, 0);
    while (m--) {
        int k; scanf("%d", &k); vector<int> p(k);
        for (int i = 0; i < k; i++) scanf("%d", &p[i]), fuck[p[i]] = 1;
        sort(p.begin(), p.end(), [&](int a, int b) { return dfn[a] < dfn[b]; });
        stack<int> stk; stk.push(p[0]);
        auto chk = [&](int a, int b) {
            if (!a) return;
            G[a].push_back(b), G[b].push_back(a);
            ok[a] = dep[a] - dep[b] > 1;
        };
        for (int i = 1; i < p.size(); i++) {
            if (p[i] == stk.top()) continue;
            int u = stk.top(), v = p[i], lca = LCA(u, v);
            int lst = 0;
            while (stk.size() && dep[stk.top()] > dep[lca]) 
                chk(lst, stk.top()), lst = stk.top(), stk.pop();
            if (!stk.size() || stk.top() != lca) stk.push(lca);
            chk(lst, lca), stk.push(v);
        }
        int lst = 0;
        while (stk.size()) chk(lst, stk.top()), lst = stk.top(), stk.pop();
        dfs1(lst, 0);
        int res = min(dp[0][lst], dp[1][lst]);
        printf("%d\n", res <= n ? res : -1);
        for (auto t : p) fuck[t] = 0;
    }
}
