#include <bits/stdc++.h>
using namespace std;

const int N = 300010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt, debug = false;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

int fa[20][N], dep[N];

void dfs(int u, int f) {
    dep[u] = dep[f] + 1, fa[0][u] = f;
    for (int i = 1; i < 20; i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u);
}

int LCA(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 19; i >= 0; i--) if (dep[fa[i][a]] >= dep[b]) a = fa[i][a];
    if (a == b) return a;
    for (int i = 19; i >= 0; i--) if (fa[i][a] != fa[i][b]) a = fa[i][a], b = fa[i][b];
    return fa[0][a];
}

int dis(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[LCA(a, b)];
}

struct item {
    int p[2], d;
    bool operator< (const item &b) const {
        return d < b.d;
    }
};

item merge(item A, item B) {
    int d = 0, a = 0, b = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            int tmp = dis(A.p[i], B.p[j]);
            if (tmp > d) d = tmp, a = A.p[i], b = B.p[j];
        }
    return max(max((item){ a, b, d }, A), B);
}

item down[N], up[N], son[N], suf[N];

int sz[N];

void dfs1(int u, int f) {
    down[u] = { u, u, 0 }, sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs1(e[i].to, u), down[u] = merge(down[u], down[e[i].to]), sz[u] += sz[e[i].to];
}

int id[N], tot = 0;

void dfs2(int u, int f) {
    item tmp = { u, u, 0 }; tot = 0;
    if (f) tmp = merge(tmp, up[u]);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            id[e[i].to] = ++tot, son[tot] = merge(tmp, down[e[i].to]), suf[tot] = son[tot];
        }
    for (int i = tot - 1; i >= 1; i--) suf[i] = merge(suf[i], suf[i + 1]);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            if (id[e[i].to] != tot) up[e[i].to] = merge(tmp, suf[id[e[i].to] + 1]);
            else up[e[i].to] = tmp;
            tmp = merge(tmp, son[id[e[i].to]]);
        }
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs2(e[i].to, u);
}

int solve(int d, int A, int B, int k) {
//    cerr << d << ' ' << A << ' ' << B << ' ' << k << endl;
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

int jump(int u, int t) {
    for (int i = 19; i >= 0; i--) if (t & (1 << i)) 
        u = fa[i][u];
    return u;
}

int find(int u, int v, int lca, int c) {
    if (c <= dep[u] - dep[lca]) 
        return jump(u, c);
    return jump(v, dep[u] + dep[v] - 2 * dep[lca] - c);
}

int get(int u, item t) {
    return max(dis(u, t.p[0]), dis(u, t.p[1]));
}

int solve(int k, int u, int v) {
    int d = dis(u, v), stepA = (k + 1) / 2, stepB = k / 2;
    if (stepB >= d) return solve(d, 0, 0, k);
    int lca = LCA(u, v);  
    // if (debug) cout <<u << ' ' << v << ' ' << lca << ' ' << stepA << endl;
    int A = find(u, v, lca, stepA), A1 = find(u, v, lca, stepA + 1); item d1;
    if (fa[0][A] == A1) d1 = up[A];
    else d1 = down[A1];
    int B = find(v, u, lca, stepB), B1 = find(v, u, lca, stepB + 1); item d2;
    if (fa[0][B] == B1) d2 = up[B];
    else d2 = down[B1];
    return solve(d, get(u, d2), get(v, d1), k);
}

int main() {
    freopen("b6.in", "r", stdin);
    freopen("1.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m); 
    for (int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        adde(a, b);
    }
    dfs(1, 0), dfs1(1, 0), dfs2(1, 0);
    while (m--) {
        if (!m) debug = true;
        int a, b, k; scanf("%d%d%d", &a, &b, &k);
        printf("%d\n", solve(k, a, b));
    }
}

