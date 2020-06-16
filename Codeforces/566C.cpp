#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

int sz[N], vis[N];

int Getsz(int u) {
    sz[u] = vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) sz[u] += Getsz(e[i].to);
    return vis[u] = 0, sz[u];
}

int Getrt(int u, int tot) {
    vis[u] = 1;
    for (int i = head[u], tmp; i; i = e[i].next)
        if (!vis[e[i].to] && (tmp = Getrt(e[i].to, tot)))
            return vis[u] = 0, tmp;
    return vis[u] = 0, sz[u] >= (tot >> 1) ? u : 0;
}

double sum[N], res;

int val[N];

void dfs(int u, int f, int t, int d) {
    sum[t] += 1.5 * sqrt(d) * val[u], res += pow(d, 1.5) * val[u];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u, t, d + e[i].w);
}

double ans = 1e20; int pos;

void Divide(int u) {
    u = Getrt(u, Getsz(u));
    if (vis[u] == 1) return;
    vis[u] = 1; double tot = 0; res = 0;
    for (int i = head[u]; i; i = e[i].next) 
        sum[e[i].to] = 0, dfs(e[i].to, u, e[i].to, e[i].w), tot += sum[e[i].to];
    if (res < ans) ans = res, pos = u;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to] && tot - 2 * sum[e[i].to] <= 0)
            Divide(e[i].to);
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
    for (int i = 1, a, b, c; i < n; i++) scanf("%d%d%d", &a, &b, &c), adde(a, b, c);
    Divide(1);
    printf("%d %.7lf\n", pos, ans);
}
