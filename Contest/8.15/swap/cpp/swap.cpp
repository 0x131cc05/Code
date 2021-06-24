#include "swap.h"

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 500010;

struct edge {
    int from, to, w;
    bool operator < (const edge &b) const {
        return w < b.w;
    }
} e[N * 2];

int n;

struct Kruskal1 {
    vector<int> G[N];
    int ncnt, val[N], fa[N], nw[N];
    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    
    void init() {
        ncnt = n;
        for (int i = 1; i <= n; i++) fa[i] = nw[i] = i;
    }
    
    void merge(int u, int v, int w) {
//        cout << "merge: " << u << ' ' << v << ' ' << w << endl;
        u = find(u), v = find(v);
        int t = ++ncnt; G[t].push_back(nw[u]), G[t].push_back(nw[v]), val[t] = w;
        fa[u] = v, nw[v] = t;
    }
    
    int father[18][N], dep[N];
    void dfs(int u, int f) {
        father[0][u] = f, dep[u] = dep[f] + 1;
        for (int i = 1; i <= 17; i++) father[i][u] = father[i - 1][father[i - 1][u]];
        for (auto v : G[u]) dfs(v, u);
    }
    
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = 17; i >= 0; i--) if (dep[father[i][u]] >= dep[v]) u = father[i][u];
        if (u == v) return u;
        for (int i = 17; i >= 0; i--) if (father[i][u] != father[i][v]) u = father[i][u], v = father[i][v];
        return father[0][u];
    }
    
    int query(int u, int v) {
        if (find(u) != find(v)) return 2e9;
        return val[lca(u, v)];
    }
} T1;

struct MST {
    struct edge {
        int to, next;
    } e[N * 2];
    int head[N], ecnt;
    void adde(int from, int to) {
        e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
        e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
    }
    
    int fa[N];
    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    void init() {
        for (int i = 1; i <= n; i++) fa[i] = i;
    }
    
    int father[N], dep[N];
    void dfs(int u, int f) {
        father[u] = f, dep[u] = dep[f] + 1;
        for (int i = head[u]; i; i = e[i].next)
            if (e[i].to != f) dfs(e[i].to, u);
    }
    
    void merge(int u, int v, int w) {
        while (find(u) != find(v)) {
            u = find(u), v = find(v);
            if (dep[u] < dep[v]) swap(u, v);
            T1.merge(u, father[u], w), fa[u] = father[u], u = father[u];
        }
    }
} T2;

struct Kruskal2 {
    vector<int> G[N];
    int ncnt, val[N], fa[N], nw[N], fuck[N][3], ok[N];
    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    
    void init() {
        ncnt = n;
        for (int i = 1; i <= n; i++) fa[i] = nw[i] = i;
    }
    
    void push(int u, int w) {
        for (int i = 0; i < 3; i++) if (fuck[u][i] == 0) {
            fuck[u][i] = w; return;
        }
    }
    
    bool merge(int u, int v, int w) {
        push(u, w), push(v, w);
        u = find(u), v = find(v);
        if (u == v) {
            int t = ++ncnt; G[t].push_back(nw[u]), val[t] = w, nw[u] = t;
            return false;
        }
        int t = ++ncnt; G[t].push_back(nw[u]), G[t].push_back(nw[v]), val[t] = w;
        fa[u] = v, nw[v] = t;
        return true;
    }
    
    int father[20][N], dep[N], mn[N];
    void dfs(int u, int f) {
        father[0][u] = f, dep[u] = dep[f] + 1;
        if (u <= n) mn[u] = fuck[u][2] ? fuck[u][2] : 2e9;
        else mn[u] = 2e9;
        for (int i = 1; i <= 19; i++) father[i][u] = father[i - 1][father[i - 1][u]];
        for (auto v : G[u]) dfs(v, u), mn[u] = min(mn[u], mn[v]);
        if (u > n && mn[u] <= val[u]) ok[u] = 1;
//        cout << "fuck: " << u << ' ' << val[u] << ' ' << mn[u] << ' ' << ok[u] << endl;
    }
    
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = 19; i >= 0; i--) if (dep[father[i][u]] >= dep[v]) u = father[i][u];
        if (u == v) return u;
        for (int i = 19; i >= 0; i--) if (father[i][u] != father[i][v]) u = father[i][u], v = father[i][v];
        return father[0][u];
    }
    
    int query(int u, int v) {
        int t = lca(u, v);
//        cout << val[t] << endl;
        if (ok[t]) return val[t];
        for (int i = 19; i >= 0; i--) 
            if (father[i][t] && !ok[father[i][t]]) t = father[i][t];
        int hh = father[0][t];
        return ok[hh] ? val[hh] : 2e9;
    }
} T3;

int inTree[N], rt[N];

void init(int n, int m, vector<int> U, vector<int> V, vector<int> W) {
    ::n = n, T1.init(), T2.init(), T3.init();
    for (int i = 1; i <= m; i++) e[i] = (edge){ U[i - 1] + 1, V[i - 1] + 1, W[i - 1] };
    sort(e + 1, e + m + 1); 
    for (int i = 1; i <= m; i++) {
        int u = e[i].from, v = e[i].to;
        if (T3.merge(u, v, e[i].w)) 
            T2.adde(u, v), inTree[i] = 1;
    }
    T2.dfs(1, 0), T3.dfs(T3.ncnt, 0);
    for (int i = 1; i <= m; i++) if (!inTree[i]) 
        T2.merge(e[i].from, e[i].to, e[i].w);
    for (int i = 1; i <= n; i++) rt[T1.nw[T1.find(i)]] = 1;
    for (int i = n + 1; i <= T1.ncnt; i++) if (rt[i])
        T1.dfs(i, 0);
//    cout << "fuck: " << T3.fuck[6][2] << endl;
}

int getMinimumFuelCapacity(int X, int Y) {
    int res = min(T3.query(X + 1, Y + 1), T1.query(X + 1, Y + 1));
//    cout << "first: " << T3.query(X + 1, Y + 1) << endl;
    return res <= 1e9 ? res : -1;
}
