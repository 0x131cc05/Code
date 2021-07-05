#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

vector<int> G[N];

int dfn[N], low[N], dfsn, scc[N], tot, stk[N], top, vis[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++dfsn, vis[u] = 1, stk[++top] = u;
    for (auto v : G[u]) if (!dfn[v])
        tarjan(v), low[u] = min(low[u], low[v]);
    else if (vis[v]) low[u] = min(low[u], dfn[v]);
    if (low[u] == dfn[u]) {
        tot++; int v = 0;
        while (v != u) v = stk[top--], vis[v] = 0, scc[v] = tot;
    }
}

void ad(int u, int v) {
    G[u].push_back(v);
}

int n, m;

int id(int u, int v, int tp) {
    return (u - 1) * n + v + tp * n * m;
}

vector<int> T[N];

int fa[N], dep[N], zjk[N], wkr[N], cnt;

void dfs(int u, int f) {
    zjk[u] = ++cnt;
    fa[u] = f, dep[u] = dep[f] + 1;
    if (f) for (int i = 1; i <= m; i++) 
        ad(id(i, u, 1), id(i, f, 1)), ad(id(i, f, 0), id(i, u, 0));
    for (auto v : T[u]) 
        if (v != f) dfs(v, u);
    for (auto v1 : T[u]) if (v1 != f)
        for (auto v2 : T[u]) if (v2 != v1 && v2 != f) 
            for (int i = 1; i <= m; i++)
                ad(id(i, v1, 1), id(i, v2, 0));
    wkr[u] = cnt;
}

int jmp(int u, int v) {
    while (fa[u] != v) u = fa[u];
    return u;
}

void link(int rt, int u, int v, int lca) {
    if (zjk[lca] < zjk[rt] && zjk[rt] <= wkr[lca]) {
        int p = jmp(rt, lca);
        ad(id(u, p, 1), id(u, p, 0)), ad(id(v, p, 1), id(v, p, 0));
        ad(id(u, lca, 0), id(v, lca, 1)), ad(id(v, lca, 0), id(u, lca, 1));
        for (auto t : T[lca]) if (t != fa[lca] && t != p) 
            ad(id(u, t, 1), id(v, t, 0)), ad(id(v, t, 1), id(u, t, 0));
    } else {
        if (rt != lca) ad(id(u, lca, 0), id(u, lca, 1)), ad(id(v, lca, 0), id(v, lca, 1));
        else ad(id(u, lca, 0), id(v, lca, 1)), ad(id(v, lca, 0), id(u, lca, 1));
        for (auto t : T[lca]) if (t != fa[lca]) 
            ad(id(u, t, 1), id(v, t, 0)), ad(id(v, t, 1), id(u, t, 0));
    }
}

int ans[N];

int main() {
    // freopen("rabbit.in", "r", stdin), freopen("rabbit.out", "w", stdout);
    int q; scanf("%d%d%d", &n, &m, &q);
    for (int i = 2; i <= n; i++) {
        int f; scanf("%d", &f), f++;
        T[f].push_back(i), T[i].push_back(f);
    }
    dfs(1, 0);
    while (q--) {
        int rt, a, b, lca; scanf("%d%d%d%d", &rt, &a, &b, &lca);
        link(rt + 1, a + 1, b + 1, lca + 1);
    }
    for (int i = 1; i <= m; i++) ad(id(i, 1, 0), id(i, 1, 1));
    for (int i = 1; i <= 2 * n * m; i++) 
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= m; i++) {
        int mx = 0, pos = 0;
        for (int j = 1; j <= n; j++) {
            int a = scc[id(i, j, 0)], b = scc[id(i, j, 1)];
            if (a == b) return puts("-1"), 0;
            if (b < a && dep[j] > mx) mx = dep[j], pos = j;
        }
        ans[i] = pos - 1;
    }
    for (int i = 1; i <= m; i++) printf("%d ", ans[i]);
}