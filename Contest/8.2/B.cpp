#include <bits/stdc++.h>
using namespace std;

const int N = 50010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int fa[N], top[N], son[N], dfn[N], sz[N], ed[N], dfsn, ct[N], rk[N], dep[N];

void dfs(int u, int f) {
    fa[u] = f, sz[u] = 1, dep[u] = dep[f] + 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u), sz[u] += sz[e[i].to], ct[u] += ct[e[i].to];
            if (sz[e[i].to] > sz[son[u]]) son[u] = e[i].to;
        }
}

void dfs1(int u, int t) {
    top[u] = t, dfn[u] = ++dfsn, rk[dfsn] = u;
    if (son[u]) dfs1(son[u], t);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != fa[u] && e[i].to != son[u]) 
            dfs1(e[i].to, e[i].to);
    ed[u] = dfsn;
}

int st[16][N], n, lg[N];

void pre() {
    for (int i = 1; i <= n; i++) st[0][i] = ct[rk[i]];
    for (int i = 1; i <= 15; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++) 
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
}

int get(int l, int r) {
    int len = lg[r - l + 1];
    return min(st[len][l], st[len][r - (1 << len) + 1]);
}

int tag[N * 32], ncnt, ls[N * 32], rs[N * 32], mn[N * 32]; vector<int> pool;

int apply() {
    if (pool.size()) {
        int u = pool.back(); pool.pop_back();
        return tag[u] = ls[u] = rs[u] = 0, u;
    }
    return ++ncnt;
}

void pushup(int rt, int l, int r) {
    mn[rt] = 1e9; int mid = (l + r) >> 1;
    if (ls[rt]) mn[rt] = min(mn[rt], mn[ls[rt]] - tag[rt]);
    else mn[rt] = min(mn[rt], get(l, mid) - tag[rt]);
    if (rs[rt]) mn[rt] = min(mn[rt], mn[rs[rt]] - tag[rt]);
    else mn[rt] = min(mn[rt], get(mid + 1, r) - tag[rt]);
}

void update(int &rt, int l, int r, int start, int end) {
    if (!rt) rt = apply(), mn[rt] = get(l, r);
    if (start <= l && r <= end) return tag[rt] += 2, mn[rt] -= 2, void();
    int mid = (l + r) >> 1;
    if (start <= mid) update(ls[rt], l, mid, start, end);
    if (end > mid) update(rs[rt], mid + 1, r, start, end);
    pushup(rt, l, r);
}

void del(int rt) {
    if (!rt) return;
    pool.push_back(rt), del(ls[rt]), del(rs[rt]);
}

int query(int rt, int l, int r, int start, int end) {
    if (start > end) return 1e9;
    if (!rt) return get(max(l, start), min(r, end));
    if (start <= l && r <= end) return mn[rt];
    int mid = (l + r) >> 1, res = 1e9;
    if (start <= mid) res = min(res, query(ls[rt], l, mid, start, end));
    if (end > mid) res = min(res, query(rs[rt], mid + 1, r, start, end));
    return res - tag[rt]; 
}

void merge(int &x, int y, int l, int r) {
    if (!x || !y) return x |= y, void();
    tag[x] += tag[y];
    if (l == r) return mn[x] -= tag[y], void();
    int mid = (l + r) >> 1;
    merge(ls[x], ls[y], l, mid), merge(rs[x], rs[y], mid + 1, r), pushup(x, l, r), pool.push_back(y);
}

void update(int &rt, int x) {
    while (top[x]) update(rt, 1, n, dfn[top[x]], dfn[x]), x = fa[top[x]];
}

int rt[N], ans[N], fuck[N]; vector<int> G[N];

void dfs2(int u, int f) {
    ans[u] = 1e9;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            int v = e[i].to;
            dfs2(v, u), merge(rt[u], rt[v], 1, n);
            ans[v] = min(ans[v], ct[u] - ct[v] + 2), ans[u] = min(ans[u], ct[u] - ct[v] + 2);
        }
    for (auto v : G[u]) update(rt[u], v);
    ans[u] = min(ans[u], 2 + ct[u] + min(query(rt[u], 1, n, 1, dfn[u] - 1), query(rt[u], 1, n, ed[u] + 1, n)));
}

int main() {
//    freopen("ex_B2.in", "r", stdin);
    int m; scanf("%d%d", &n, &m);
    for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), adde(a, b);
    for (int i = 1, a, b; i <= m - n + 1; i++) 
        scanf("%d%d", &a, &b), G[a].push_back(b), G[b].push_back(a), ct[a]++, ct[b]++;
    dfs(1, 0), dfs1(1, 1), pre();
    for (int i = head[1]; i; i = e[i].next)
        dfs2(e[i].to, 1), del(rt[e[i].to]);
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i; i = e[i].next)
            if (dep[e[i].to] > dep[u]) 
                fuck[(i + 1) / 2] = ans[e[i].to];
    for (int i = 1; i < n; i++) printf("%d ", fuck[i]);
}
