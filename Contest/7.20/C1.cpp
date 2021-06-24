#include <bits/stdc++.h>
using namespace std;

const int N = 15010;
const int M = 120010;

struct edge {
    int to, next, w, c;
} e[M];

#define LL long long

int head[N], ecnt = 1, vis[N], cur[N]; LL dis[N];

inline void adde(int from, int to, int f, int c) {
//    cout << "adde: " << from << ' ' << to << ' ' << f << ' ' << c << endl;
    e[++ecnt] = (edge){to, head[from], f, c}, head[from] = ecnt;
    e[++ecnt] = (edge){from, head[to], 0, -c}, head[to] = ecnt;
}

inline bool SPFA(int s, int t) {
    memset(vis, 0, sizeof(vis)), memset(dis, 0x3f, sizeof(dis)), dis[t] = 0, vis[t] = 1;
    queue<int> q; q.push(t);
    while (!q.empty()) {
        int u = q.front(); q.pop(), vis[u] = 0;
        for (int i = head[u];i;i = e[i].next)
            if (e[i ^ 1].w && dis[e[i].to] > dis[u] - e[i].c) {
                dis[e[i].to] = dis[u] - e[i].c;
                if (!vis[e[i].to]) 
                    vis[e[i].to] = 1, q.push(e[i].to);
            }
    }
    return dis[s] < 1e17;
}

LL MCMF;

int DFS(int u, int f, int t) {
    int res = 0;
    if (u == t || !f) return f;
    vis[u] = 1; 
    for (int &i = cur[u], tmp;i;i = e[i].next)
        if (!vis[e[i].to] && e[i].w && dis[u] - e[i].c == dis[e[i].to] && (tmp = DFS(e[i].to, min(f, e[i].w), t))) {
            f -= tmp, res += tmp, e[i].w -= tmp, e[i ^ 1].w += tmp, MCMF += (LL)tmp * e[i].c;
            if (!f) break;
        }
    return res;
}

int ct;

inline LL Dinic(int s, int t) {
    MCMF = 0; int f = 0;
    while (SPFA(s, t)) memcpy(cur, head, sizeof(head)), f += DFS(s, 1e9, t);
//    cout << f << endl;
    return f == 2 * ct ? MCMF : 1;
}

int wkr[160][31]; int n, m, nxt[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}, s, t, v[160][31];

int ID(int x, int y) {
    return (x - 1) * m + y;
}

void dfs(int x, int y) {
    wkr[x][y] = -1;
    int tmp = ID(x, y), id = tmp + n * m * 2 + 1;
    if ((x + y) & 1) {
        adde(s, id, 2, 0), adde(id, tmp * 2, 1, 0), adde(id, tmp * 2, 1, -v[x][y]), ct++;
        adde(id, tmp * 2 + 1, 1, 0), adde(id, tmp * 2 + 1, 1, -v[x][y]);
    } else {
        adde(id, t, 2, 0), adde(tmp * 2, id, 1, 0), adde(tmp * 2, id, 1, -v[x][y]);
        adde(tmp * 2 + 1, id, 1, 0), adde(tmp * 2 + 1, id, 1, -v[x][y]);
    }
    for (int i = 0; i < 4; i++) {
        int tx = x + nxt[i][0], ty = y + nxt[i][1];
        if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
        if (wkr[tx][ty] == 1) continue;
        int nw = tmp * 2 + (i < 2), to = ID(tx, ty) * 2 + (i < 2);
        if ((x + y) & 1) adde(nw, to, 1, 0);
        if (wkr[tx][ty] != -1) dfs(tx, ty);
    }
}

int main() {
    scanf("%d%d", &n, &m), s = n * m * 3 + 2, t = s + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1, a; j <= m; j++) 
            scanf("%d", &a), wkr[i][j] = a;
    int sum = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) scanf("%d", &v[i][j]), sum += v[i][j] * (1 - wkr[i][j]);
//    cout << s << ' ' << t << endl;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) if (wkr[i][j] == 0) dfs(i, j);
    LL res = -Dinic(s, t);
    if (res == -1) return puts("-1"), 0;
    printf("%lld\n", res - sum);
}
