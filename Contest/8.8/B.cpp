#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int M = 520010;

typedef long long LL;

namespace Flow {
    struct edge {
        int to, next, w, c;
    } e[M];
    int head[N], ecnt = 1;
    void adde(int from, int to, int f, int c) {
        e[++ecnt] = (edge){ to, head[from], f, c }, head[from] = ecnt;
        e[++ecnt] = (edge){ from, head[to], 0, -c }, head[to] = ecnt;
    }
    int dis[N], vis[N];
    bool SPFA(int s, int t) {
        memset(dis, 0x3f, sizeof(dis)), dis[t] = 0;
        memset(vis, 0, sizeof(vis)), vis[t] = 1; queue<int> q; q.push(t);
        while (!q.empty()) {
            int u = q.front(); q.pop(), vis[u] = 0;
            for (int i = head[u]; i; i = e[i].next)
                if (e[i ^ 1].w && dis[e[i].to] + e[i].c > dis[u]) {
                    dis[e[i].to] = dis[u] - e[i].c;
                    if (!vis[e[i].to]) q.push(e[i].to), vis[e[i].to] = 1;
                }
        }
        return dis[s] <= 1e7;
    }
    LL MCMF;
    int DFS(int u, int t) {
        if (u == t || vis[u]) return !vis[u];
        // cout << u << endl;
        vis[u] = 1; int res = 0;
        for (int i = head[u]; i; i = e[i].next)
            if (e[i].w && dis[u] == dis[e[i].to] + e[i].c && DFS(e[i].to, t)) {
                MCMF += e[i].c, e[i].w--, e[i ^ 1].w++, vis[u] = 0;
                return 1;
            }
        // vis[u] = 0;
        return 0;
    }
}

LL flow[N];

int main() {
    int n, q; scanf("%*d%d%d", &n, &q);
    int s = n * 2 + 1, t = s + 1;
    for (int i = 1; i <= n; i++) {
        static int out[N], id[N];
        for (int j = 1; j <= n; j++) id[j] = j, scanf("%d", &out[j]);
        sort(id + 1, id + n + 1, [](int a, int b) { return out[a] > out[b]; }); 
        for (int j = 1; j <= min(n, 50); j++) // Yusland
            Flow::adde(i, id[j] + n, 1, -out[id[j]]);
    }
    for (int i = 1; i <= n; i++)
        Flow::adde(s, i, 1, 0), Flow::adde(i + n, t, 1, 0);
    int cur = 0;
    while (Flow::SPFA(s, t)) 
        while (Flow::DFS(s, t)) 
            cur++, flow[cur] = -Flow::MCMF, memset(Flow::vis, 0, sizeof(Flow::vis));
    while (q--) {
        int c; scanf("%d", &c);
        printf("%lld.0\n", flow[min(c, n)]);
    }
}