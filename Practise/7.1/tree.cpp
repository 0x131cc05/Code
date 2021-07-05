#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

int fa[N], dfn[N], sz[N], top[N], son[N], n, dfsn, dep[N];

void dfs(int u, int f) {
    sz[u] = 1, fa[u] = f, dep[u] = dep[f] + 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u), sz[u] += sz[e[i].to];
            if (sz[e[i].to] > sz[son[u]]) son[u] = e[i].to;
        }
}

int st[17][N], lg[N];

void dfs1(int u, int t) {
    top[u] = t, dfn[u] = ++dfsn, st[0][dfsn] = u;
    if (son[u]) dfs1(son[u], t);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != fa[u] && e[i].to != son[u]) {
            dfs1(e[i].to, e[i].to);
        }
}

void build() {
    dfs(1, 0), dfs1(1, 1);
    for (int i = 1; i < 17; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
}

int get(int l, int r) {
    if (l > r) return 0;
    int len = lg[r - l + 1];
    return max(st[len][l], st[len][r - (1 << len) + 1]);
}

bool check(int a, int b) {
    int mn = min(a, b);
    if (dep[a] < dep[b]) swap(a, b);
    int offset = 0;
    if (dfn[b] <= dfn[a] && dfn[b] + sz[b] - 1 >= dfn[a]) offset = 1;
    else b = fa[b];
    a = fa[a];
    int mx = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        mx = max(mx, get(dfn[top[a]], dfn[a])), a = fa[top[a]];
        if (mx > mn) return false;
    }
    if (dep[a] < dep[b]) swap(a, b);
    mx = max(mx, get(dfn[b] + offset, dfn[a]));
    return mx < mn;
}

struct tree {
    vector<int> G[N];

    int fa[17][N], dep[N];

    void clr() {
        for (int i = 1; i <= n; i++) G[i].clear();
    }

    void adde(int from, int to) {
        G[from].push_back(to), G[to].push_back(from);
    }

    void dfs(int u, int f) {
        dep[u] = dep[f] + 1, fa[0][u] = f;
        for (int i = 1; i < 17; i++) {
            if (dep[u] < (1 << i)) fa[i][u] = 0;
            else fa[i][u] = fa[i - 1][fa[i - 1][u]];
        }
        for (auto v : G[u]) if (v != f) 
            dfs(v, u);
    }

    int LCA(int a, int b) {
        if (dep[a] < dep[b]) swap(a, b);
        for (int i = 16; i >= 0; i--) if (dep[fa[i][a]] >= dep[b]) a = fa[i][a];
        if (a == b) return a;
        for (int i = 16; i >= 0; i--) if (fa[i][a] != fa[i][b]) a = fa[i][a], b = fa[i][b];
        return fa[0][a];
    }

    int jmp(int a, int lca) {
        for (int i = 16; i >= 0; i--) if (dep[fa[i][a]] > dep[lca]) a = fa[i][a];
        return a;
    }

    int solve(int a, int b) {
        int res = 0;
        while (a != b && !check(a, b)) {
            if (a > b) swap(a, b);
            a = fa[0][a], res++;
        }
        return res + (a != b);
    }
} T;

struct tcurts {
    int op, a, b;
} q[N * 5];

int m;

void solveSmall() {
    vector<int> wkr = {1};
    for (int i = 1; i <= m; i++) if (q[i].op == 1) 
        adde(q[i].a, q[i].b);
    build();
    static int fuck[N]; memset(fuck, 0, sizeof(fuck));
    int mx = 1;
    for (int i = 1; i <= m; i++) if (q[i].op == 1) {
        for (auto v : wkr) {
            if (v < q[i].b && fuck[v] > q[i].b) continue;
            if (v > q[i].b && fuck[q[i].b] > v) continue;
            if (check(v, q[i].b)) {
                if (v > q[i].b) fuck[q[i].b] = v;
                else fuck[v] = q[i].b;
            }
        }
        mx = max(mx, q[i].b);
        T.clr(), wkr.push_back(q[i].b);
        for (auto v : wkr) if (fuck[v])
            T.adde(v, fuck[v]);
        T.dfs(mx, 0);
    } else {
        printf("%d\n", T.solve(q[i].a, q[i].b));
    }
}

template<class T> void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
    // freopen("tree.in", "r", stdin), freopen("tree.out", "w", stdout);
    read(n), read(m);
    for (int i = 1; i <= m; i++) 
        read(q[i].op), read(q[i].a), read(q[i].b);
    if (n <= 5000) solveSmall();
}