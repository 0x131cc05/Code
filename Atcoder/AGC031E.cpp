#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 410;
const int M = 100010;

struct edge {
    int to, next, w; LL c;
} e[M];

int head[N], ecnt = 1, vis[N], cur[N]; LL dis[N];

inline void adde(int from, int to, int f, LL c) {
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
    for (int &i = cur[u], tmp; i; i = e[i].next)
        if (!vis[e[i].to] && e[i].w && dis[u] - e[i].c == dis[e[i].to] && (tmp = DFS(e[i].to, min(f, e[i].w), t))) {
            f -= tmp, res += tmp, e[i].w -= tmp, e[i ^ 1].w += tmp, MCMF += (LL)tmp * e[i].c;
            if (!f) break;
        }
    return res;
}

inline int Dinic(int s, int t) {
    MCMF = 0; int f = 0;
    while (SPFA(s, t)) memcpy(cur, head, sizeof(head)), f += DFS(s, 1e9, t);
    return f;
}

int x[N], y[N]; char s[N][5]; int a[N], b[N]; LL c[N];

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d%lld", &x[i], &y[i], &c[i]);
    int m; scanf("%d", &m);
    for (int i = 1; i <= m; i++) scanf("%s%d%d", s[i] + 1, &a[i], &b[i]);
    LL res = 0;
    for (int i = 1; i <= n; i++) {
        memset(head, 0, sizeof(head)), ecnt = 1;
        static int xl[N], xr[N], yl[N], yr[N]; 
        memset(xl, 0, sizeof(xl)), memset(yl, 0, sizeof(yl)), memset(xr, 0x3f, sizeof(xr)), memset(yr, 0x3f, sizeof(yr));
        for (int j = 1; j <= m; j++) if (b[j] < i) {
            if (s[j][1] == 'L') for (int k = b[j] + 1; k <= i; k++) xl[k] = max(xl[k], a[j] + 1);
            if (s[j][1] == 'R') for (int k = 1; k <= i - b[j]; k++) xr[k] = min(xr[k], a[j] - 1);
            if (s[j][1] == 'D') for (int k = b[j] + 1; k <= i; k++) yl[k] = max(yl[k], a[j] + 1);
            if (s[j][1] == 'U') for (int k = 1; k <= i - b[j]; k++) yr[k] = min(yr[k], a[j] - 1);
        }
        int s = 2 * n + 2 * i + 1, t = s + 1;
        for (int j = 1; j <= i; j++) adde(s, j, 1, 0), adde(j + i + 2 * n, t, 1, 0);
        for (int j = 1; j <= n; j++) adde(i + j, i + j + n, 1, -c[j]);
        for (int j = 1; j <= i; j++) 
            for (int k = 1; k <= n; k++) if (xl[j] <= x[k] && x[k] <= xr[j]) adde(j, k + i, 1, 0);
        for (int j = 1; j <= i; j++)
            for (int k = 1; k <= n; k++) if (yl[j] <= y[k] && y[k] <= yr[j]) adde(k + i + n, j + i + 2 * n, 1, 0);
        if (Dinic(s, t) == i) res = max(res, -MCMF);
    }
    printf("%lld\n", res);
}
