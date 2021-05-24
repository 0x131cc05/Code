#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int use[N * N * 2], n, m, vis[N][N], id[2][N][N], ncnt; char G[N][N];

int nxt[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

void dfs(int x, int y, int &ct, char c) {
    if (x < 1 || y < 1 || x > n || y > m || G[x][y] != c || vis[x][y]) return;
    vis[x][y] = 1, ct++;
    for (int i = 0; i < 4; i++) 
        dfs(x + nxt[i][0], y + nxt[i][1], ct, c);
    if (!use[id[0][x][y]]) dfs(x + 1, y + 1, ct, c);
    if (!use[id[0][x - 1][y - 1]]) dfs(x - 1, y - 1, ct, c);
    if (!use[id[1][x - 1][y]]) dfs(x - 1, y + 1, ct, c);
    if (!use[id[1][x][y - 1]]) dfs(x + 1, y - 1, ct, c);
}

bool check1() {
    use[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) vis[i][j] = 0;
    int ctA = 0, ctB = 0, flgA = 0, totA = 0, totB = 0, flgB = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (G[i][j] == 'A' && !flgA) 
                dfs(i, j, ctA, 'A'), flgA = 1;
            if (G[i][j] == 'B' && !flgB)
                dfs(i, j, ctB, 'B'), flgB = 1;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (G[i][j] == 'A') totA++;
            else if (G[i][j] == 'B') totB++;
    return ctA == totA && ctB == totB;
}

bool check2() {
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++) 
            if (use[id[0][i][j]] && use[id[1][i][j]]) return false;
    return true;
}

vector<int> ed[N * N * 2];

void inter() {
    while (233) {
        int s = ncnt + 1, t = ncnt + 2;
        for (int i = 1; i <= ncnt + 2; i++) ed[i].clear();
        for (int i = 1; i <= ncnt; i++) if (use[i])
            for (int j = 1; j <= ncnt; j++) if (!use[j]) {
                use[i] = 0, use[j] = 1;
                if (check1()) ed[i].push_back(j);
                if (check2()) ed[j].push_back(i);
                use[i] = 1, use[j] = 0;
            } 
        for (int i = 1; i <= ncnt; i++) if (!use[i]) {
            use[i] = 1;
            if (check1()) ed[s].push_back(i);
            if (check2()) ed[i].push_back(t);
            use[i] = 0;
        }
        vector<int> vis(ncnt + 3), lst(ncnt + 3), dis(ncnt + 3, -1e9);
        queue<int> q; q.push(s), dis[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for (auto v : ed[u]) {
                int c = v <= ncnt ? (use[v] ? -1 : 1) : 0;
                if (dis[v] < dis[u] + c) {
                    dis[v] = dis[u] + c, lst[v] = u;
                    if (!vis[v]) q.push(v), vis[v] = 1;
                }
            }
        }
        if (!lst[t]) return;
        int pos = t;
        while (pos) {
            if (pos <= ncnt) use[pos] ^= 1;
            pos = lst[pos];
        }
    }
}

int main() {
    int T; scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%d%d", &n, &m), ncnt = 0;
        for (int i = 1; i <= n; i++) scanf("%s", G[i] + 1);
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
                id[0][i][j] = ++ncnt, id[1][i][j] = ++ncnt;
        for (int i = 1; i <= ncnt; i++) use[i] = 0;
        inter(); int ct = 0;
        for (int i = 1; i <= ncnt; i++) if (use[i]) ct++;
        if (ct != ncnt / 2) printf("Case #%d: IMPOSSIBLE\n", t);
        else {
            printf("Case #%d: POSSIBLE\n", t);
            for (int i = 1; i < n; i++, puts(""))
                for (int j = 1; j < m; j++) {
                    int t = use[id[0][i][j]];
                    if (t) {
                        if (G[i][j] != G[i + 1][j + 1]) putchar('.');
                        else putchar('\\');
                    } else {
                        if (G[i + 1][j] != G[i][j + 1]) putchar('.');
                        else putchar('/');
                    }
                }
        }
    }
}