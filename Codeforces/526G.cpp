#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt, n;

inline void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

struct WEN {

int fa[N][18], len[N], son[N], dis[N], top[N], val[N];

void dfs(int u, int f, int w) {
    fa[u][0] = f, dis[u] = dis[f] + w, val[u] = w;
    for (int i = 1; i <= 17; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u, e[i].w);
            if (len[e[i].to] > len[u]) 
                son[u] = e[i].to, len[u] = len[son[u]];
        }
    len[u] += w;
}

void dfs1(int u, int f, int t) {
    // cout << "dfs1: " << u << ' ' << f << ' ' << t << endl;
    top[u] = t;
    if (son[u]) dfs1(son[u], u, t);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && e[i].to != son[u]) dfs1(e[i].to, u, e[i].to);
}

int rk[N];

inline int jump(int u, int lim) { // rk[top[v]] <= lim
    for (int i = 17; i >= 0; i--)
        if (rk[top[fa[u][i]]] > lim) u = fa[u][i];
    return rk[top[u]] <= lim ? u : fa[u][0]; 
}

int id[N], sum[N], ct;

inline void pre(int rt) {
    dfs(rt, 0, 0), dfs1(rt, 0, rt), ct = 0;
    for (int i = 1; i <= n; i++) if (top[i] == i) id[++ct] = i;
    sort(id + 1, id + ct + 1, [&](int a, int b) {
        return len[a] > len[b];
    });
    for (int i = 1; i <= ct; i++) 
        rk[id[i]] = i, sum[i] = sum[i - 1] + len[id[i]];
}

inline int solve(int x, int y) {
    int t = min(ct, 2 * y - 1);
    if (rk[top[x]] <= t) return sum[t];
    int F = fa[top[x]][0], T = jump(F, t - 1), T1 = jump(F, t);
    int a = sum[t - 1] + len[top[x]] + dis[F] - dis[T];
    int b = sum[t] + dis[F] - dis[T1] - len[T1] + val[T1] + len[top[x]];
    // cout << a << ' ' << b << endl;
    return max(a, b);
}

} A, B;

int mx, p;

void dfs(int u, int f, int d) {
    if (d > mx) mx = d, p = u;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u, d + e[i].w);
}

int main() {
    int q; scanf("%d%d", &n, &q);
    for (int i = 1, a, b, c; i < n; i++) 
        scanf("%d%d%d", &a, &b, &c), adde(a, b, c);
    int rt1, rt2;
    dfs(1, 0, 0), rt1 = p, mx = 0, dfs(rt1, 0, 0), rt2 = p;
    // cout << rt1 << ' ' << rt2 << endl;
    A.pre(rt1), B.pre(rt2);
    int lastans = 0;
    while (q--) {
        int x, y; scanf("%d%d", &x, &y);
        x = (x + lastans - 1) % n + 1, y = (y + lastans - 1) % n + 1;
        // cout << x << ' ' << y << endl;
        printf("%d\n", lastans = max(A.solve(x, y), B.solve(x, y)));
    }
    return 0;
}


