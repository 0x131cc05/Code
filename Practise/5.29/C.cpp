#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

struct edge { int to; LL w; };
vector<edge> in[N], out[N];

void adde(int from, int to, int w) {
    in[to].push_back({ from, w }), out[from].push_back({ to, w });
}

LL dis[N]; int vis[N], pre[N];

void dijkstra(int s) {
    memset(dis, 0x3f, sizeof(dis)), dis[s] = 0;
    priority_queue<pair<LL, int>> q; q.push(make_pair(0, s));
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto t : out[u]) {
            if (dis[u] + t.w < dis[t.to]) {
                dis[t.to] = dis[u] + t.w, pre[t.to] = u;
                q.push(make_pair(-dis[t.to], t.to));
            }
        }
    }
}

vector<int> G[N];

LL ans[N];

int mid, ct;

void dfs(int u, int f) {
    ct++; if (ct == mid) return;
    for (auto v : G[u]) if (v != f && !vis[v]) {
        dfs(v, u);
        if (ct == mid) return;
    }
}

bool cmp(int a, int b) {
    if (!a) return 1;
    for (int s = 1; s; s <<= 1) {
        mid = s, ct = 0, dfs(a, 0); int A = ct;
        mid = s, ct = 0, dfs(b, 0); int B = ct;
        if (A != s || B != s) return A < B;
    }
}

int col[N], tot;

void dfs1(int u, int f) {
    col[u] = tot;
    for (auto v : G[u]) if (v != f && !vis[v]) 
        dfs1(v, u);
}

priority_queue<pair<LL, int>> q;

int rt;

void upd(int u, int f) {
    for (auto t : out[u]) if (col[t.to] != col[u] && !vis[t.to]) {
        if (ans[rt] + t.w < ans[t.to]) {
            ans[t.to] = ans[rt] + t.w, q.push({-ans[t.to], t.to});
        }
    }
    bool flag = false;
    for (auto t : in[u]) if (col[t.to] != col[u] && !vis[t.to]) {
        if (ans[rt] + t.w < ans[u]) {
            ans[u] = ans[rt] + t.w, flag = true;
        }
    }
    if (flag) q.push({-ans[u], u});
    for (auto v : G[u]) if (v != f && !vis[v]) upd(v, u);
}

int fuck[N];

void divide(int u) {
    rt = u, vis[u] = 1; int lst = 0;
    for (auto v : G[u]) if (!vis[v]) {
        fuck[v] = u;
        if (cmp(lst, v)) { 
            if (lst) tot++, dfs1(lst, u), upd(lst, u);
            lst = v; continue; 
        }
        tot++, dfs1(v, u), upd(v, u);
    }
    for (auto v : out[u]) if (!vis[v.to] && pre[v.to] != u) {
        if (ans[u] + v.w < ans[v.to]) {
            ans[v.to] = ans[u] + v.w;
            q.push({-ans[v.to], v.to});
        }
        
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, d; scanf("%d%d%d", &u, &v, &d);
        adde(u, v, d);
    }
    dijkstra(1), memset(vis, 0, sizeof(vis)), memset(ans, 0x3f, sizeof(ans)), ans[1] = 0;
    for (int i = 2; i <= n; i++) if (pre[i]) 
        G[pre[i]].push_back(i), G[i].push_back(pre[i]);
    for (int i = 1; i <= n; i++) {
        for (auto &t : out[i]) 
            t.w = t.w - (dis[t.to] - dis[i]);
        for (auto &t : in[i]) 
            t.w = t.w - (dis[i] - dis[t.to]);
    }
    q.push({ 0, 1 });
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        divide(u);
    }
    for (int i = 2; i <= n; i++) {
        if (ans[i] > 1e16) puts("-1");
        else printf("%lld\n", 2 * dis[i] + ans[i]);
    }
}