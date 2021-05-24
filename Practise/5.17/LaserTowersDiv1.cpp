#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
const int M = 100010;

typedef long long LL;

struct edge {
    int to, next, w;
} e[M * 2];

int head[N], ecnt = 1;

void adde(int from, int to, int w) {
    e[++ecnt] = { to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = { from, head[to], 0 }, head[to] = ecnt;
}

int dep[N];

bool BFS(int s, int t) {
    memset(dep, -1, sizeof(dep)), dep[s] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next)
            if (dep[e[i].to] == -1 && e[i].w) {
                dep[e[i].to] = dep[u] + 1, q.push(e[i].to);
                if (e[i].to == t) return true;
            }
    }
    return false;
}

int cur[N];

int DFS(int u, int f, int t) {
    if (u == t || !f) return f;
    int res = 0;
    for (int &i = cur[u], tmp; i; i = e[i].next)
        if (e[i].w && dep[e[i].to] == dep[u] + 1 && (tmp = DFS(e[i].to, min(f, e[i].w), t))) {
            res += tmp, f -= tmp, e[i].w -= tmp, e[i ^ 1].w += tmp;
            if (!f) break;
        }
    return res;
}

int dinic(int s, int t) {
    int res = 0;
    while (BFS(s, t)) memcpy(cur, head, sizeof(cur)), res += DFS(s, 1e9, t);
    return res;
}

int id[51][51][51], ncnt, nxt[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int trans[255];

struct LaserTowersDiv1 {
    int countMaxEnemies(vector<string> G) {
        trans['A'] = 0, trans['V'] = 1, trans['<'] = 2, trans['>'] = 3;
        int n = G.size(), m = G[0].size();
        int S = ++ncnt, T = ++ncnt, tot = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (!isdigit(G[i - 1][j - 1]) && G[i - 1][j - 1] != '.') {
                    int t = trans[(int)G[i - 1][j - 1]]; tot += 9;
                    id[i][j][0] = ++ncnt;
                    if (t < 2) adde(S, ncnt, 1e9);
                    else adde(ncnt, T, 1e9);
                    int tx = i, ty = j, cur = 0, mx = 0;
                    while (233) {
                        tx += nxt[t][0], ty += nxt[t][1], cur++;
                        if (tx < 1 || ty < 1 || tx > n || ty > m) break;
                        id[i][j][cur] = ++ncnt;
                        if (t < 2) adde(ncnt - 1, ncnt, 9 - mx);
                        else adde(ncnt, ncnt - 1, 9 - mx);
                        if (isdigit(G[tx - 1][ty - 1])) mx = max(mx, G[tx - 1][ty - 1] - '0');
                    }
                    if (t < 2) adde(ncnt, T, 9 - mx);
                    else adde(S, ncnt, 9 - mx);
                }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) 
                if (!isdigit(G[i - 1][j - 1]) && G[i - 1][j - 1] != '.' && trans[(int)G[i - 1][j - 1]] < 2) {
                    char A = G[i - 1][j - 1];
                    for (int x = 1; x <= n; x++)
                        for (int y = 1; y <= m; y++)
                            if (trans[(int)G[x - 1][y - 1]] >= 2) {
                                char B = G[x - 1][y - 1];
                                int d1 = abs(x - i), d2 = abs(j - y);
                                if (i + nxt[trans[(int)A]][0] * d1 != x || y + nxt[trans[(int)B]][1] * d2 != j) continue; 
                                assert(d1 > 0 && d2 > 0);
                                adde(id[i][j][d1], id[x][y][d2], 1e9);
                            } 
                }
        return tot - dinic(S, T);
    }
};

// int main() {
//     LaserTowersDiv1 solver;
//     printf("%d\n", solver.countMaxEnemies(	
// {
// "..V..",
// ">.54.",
// ".>3.6",
// "9..A."
// }));
// }