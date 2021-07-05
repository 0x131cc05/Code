#include <bits/stdc++.h>
using namespace std;

const int N = 50010;

vector<int> G[N];

int h[N], f[N], g[N], dep[N];

void dfs(int u, int fa) {
    g[u] = h[u], dep[u] = dep[fa] + 1;
    for (auto v : G[u]) if (v != fa) {
        dfs(v, u), f[u] += f[v];
        int t = min(g[v], g[u]);
        g[u] -= t, g[v] -= t, f[u] += t * 2;
    }
}

int ans[N];

void dfs1(int u, int fa, int r, int tp) {
    int tot = r;
    for (auto v : G[u]) if (v != fa) tot += g[v];
    int hh = g[u] + (u != 1);
    ans[u] = tp + min(tot, hh) * 2;
    for (auto v : G[u]) if (v != fa) {
        int tmp = tot - g[v], offset = min(hh, tmp);
        dfs1(v, u, hh - offset, tp + offset * 2);
    }
}

int main() {
    // freopen("4.in", "r", stdin);
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
    for (int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        G[a + 1].push_back(b + 1), G[b + 1].push_back(a + 1);
    }
    for (int i = 1; i <= n; i++) h[i] -= G[i].size();
    dfs(1, 0), dfs1(1, 0, 0, 0);
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i] + f[1] + (n - 1) * 2 - (dep[i] - 1));
}