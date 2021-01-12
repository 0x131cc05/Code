#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int M = 6010;

typedef long long LL;

struct edge {
    int to, next, w, c;
} e[M];

int head[N], ecnt = 1, vis[N], cur[N]; LL dis[N];

inline void adde(int from, int to, int f, int c) {
    e[++ecnt] = (edge){to, head[from], f, c}, head[from] = ecnt;
    e[++ecnt] = (edge){from, head[to], 0, -c}, head[to] = ecnt;
}

inline bool SPFA(int s, int t) {
    memset(vis, 0, sizeof(vis)), memset(dis, 0x3f, sizeof(dis)), dis[t] = 0, vis[t] = 1;
    deque<int> q; q.push_back(t);
    while (!q.empty()) {
        int u = q.front(); q.pop_front(), vis[u] = 0;
        for (int i = head[u];i;i = e[i].next)
            if (e[i ^ 1].w && dis[e[i].to] > dis[u] - e[i].c) {
                dis[e[i].to] = dis[u] - e[i].c;
                if (!vis[e[i].to]) {
                    vis[e[i].to] = 1;
                    if (!q.empty() && dis[e[i].to] < dis[q.front()]) q.push_front(e[i].to);
                    else q.push_back(e[i].to);
                }
            }
    }
    return dis[s] < 1e17;
}

LL MCMF;

int DFS(int u, int f, int t) {
    vis[u] = 1; int res = 0;
    if (u == t || !f) return f;
    for (int &i = cur[u], tmp;i;i = e[i].next)
        if (!vis[e[i].to] && e[i].w && dis[u] - e[i].c == dis[e[i].to] && (tmp = DFS(e[i].to, min(f, e[i].w), t))) {
            f -= tmp, res += tmp, e[i].w -= tmp, e[i ^ 1].w += tmp, MCMF += (LL)tmp * e[i].c;
            if (!f) break;
        }
    return res;
}

inline LL Dinic(int s, int t) {
    MCMF = 0; int f = 0;
    while (SPFA(s, t)) memcpy(cur, head, sizeof(head)), f += DFS(s, 1e9, t);
    return f;
}

int from[M], to[M], w[M];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &from[i], &to[i], &w[i]);
    for (int i = 2; i <= n; i++) {
        ecnt = 1, memset(head, 0, sizeof(head)), MCMF = 0;
        for (int j = 1; j <= m; j++) adde(from[j], to[j], 1, w[j]);
        adde(n + 1, 1, 2, 0);
        LL res = Dinic(n + 1, i);
        if (res != 2) puts("-1");
        else printf("%lld\n", MCMF);
    }
}