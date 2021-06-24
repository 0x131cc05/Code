#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

typedef unsigned long long LL; 

int v[N];

struct edge {
    int to, next; LL w;
} e[N * N * 4];

int head[N], ecnt;

inline void adde(int from, int to, LL w) {
    // cout << "adde: " << from << ' ' << to << ' ' << w << endl;
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], 0 }, head[to] = ecnt;
}

int dep[N], cur[N], n;

inline bool BFS(int s, int t) {
    memset(dep, -1, sizeof(dep)), dep[s] = 0; queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next)
            if (e[i].w && dep[e[i].to] == -1) {
                dep[e[i].to] = dep[u] + 1, q.push(e[i].to);
                if (e[i].to == t) return true;
            }
    }
    return false;
}

LL DFS(int u, LL f, int t) {
    if (u == t || !f) return f;
    LL res = 0, tmp;
    for (int &i = cur[u]; i; i = e[i].next)
        if (e[i].w && dep[e[i].to] == dep[u] + 1 && (tmp = DFS(e[i].to, min(f, e[i].w), t))) {
            res += tmp, f -= tmp, e[i].w -= tmp, e[i ^ 1].w += tmp;
            if (!f) break;
        }
    return res;
}

inline LL dinic(int s, int t) {
    LL res = 0;
    while (BFS(s, t)) memcpy(cur, head, sizeof(head)), res += DFS(s, 1e18, t);
    return res;
}

inline void reset() {
    ecnt = 1, memset(head, 0, sizeof(head));
}

LL ans; vector<int> G[N]; // u <= v => u 向 v 连边

inline long long calc(int v, int x) {
    return (long long)(v - x) * (v - x);
}

int vis[N];

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].w) dfs(e[i].to);
}

void solve(vector<int> p, int l, int r) {
    if (p.empty()) return;
    // cout << "solve: " << l << ' ' << r << endl;
    // for (auto t : p) cout << t << ' ';
    // cout << endl;
    if (l == r) {
        for (auto t : p) ans += calc(v[t], l);
        return;
    }
    int mid = (l + r - 1) >> 1; reset();
    static int tmp[N]; memset(tmp, 0, sizeof(tmp));
    for (auto t : p) tmp[t] = 1;
    int s = n + 1, t = n + 2;
    for (auto u : p) {
        long long w = calc(v[u], mid + 1) - calc(v[u], mid);  
        // cout << u << ' ' << v[u] << ' ' << mid << endl;
        if (w > 0) adde(u, t, w); else adde(s, u, -w);
        for (auto v : G[u]) if (tmp[v]) 
            adde(u, v, 1e18);
    }
    LL hh = dinic(s, t); vector<int> L, R;
    // cout << "flow: " << hh << endl;
    memset(vis, 0, sizeof(vis));
    dfs(s);
    // for (auto u : p) cout << vis[u] << ' ';
    // cout << endl;
    for (auto u : p) 
        if (vis[u]) R.push_back(u);
        else L.push_back(u); 
    solve(L, l, mid), solve(R, mid + 1, r);
}

LL base[64];

inline void insert(LL x) {
    for (int i = 63; i >= 0; i--) if (x >> i & 1) {
        if (base[i]) x ^= base[i];
        else {
            for (int j = 63; j > i; j--) if (base[j] >> i & 1)
                base[j] ^= x;
            return base[i] = x, void();
        }
    }
}

inline bool test(LL x) {
    for (int i = 63; i >= 0; i--) if (x >> i & 1) 
        if (base[i]) x ^= base[i];
        else return true;
    return false;
}

LL c[N]; int A[N], B[N], t[N];

int main() {
    int m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%llu", &c[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &A[i]), t[A[i]] |= 1;
    for (int i = 1; i <= m; i++) scanf("%d", &B[i]), t[B[i]] |= 2;
    for (int i = 1; i <= m; i++) {
        memset(base, 0, sizeof(base));
        for (int j = 1; j <= m; j++) if (j != i) insert(c[A[j]]);
        for (int j = 1; j <= n; j++) if (!(t[j] & 1)) 
            if (test(c[j])) G[A[i]].push_back(j);
    }
    for (int i = 1; i <= m; i++) {
        memset(base, 0, sizeof(base));
        for (int j = 1; j <= m; j++) if (j != i) insert(c[B[j]]);
        for (int j = 1; j <= n; j++) if (!(t[j] & 2)) 
            if (test(c[j])) G[j].push_back(B[i]);
    }
    // for (int i = 1; i <= n; i++)
    //     for (auto j : G[i]) cout << i << " <= " << j << endl;
    vector<int> base;
    for (int i = 1; i <= n; i++) base.push_back(i);
    solve(base, 0, 1e9);
    printf("%llu\n", ans);
}