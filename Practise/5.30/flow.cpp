#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct edge {
    int to, next, w, id;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to, int w, int id) {
    e[++ecnt] = { to, head[from], w, id }, head[from] = ecnt;
    e[++ecnt] = { from, head[to], w, id }, head[to] = ecnt;
}

struct tree {
    struct node {
        int l, r, mn;
    } T[N << 2];

    void pushup(int rt) {
        T[rt].mn = min(T[rt << 1].mn, T[rt << 1 | 1].mn);
    }

    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r, T[rt].mn = 1e9;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
    }

    void update(int rt, int pos, int x) {
        int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
        if (l == r) return T[rt].mn = x, void();
        if (pos <= mid) update(rt << 1, pos, x);
        else update(rt << 1 | 1, pos, x);
        pushup(rt);
    }

    int query(int rt, int start, int end) {
        if (start > end) return 1e9;
        int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
        if (start <= l && r <= end) return T[rt].mn;
        int res = 1e9;
        if (start <= mid) res = min(res, query(rt << 1, start, end));
        if (end > mid) res = min(res, query(rt << 1 | 1, start, end));
        return res;
    }
} T1, T2;

int dep[N], fa[N], dfn[N], dfsn, pos[N], bl[N];
int sz[N], son[N], top[N], fuck[N];

int rt;

int id[N], cir[N], from[N], to[N], wkr[N], tot;

void dfs(int u, int f) {
    fa[u] = f, dep[u] = dep[f] + 1, bl[u] = rt, sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !cir[e[i].to]) {
            pos[e[i].id] = e[i].to, dfs(e[i].to, u), fuck[e[i].to] = e[i].w;
            if (sz[e[i].to] > sz[son[u]]) son[u] = e[i].to;
            sz[u] += sz[e[i].to];
        }
}

void dfs1(int u, int t) {
    top[u] = t, dfn[u] = ++dfsn, T1.update(1, dfsn, fuck[u]);
    if (son[u]) dfs1(son[u], t);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != fa[u] && e[i].to != son[u] && !cir[e[i].to]) dfs1(e[i].to, e[i].to);
}

int query(int u, int v) {
    int res = 1e9;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res = min(res, T1.query(1, dfn[top[u]], dfn[u])), u = fa[top[u]];
    }
    if (u != v) {
        if (dep[u] > dep[v]) swap(u, v);
        res = min(res, T1.query(1, dfn[u] + 1, dfn[v]));
    }
    return res;
}

int n, m;

void solve1() {
    for (int i = 1; i < n; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        adde(a, b, c, i);
    }
    T1.build(1, 1, n), dfs(1, 0), dfs1(1, 1);
    int q; scanf("%d", &q);
    while (q--) {
        int op, a, b; scanf("%d%d%d", &op, &a, &b);
        if (op == 1) T1.update(1, dfn[pos[a]], b);
        else printf("%d\n", query(a, b)); 
    }
}

int _fa[N];

int find(int x) {
    return x == _fa[x] ? x : _fa[x] = find(_fa[x]);
}

bool push(int u, int f, int t) {
    if (u == t) return id[u] = ++tot, cir[u] = 1, true;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && push(e[i].to, u, t)) 
            return id[u] = ++tot, cir[u] = 1, true;
    return false;
}

void solve2() {
    for (int i = 1; i <= n; i++) _fa[i] = i;
    int hh = 0, u = 0, v = 0, l = 0;
    for (int i = 1; i <= n; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c), from[i] = a, to[i] = b, wkr[i] = c;
        int fx = find(a), fy = find(b);
        if (fx != fy) adde(a, b, c, i), _fa[fx] = fy;
        else hh = i, u = a, v = b, l = c;
    }
    push(u, 0, v);
    T1.build(1, 1, n), T2.build(1, 1, n);
    for (int i = 1; i <= n; i++) if (cir[i]) 
        rt = i, dfs(i, 0), dfs1(i, i);
    for (int i = 1; i <= n; i++) if (i != hh) {
        int a = from[i], b = to[i];
        if (cir[a] && cir[b]) {
            T2.update(1, max(id[a], id[b]), wkr[i]);
        }
    }
    int q; scanf("%d", &q);
    while (q--) {
        int op, a, b; scanf("%d%d%d", &op, &a, &b);
        if (op == 1) {
            if (pos[a]) T1.update(1, dfn[pos[a]], b);
            else if (a == hh) l = b;
            else T2.update(1, max(id[from[a]], id[to[a]]), b);
        } else {
            if (bl[a] == bl[b]) printf("%d\n", query(a, b));
            else {
                int A = query(a, bl[a]), B = query(b, bl[b]);
                a = id[bl[a]], b = id[bl[b]];
                if (a > b) swap(a, b);
                int C = T2.query(1, a + 1, b), D = min(l, min(T2.query(1, 2, a), T2.query(1, b + 1, tot)));
                printf("%d\n", min(A, min(B, C + D)));
            }
        }
    }
}

int main() {
    freopen("flow.in", "r", stdin), freopen("flow.out", "w", stdout);
    scanf("%d%d", &n, &m);
    if (m == n - 1) solve1();
    else if (m == n) solve2();
}