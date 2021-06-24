#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int M = 200010;

typedef pair<int, int> P;

int d1[N][M], d2[N][M], n;

struct G {
    struct edge { int to, next, id; } e[M];
    int head[N], ecnt, dis[N], vis[N];
    void adde(int from, int to, int id) {
        e[++ecnt] = { to, head[from], id }, head[from] = ecnt;
    }
    void Dijkstra(int s) {
        for (int i = s; i <= n; i++) dis[i] = vis[i] = 0;
        dis[s] = 1e9;
        priority_queue<P> q; q.push(P(dis[s], s));
        while (!q.empty()) {
            int u = q.top().second; q.pop();
            if (vis[u]) continue; vis[u] = 1;
            for (int i = head[u]; i; i = e[i].next)
                if (e[i].to > s && min(dis[u], e[i].id) > dis[e[i].to]) 
                    dis[e[i].to] = min(dis[u], e[i].id), q.push(P(dis[e[i].to], e[i].to));
        }
    }
} A, B;

int res[M];

int main() {
    int m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        A.adde(a, b, i), B.adde(b, a, i);
    }
    for (int i = 1; i <= n; i++) {
        A.Dijkstra(i), B.Dijkstra(i);
        for (int j = i; j <= n; j++) 
            res[min(m + 1, min(A.dis[j], B.dis[j]))]++;
    }
    for (int i = m + 1; i >= 1; i--) res[i] += res[i + 1];
    for (int i = 1; i <= m + 1; i++) printf("%d ", res[i]);
}


