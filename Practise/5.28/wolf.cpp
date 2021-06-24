#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

int d1[N], d2[N], up[N], fa[20][N], dep[N], dfn[N], ed[N], dfsn;

void dfs(int u, int f) {
    dfn[u] = ++dfsn;
    fa[0][u] = f, dep[u] = dep[f] + 1;
    for (int i = 1; i < 20; i++)
        fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u); int w = d1[e[i].to] + 1;
            if (w > d1[u]) d2[u] = d1[u], d1[u] = w;
            else if (w > d2[u]) d2[u] = w;
        }
    ed[u] = dfsn;
}

int LCA(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 19; i >= 0; i--) if (dep[fa[i][a]] >= dep[b]) a = fa[i][a];
    if (a == b) return a;
    for (int i = 19; i >= 0; i--) if (fa[i][a] != fa[i][b]) a = fa[i][b], b = fa[i][b];
    return fa[0][a];
}

int dis(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[LCA(a, b)];
}

int jump(int a, int b) {
    for (int i = 19; i >= 0; i--) if (dep[fa[i][a]] > dep[b]) a = fa[i][a];
    return a;
}

int chain(int u, int v) {
    if (dfn[u] <= dfn[v] && dfn[v] <= ed[u]) {
        int t = jump(v, u);
        if (d1[u] == d1[t] + 1) return max(d2[u], up[u]);
        return max(d1[u], up[u]);
    } 
    return d1[u];
}

void dfs1(int u, int f) {
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            int v = e[i].to;
            up[v] = max(up[v], up[u] + 1);
            if (d1[u] == d1[v] + 1) up[v] = max(up[v], d2[u] + 1);
            else up[v] = max(up[v], d1[u] + 1);
            dfs1(e[i].to, u);
        }
}

int solve(int d, int A, int B, int k) {
    if (d > k) return k & 1;
    if ((d & 1) && (k & 1)) {
        int fir = (k + 1) / 2;
        if (d <= fir) return 2;
        if (B >= fir - 1) return 1;
        return 2;
    }
    if ((d & 1) && !(k & 1)) return 0;
    if ((!(d & 1)) && (k & 1)) return 1;
    int sec = k / 2;
    if (d <= sec) return -1;
    if (A >= sec) return 0;
    return -1;
}

int main() {
    freopen("wolf.in", "r", stdin), freopen("wolf.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b), adde(a, b);
    }
    dfs(1, 0), dfs1(1, 0);
    while (m--) {
        int a, b, k; scanf("%d%d%d", &a, &b, &k);
        printf("%d\n", solve(dis(a, b), chain(a, b), chain(b, a), k));
    }
}