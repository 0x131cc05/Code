#include <bits/stdc++.h>
using namespace std;

const int N = 20010;
const int M = 500010;

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

int MCMF;

int DFS(int u, int f, int t) {
    if (u == t || !f) return f;
    vis[u] = 1; int res = 0;
    for (int i = head[u], tmp; i; i = e[i].next)
        if (e[i].w && !vis[e[i].to] && dis[u] == dis[e[i].to] + e[i].c && (tmp = DFS(e[i].to, min(f, e[i].w), t))) {
            MCMF += e[i].c * tmp, e[i].w -= tmp, e[i ^ 1].w += tmp, res += tmp, f -= tmp;
            if (!f) break;
        }
    return res;
}

int dinic(int s, int t) {
    int res = 0;
    while (SPFA(s, t)) res += DFS(s, 1e9, t);
    return res;
} 

int D[110][110], R[110][110], n, m;

char G[110][110];

int id(int a, int b) {
    return (a - 1) * m + b;
}

string res;

void dfs(int i, int j) {
    if (i == n && j == m) { puts(res.c_str()); return; }
    if (D[i][j]) res += 'D', D[i][j]--, dfs(i + 1, j);
    else assert(R[i][j]), res += 'R', R[i][j]--, dfs(i, j + 1);
}

int main() {
    freopen("ioi.in", "r", stdin), freopen("ioi.out", "w", stdout);
    int k; scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) scanf("%s", G[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) if (G[i][j] != '#') {
            adde(id(i, j), id(i, j) + n * m, 1, -(G[i][j] - '0'));
            adde(id(i, j), id(i, j) + n * m, 1e9, 0);
            if (i != n && G[i + 1][j] != '#') {
                D[i][j] = ecnt + 1;
                adde(id(i, j) + n * m, id(i + 1, j), 1e9, 0);
            }
            if (j != m && G[i][j + 1] != '#') {
                R[i][j] = ecnt + 1;
                adde(id(i, j) + n * m, id(i, j + 1), 1e9, 0);
            }
        }
    int s = n * m * 2 + 1, t = s + 1;
    adde(s, id(1, 1), k, 0), adde(s - 1, t, k, 0);
    assert(dinic(s, t) == k);
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) if (G[i][j] != '#') {
            if (D[i][j]) D[i][j] = e[D[i][j] ^ 1].w;
            if (R[i][j]) R[i][j] = e[R[i][j] ^ 1].w;
        }
    for (int i = 1; i <= k; i++) res = "", dfs(1, 1);
}
