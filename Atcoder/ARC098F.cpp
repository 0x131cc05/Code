#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

int fa[N]; 

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

LL dp[N], a[N], b[N], sum[N];

void dfs(int u, int f) {
    sum[u] = b[u];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u), sum[u] += sum[e[i].to];
    dp[u] = sum[u] + a[u];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dp[u] = min(dp[u], sum[u] - sum[e[i].to] + max(a[u], dp[e[i].to]));
}

int id[N], vis[N]; vector<int> G[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i], &b[i]), a[i] = max(0ll, a[i] - b[i]);
    for (int i = 1; i <= n; i++) id[i] = fa[i] = i;
    for (int i = 1, a, b; i <= m; i++) scanf("%d%d", &a, &b), G[a].push_back(b), G[b].push_back(a);
    sort(id + 1, id + n + 1, [](int i, int j) { return a[i] < a[j]; }), vis[id[1]] = 1;
    for (int i = 2; i <= n; i++) {
        int u = id[i]; vis[u] = 1;
        for (auto v : G[u]) if (vis[v]) {
            if (find(u) == find(v)) continue;
            adde(find(v), u), fa[find(v)] = u;
        }
    }
    dfs(id[n], 0), printf("%lld\n", dp[id[n]]);
}