#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long LL;

int col[35][35], n, m, nxt[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

char G[35][35];

void dfs(int x, int y, int c, char t) {
    if (x <= 0 || y <= 0 || x > n || y > m || col[x][y] || G[x][y] != t) return;
    col[x][y] = c;
    for (int i = 0; i < 4; i++) 
        dfs(x + nxt[i][0], y + nxt[i][1], c, t);
}

int s, t; LL adj[65], ed[65];

set<LL> mp[2][65];

bool go(int u, LL vis, bool type) {
    if (u == t) return type;
    if (mp[type][u].count(vis)) return false;
    mp[type][u].insert(vis);
    LL go8 = (ed[u] ^ adj[u]) & ~vis;
    LL go4 = ed[u] & ~vis;
    for (int i = 1; i <= t; i++) if (go4 & (1ll << (i - 1))) 
        if (go(i, vis | ed[u], type | ((go8 >> (i - 1)) & 1))) return true;
    return false;
}

struct ConnectingGame {
    string isValid(vector<string> board) {
        n = board.size(), m = board[0].size();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                G[i][j] = board[i - 1][j - 1];
        int ncnt = 1; s = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) if (!col[i][j]) {
                dfs(i, j, ++ncnt, G[i][j]);
            }
        }
        t = ++ncnt;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                for (int x = -1; x <= 1; x++)
                    for (int y = -1; y <= 1; y++) {
                        int d = abs(x) + abs(y);
                        if (!d) continue;
                        int tx = i + x, ty = j + y, tar = -1;
                        if (ty == 0) tar = s;
                        else if (ty == m + 1) tar = t;
                        else if (1 <= tx && tx <= n && G[tx][ty] != G[i][j]) 
                            tar = col[tx][ty]; 
                        if (tar == -1) continue;
                        int u = col[i][j];
                        if (d == 1 || tar == s || tar == t) adj[u] |= 1ll << (tar - 1);
                        ed[u] |= 1ll << (tar - 1);
                        if (tar == s) adj[s] |= 1ll << (u - 1), ed[s] |= 1ll << (u - 1);
                    }
            }
        return go(s, 1ll << (s - 1), false) ? "invalid" : "valid";
    }
};

int main() {
    ConnectingGame solver;
    cout << solver.isValid(	{"ssssYNNNN4444ZZZZZZK0", "ssssBBNNNN4444Zvvvvvv"});
}
