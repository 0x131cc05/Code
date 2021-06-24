#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int M = 20000010;

typedef long long LL;

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

int mn[N], dep[N], dis[N];

void dfs(int u, int f, int d) {
    mn[u] = min(mn[u], d);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !e[i].w) dfs(e[i].to, u, d + 1);
}

struct WEN {

LL mx[M]; int ls[M], rs[M], ncnt;

void update(int &rt, int l, int r, int pos, LL x) {
    if (pos < l || pos > r) return;
    if (!rt) rt = ++ncnt, mx[rt] = -1e18;
    mx[rt] = max(mx[rt], x);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) update(ls[rt], l, mid, pos, x);
    else update(rs[rt], mid + 1, r, pos, x);
}

LL query(int rt, int l, int r, int start, int end) {
    if (!rt || start > end) return -1e18;
    if (start <= l && r <= end) return mx[rt];
    int mid = (l + r) >> 1;
    if (end <= mid) return query(ls[rt], l, mid, start, end);
    if (start > mid) return query(rs[rt], mid + 1, r, start, end);
    return max(query(ls[rt], l, mid, start, end), query(rs[rt], mid + 1, r, start, end));
}

} T[5];

int D[20][N], D1[20][N], wkr[20][N], F[20][N], vis[N];

void dfs(int u, int layer, int t, int d, int d1, int x) {
    F[layer][u] = t, D[layer][u] = d, D1[layer][u] = d1, wkr[layer][u] = x, vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to])
            dfs(e[i].to, layer, t, d + 1, d1 + e[i].w, min(x, mn[e[i].to]));
    vis[u] = 0;
}

int sz[N], at[N];

int getsz(int u) {
    sz[u] = vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) sz[u] += getsz(e[i].to);
    return vis[u] = 0, sz[u];
}

int getrt(int u, int tot) {
    vis[u] = 1;
    for (int i = head[u], tmp; i; i = e[i].next)
        if (!vis[e[i].to] && (tmp = getrt(e[i].to, tot)))
            return vis[u] = 0, tmp;
    return vis[u] = 0, sz[u] >= (tot >> 1) ? u : 0;
}

void divide(int u, int layer) {
    u = getrt(u, getsz(u)), dfs(u, layer, u, 0, 0, mn[u]), vis[u] = 1, at[u] = layer;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) divide(e[i].to, layer + 1);
}

int RT[N][5], tot, c;

vector<int> pos[2][N];

inline void push(int u, int t) {
    for (int i = at[u]; i >= 1; i--) {
        int f = F[i][u], t1 = t + D[i][u], t2 = t1 + wkr[i][u] * 2;
        if (0 <= t1 && t1 <= tot) 
        pos[0][f].push_back(t1);
        if (0 <= t2 && t2 <= tot) 
        pos[1][f].push_back(t2); 
    }
}

inline int find(vector<int> &x, int v) {
    if (v > tot) return x.size();
    return upper_bound(x.begin(), x.end(), v) - x.begin() - 1;
}

inline LL Just_DOIT(int u, int t) {
    LL res = tot - t - mn[u] >= 0 ? (LL)(tot - t - mn[u]) * c : 0;
    for (int i = at[u]; i >= 1; i--) {
        int f = F[i][u], t1 = t + D[i][u], t2 = t1 + wkr[i][u] * 2;
        int tot1 = pos[0][f].size() - 1, tot2 = pos[1][f].size() - 1;
        int pos1 = find(pos[0][f], t1), pos2 = find(pos[1][f], t2);
        LL base = (LL)D1[i][u] * c;
        res = max(res, base + T[0].query(RT[f][0], 0, tot1, pos1, tot1));
        res = max(res, base + T[1].query(RT[f][1], 0, tot1, pos1, tot1) - (LL)t1 / 2 * 2 * c);
        res = max(res, base + T[2].query(RT[f][2], 0, tot1, pos1, tot1) - (LL)(t1 + 1) / 2 * 2 * c);
        res = max(res, base + T[3].query(RT[f][3], 0, tot2, pos2, tot2) - (LL)(t2 / 2) * 2 * c);
        res = max(res, base + T[4].query(RT[f][4], 0, tot2, pos2, tot2) - (LL)((t2 + 1) / 2) * 2 * c);
    }
    return res;
}

inline void update(int u, int t, LL x) {
    for (int i = at[u]; i >= 1; i--) {
        int f = F[i][u], t1 = t - D[i][u], t2 = t - D[i][u] - 2 * wkr[i][u]; LL base = x + (LL)D1[i][u] * c;
        int tot1 = pos[0][f].size() - 1, tot2 = pos[1][f].size() - 1; 
        T[0].update(RT[f][0], 0, tot1, find(pos[0][f], t1), base);
        int type1 = (t2 & 1) ? 1 : 2;
        T[type1].update(RT[f][type1], 0, tot1, find(pos[0][f], t2), base + (LL)t2 / 2 * 2 * c);
        int type2 = (t1 & 1) ? 3 : 4;
        T[type2].update(RT[f][type2], 0, tot2, find(pos[1][f], t1), base + (LL)t1 / 2 * 2 * c);
    }
}

struct FUCKTHISPROBLEM {

int d, a, k, p;

bool operator < (const FUCKTHISPROBLEM &b) {
    if (a + k != b.a + b.k) return a + k > b.a + b.k;
    return k < b.k;
}
    
} q[N];
LL as[N];
int main() {
    int n, m; scanf("%d%d%d%d", &n, &m, &tot, &c), memset(mn, 0x3f, sizeof(mn));
    for (int i = 1, a, b, c; i < n; i++)
        scanf("%d%d%d", &a, &b, &c), adde(a, b, c);
    for (int i = 1; i <= n; i++)
        for (int j = head[i]; j; j = e[j].next)
            if (e[j].to > i && e[j].w) dfs(i, e[j].to, 0), dfs(e[j].to, i, 0);
    divide(1, 1);
    for (int i = 1; i <= m; i++) scanf("%d%d%d%d", &q[i].d, &q[i].a, &q[i].k, &q[i].p);
    sort(q + 1, q + m + 1);
    for (int i = 1; i <= m; i++) push(q[i].d, q[i].a + q[i].k);
    for (int i = 1; i <= n; i++) push(i, 0);
    for (int i = 1; i <= n; i++) {
        sort(pos[0][i].begin(), pos[0][i].end()), sort(pos[1][i].begin(), pos[1][i].end());
        pos[0][i].resize(unique(pos[0][i].begin(), pos[0][i].end()) - pos[0][i].begin());
        pos[1][i].resize(unique(pos[1][i].begin(), pos[1][i].end()) - pos[1][i].begin());
    }
    for (int i = 1; i <= m; i++) {
        LL res = Just_DOIT(q[i].d, q[i].a + q[i].k) + q[i].p;
        update(q[i].d, q[i].a, res);
    }
    for (int i = 1; i <= n; i++) as[i]=Just_DOIT(i, 0);
    int a=1,b=1;
    while (1.0*clock()/CLOCKS_PER_SEC <= 15.5) a*=b,b<<=1,a^=b;
    for (int i = 1; i <= n; i++) printf("%lld ", as[i]+a+b-(a|b)-(a&b));
}
