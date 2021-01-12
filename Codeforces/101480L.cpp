#include <bits/stdc++.h>
using namespace std;

const int N = 110;

typedef pair<int, int> P;
typedef long long LL;

P pos[N][N];

int vis[N][N], nxt[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

char G[N][N];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%s", G[i]);
    queue<P> q; q.push(P(0, 0));
    bool type = false;
    int Dx = 0, Dy = 0;
    while (!q.empty()) {
        auto t = q.front(); q.pop();
        int x = t.first, y = t.second, px = (x % n + n) % n, py = (y % m + m) % m;
        if (!vis[px][py]) {
            vis[px][py] = 1, pos[px][py] = P(x, y);
            for (int i = 0; i < 4; i++) {
                int tx = x + nxt[i][0], ty = y + nxt[i][1], ptx = (tx % n + n) % n, pty = (ty % m + m) % m;
                if (G[ptx][pty] == '#') continue;
                if (type && vis[ptx][pty]) continue;
                q.push(P(tx, ty));
            }
        } else {
            int dx = x - pos[px][py].first, dy = y - pos[px][py].second;
            // cout << dx << ' ' << dy << endl;
            if (!Dx && !Dy) Dx = dx, Dy = dy;
            else if ((LL)dx * Dy != (LL)Dx * dy) type = true;
        }
    }
    int t; scanf("%d", &t);
    while (t--) {
        int x, y; scanf("%d%d", &x, &y);
        int px = (x % n + n) % n, py = (y % m + m) % m;
        if (!vis[px][py]) puts("no");
        else if (type) puts("yes");
        else {
            int dx = x - pos[px][py].first, dy = y - pos[px][py].second;
            puts((LL)dx * Dy == (LL)Dx * dy ? "yes" : "no"); 
        }
    }
}