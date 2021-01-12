#include <bits/stdc++.h>
using namespace std;

const int N = 2010;

typedef long long LL;

struct edge {
    int to, next, w, c;
} e[N * 10];

int head[N], ecnt = 1;

void adde(int from, int to, int w, int c) {
    e[++ecnt] = (edge){ to, head[from], w, c }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], 0, -c }, head[to] = ecnt;
}

int ind[N], vis[N];

LL tot, dis[N];

void adde(int from, int to, int l, int r, int c) {
    adde(from, to, r - l, c), tot += l * c, ind[to] += l, ind[from] -= l;
}

bool SPFA(int s, int t) {
    memset(vis, 0, sizeof(vis)), memset(dis, 0x3f, sizeof(dis)), dis[t] = 0, vis[t] = 1;
    queue<int> q; q.push(t);
    while (!q.empty()) {
        int u = q.front(); q.pop(), vis[u] = 0;
        for (int i = head[u]; i; i = e[i].next)
            if (e[i ^ 1].w && dis[e[i].to] > dis[u] - e[i].c) {
                dis[e[i].to] = dis[u] - e[i].c;
                if (!vis[e[i].to]) vis[e[i].to] = 1, q.push(e[i].to);
            }
    }
    return dis[s] < 1e17;
}

int DFS(int u, int f, int t) {
    vis[u] = 1; int res = 0;
    if (u == t || !f) return f;
    for (int i = head[u], tmp; i; i = e[i].next)
        if (!vis[e[i].to] && e[i].w && dis[u] - e[i].c == dis[e[i].to] && (tmp = DFS(e[i].to, min(f, e[i].w), t))) {
            f -= tmp, res += tmp, e[i].w -= tmp, e[i ^ 1].w += tmp, tot += tmp * e[i].c;
            if (!f) break;
        }
    return res;
}

int dinic(int s, int t) {
    int res = 0;
    while (SPFA(s, t)) res += DFS(s, 1e9, t);
    return res;
} 

int A[N], B[N], ed[N];

int main() {
    freopen("delight.in", "r", stdin), freopen("delight.out", "w", stdout);
    int n, k, a, b; LL offset = 0; scanf("%d%d%d%d", &n, &k, &a, &b), b = k - b;
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &B[i]), offset += B[i], A[i] -= B[i];
    for (int i = 1; i <= n; i++) 
        adde(i, min(n + 1, i + k), 0, 1, -A[i]), ed[i] = ecnt - 1;
    for (int i = 1; i <= n; i++) 
        if (i < k) adde(i, i + 1, 0, 1e9, 0);
        else adde(i, i + 1, k - b, k - a, 0);
    int s = n + 2, t = s + 1, s1 = t + 1, t1 = s1 + 1;
    adde(s, 1, k, k, 0), adde(n + 1, t, k, k, 0), adde(t, s, 0, 1e9, 0);
    for (int i = 1; i <= t; i++) 
        if (ind[i] > 0) adde(s1, i, ind[i], 0);
        else adde(i, t1, -ind[i], 0);
    dinic(s1, t1);
    printf("%lld\n", offset - tot);
    for (int i = 1; i <= n; i++) putchar(e[ed[i]].w ? 'E' : 'S');
}