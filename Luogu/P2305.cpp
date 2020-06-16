#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef long long LL;

struct edge {
    int to, next; LL w;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to, LL w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
} 

LL dis[N];

void dfs(int u, int f) {
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dis[e[i].to] = dis[u] + e[i].w, dfs(e[i].to, u);
}

LL dp[N], l[N], p[N], q[N];
// dp[v] + (dis[u] - dis[v]) * p[u] + q[u]

int sz[N], vis[N];

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

struct zjk {

LL dep; int u, type;

bool operator < (const zjk &b) const {
    if (dep != b.dep) return dep > b.dep;
    if (type != b.type) return type > b.type;
    return dp[u] < dp[b.u];
}

};

bool afs(int u, int rt, vector<zjk> &tmp) {
    if (u == rt) {
        tmp.push_back((zjk){ dis[u], u, 1 });
        return true;
    }
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to] && afs(e[i].to, rt, tmp)) 
            return vis[u] = 0, tmp.push_back((zjk){ dis[u], u, 1 }), true;
    return vis[u] = 0, false;
}

inline LL calc(int u, int v) {
    return dp[v] + (dis[u] - dis[v]) * p[u] + q[u];
}

void bfs(int u, vector<zjk> &tmp) {
    tmp.push_back((zjk){ l[u], u, 0 }), vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) bfs(e[i].to, tmp);
    vis[u] = 0;
} 

struct Line { LL k, b; };

inline LL calc(Line a, LL pos) {
    return a.b + a.k * pos;
}

inline bool calc(Line a, Line b, Line c) {
    return (double)(b.b - a.b) / (a.k - b.k) <= (double)(c.b - a.b) / (a.k - c.k);
}

void divide(int u, int rt) {
    u = getrt(u, getsz(u)), vis[u] = 1;
    int belong = u; vector<zjk> nw;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) {
            if (afs(e[i].to, rt, nw)) {
                divide(e[i].to, rt), belong = e[i].to; break;
            }
        } 
    if (belong != u) for (auto t : nw) 
        if (dis[t.u] >= l[u]) dp[u] = min(dp[u], calc(u, t.u)); 
    nw.push_back((zjk){ dis[u], u, 1 });
    for (int i = head[u]; i; i = e[i].next) 
        if (!vis[e[i].to] && e[i].to != belong) bfs(e[i].to, nw);
    sort(nw.begin(), nw.end());
    static Line stk[N]; int top = 0;
    for (auto t : nw) {
        if (t.type == 1) {
            Line a = (Line){ dis[t.u], dp[t.u] };
            if (top && stk[top].k == a.k) continue;
            while (top >= 2 && !calc(stk[top - 1], stk[top], a)) top--;
            stk[++top] = a;           
        } else {
            if (!top) continue;
            int l = 1, r = top - 1, pos = top, mid;
            while (l <= r) {
                mid = (l + r) >> 1;
                if (calc(stk[mid], -p[t.u]) <= calc(stk[mid + 1], -p[t.u])) pos = mid, r = mid - 1;
                else l = mid + 1;
            }
            dp[t.u] = min(dp[t.u], calc(stk[pos], -p[t.u]) + q[t.u] + dis[t.u] * p[t.u]);
        }
    }
        
    nw.clear();
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to] && e[i].to != belong) divide(e[i].to, e[i].to);
}

int main() {
//    freopen("ticket2.in", "r", stdin), freopen("out.out", "w", stdout);
    int n; scanf("%d%*d", &n);
    for (int i = 2, f; i <= n; i++) {
        LL w; scanf("%d%lld%lld%lld%lld", &f, &w, &p[i], &q[i], &l[i]);
        adde(f, i, w);
    }
    dfs(1, 0);
    for (int i = 2; i <= n; i++) dp[i] = 1e18;
    for (int i = 2; i <= n; i++) l[i] = dis[i] - l[i];
    divide(1, 1);
    for (int i = 2; i <= n; i++) printf("%lld\n", dp[i]); 
}

