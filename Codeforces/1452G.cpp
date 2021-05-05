#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef pair<int, int> P;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

int dis[N], n;

void BFS() {
    queue<int> q; 
    for (int i = 1; i <= n; i++) if (!dis[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next)
            if (dis[e[i].to] == -1) dis[e[i].to] = dis[u] + 1, q.push(e[i].to);
    }
}

int ans[N], remain[N];

void dfs(int u, int f, int d, int t) {
    if (d <= remain[u] || t < dis[u]) return;
    if (ans[u] <= t) ans[u] = t;
    remain[u] = max(remain[u], d); 
    if (d <= 1) return;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && dis[e[i].to]) dfs(e[i].to, u, d - 1, t);
}

int main() {
    scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++) 
        scanf("%d%d", &a, &b), adde(a, b);
    int k; scanf("%d", &k);
    memset(dis, -1, sizeof(dis));
    for (int i = 1, a; i <= k; i++)
        scanf("%d", &a), dis[a] = 0;
    BFS(); vector<int> p;
    for (int i = 1; i <= n; i++) 
        p.push_back(i);
    sort(p.begin(), p.end(), [&](int a, int b) {
        return dis[a] > dis[b];
    });
    for (int i = 0; i < n; i++) dfs(p[i], 0, dis[p[i]], dis[p[i]]);
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
} 