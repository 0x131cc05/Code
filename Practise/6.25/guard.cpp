#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt, dfn[N], dfsn;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

int dep[N], fa[18][N], ed[N];

void dfs(int u, int f) {
    fa[0][u] = f, dep[u] = dep[f] + 1, dfn[u] = ++dfsn;
    for (int i = 1; i < 18; i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u);
    ed[u] = dfsn;
}

int LCA(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 17; i >= 0; i--) if (dep[fa[i][a]] >= dep[b]) a = fa[i][a];
    if (a == b) return a;
    for (int i = 17; i >= 0; i--) if (fa[i][a] != fa[i][b]) a = fa[i][a], b = fa[i][b];
    return fa[0][a];
}

int jump(int u, int d) {
    for (int i = 17; i >= 0; i--) if (d & (1 << i))
        u = fa[i][u];
    return u;
}

int getDis(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[LCA(u, v)];
}

int sz[N], vis[N];

int getSize(int u) {
    sz[u] = vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) sz[u] += getSize(e[i].to);
    return vis[u] = 0, sz[u];
}

int getRoot(int u, int tot) {
    vis[u] = 1;
    for (int i = head[u], tmp = 0; i; i = e[i].next)
        if (!vis[e[i].to] && (tmp = getRoot(e[i].to, tot))) 
            return vis[u] = 0, tmp;
    vis[u] = 0;
    if (sz[u] >= (tot >> 1)) return u;
    return 0;
}

vector<int> buk[N], buk1[N];

int dis[N], fuck[N], layer[N];

void divide(int u, int f) {
    u = getRoot(u, getSize(u)), vis[u] = 1;
    layer[u] = layer[f] + 1, fuck[u] = f;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) divide(e[i].to, u);
}

int wkr[N];

vector<int> G[N];

void dfs(int u) {
   if (!G[u].size()) return;
   for (auto v : G[u]) {
       dfs(v);
       int d = dep[v] - dep[u];
       wkr[u] = max(wkr[u], wkr[v] - d);
   } 
}

void dfs1(int u) {
    for (auto v : G[u]) {
        int d = dep[v] - dep[u];
        wkr[v] = max(wkr[v], wkr[u] - d), dfs1(v);
    }
}

int n;

int D[25][N];

void work() {
    int hh = (n + 1) / 2;
    for (int i = 1; i <= n; i++) {
        int cur = i, lst = 0;
        for (int j = layer[i]; j >= 1; j--, lst = cur, cur = fuck[cur]) {
            int d = getDis(cur, i);
            D[j][i] = d;
            if (i > hh) continue;
            if (buk[cur].size() <= d) buk[cur].resize(d + 1);
            buk[cur][d]++;
            if (lst) {
                if (buk1[lst].size() <= d) buk1[lst].resize(d + 1);
                buk1[lst][d]++;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < buk[i].size(); j++) buk[i][j] += buk[i][j - 1];
        for (int j = 1; j < buk1[i].size(); j++) buk1[i][j] += buk1[i][j - 1];
    }
}

int query(int u, int r) {
    int cur = u, lst = 0, ans = 0;
    for (int j = layer[u]; j >= 1; j--, lst = cur, cur = fuck[cur]) {
        int d = D[j][u];
        if (d <= r) {
            int t = min(r - d, (int)buk[cur].size() - 1);
            if (t >= 0) {
                ans += buk[cur][t];
                if (lst && buk1[lst].size()) ans -= buk1[lst][min(t, (int)buk1[lst].size() - 1)];
            }
        }
    }
    return ans;
}


int main() {
    // freopen("A7.in", "r", stdin), freopen("out.out", "w", stdout);
    freopen("guard.in", "r", stdin), freopen("guard.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++) 
        scanf("%d%d", &a, &b), adde(a, i + n), adde(b, i + n);
    n += n - 1;
    dfs(1, 0), divide(1, 0), work();
    int q; scanf("%d", &q);
    memset(wkr, -1, sizeof(wkr));
    while (q--) {
        vector<int> tmp;
        int k; scanf("%d", &k); LL ans = 0;
        for (int i = 1; i <= k; i++) {
            int a, b; scanf("%d%d", &a, &b), b *= 2;
            wkr[a] = b, tmp.push_back(a);
        } 
        sort(tmp.begin(), tmp.end(), [&](int a, int b) {
            return dfn[a] < dfn[b];
        });
        int n = tmp.size();
        for (int i = 1; i < n; i++) 
            tmp.push_back(LCA(tmp[i - 1], tmp[i]));
        tmp.push_back(1);
        sort(tmp.begin(), tmp.end(), [&](int a, int b) {
            return dfn[a] < dfn[b];
        });
        tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());
        static int stk[N]; int top = 0;
        stk[++top] = 1; 
        for (int i = 0; i < tmp.size(); i++) {
            int u = tmp[i];
            assert(u);
            while (!(dfn[stk[top]] <= dfn[u] && dfn[u] <= ed[stk[top]])) 
                top--;
            if (u != stk[top]) {
                G[stk[top]].push_back(u);
                stk[++top] = u;
            } 
        }
        dfs(1), dfs1(1);
        for (auto u : tmp) if (wkr[u] >= 0)
            ans += query(u, wkr[u]);
        for (auto u : tmp) for (auto v : G[u]) if (wkr[u] >= 0 && wkr[v] >= 0) {
            if (wkr[u] + wkr[v] >= dep[v] - dep[u]) {
                int mid = (wkr[v] - wkr[u] + dep[v] - dep[u]) / 2;
                int t = jump(v, mid);
                ans -= query(t, (wkr[u] + wkr[v] - dep[v] + dep[u]) / 2);
            }
        }
        for (auto t : tmp) wkr[t] = -1, G[t].clear();
        printf("%lld\n", ans);
    }
}