#include <bits/stdc++.h>
using namespace std;

const int N = 55;

typedef long long LL;
typedef pair<int, int> P;

vector<string> G;

int n, m;

int dis[2][N][N], nxt[][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
void BFS(int id, int x, int y) {
    memset(dis[id], 0x3f, sizeof(dis[id])), dis[id][x][y] = 0;
    queue<P> q; q.push(P(x, y));
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second; q.pop();
        for (int i = 0; i < 4; i++) {
            int tx = x + nxt[i][0], ty = y + nxt[i][1];
            if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
            if (G[tx - 1][ty - 1] == '#') continue;
            if (dis[id][tx][ty] > dis[id][x][y] + 1) 
                dis[id][tx][ty] = dis[id][x][y] + 1, q.push(P(tx, ty));
        }
    }
}

LL gcd(LL a, LL b) { 
    return b ? gcd(b, a % b) : a;    
}

struct MeetInTheMaze {
    string getExpected(vector<string> Maze) {
        G = Maze, n = G.size(), m = G[0].size();
        vector<P> L, F, R;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (G[i - 1][j - 1] == 'L') L.push_back(P(i, j));
                if (G[i - 1][j - 1] == 'F') F.push_back(P(i, j));
                if (G[i - 1][j - 1] == 'R') R.push_back(P(i, j));
            }
        LL res = 0;
        for (auto f : F) for (auto r : R) {
            BFS(0, f.first, f.second), BFS(1, r.first, r.second);
            static int dis[N][N], vis[N][N]; 
            priority_queue<pair<int, P>> q;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++) {
                    dis[i][j] = ::dis[0][i][j] + ::dis[1][i][j];
                    if (dis[i][j] > 1e8) continue;
                    q.push(make_pair(-dis[i][j], P(i, j))), vis[i][j] = 0;
                }
            while (!q.empty()) {
                int x = q.top().second.first, y = q.top().second.second; q.pop();
                if (vis[x][y]) continue;
                vis[x][y] = 1;
                for (int i = 0; i < 4; i++) {
                    int tx = x + nxt[i][0], ty = y + nxt[i][1];
                    if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
                    if (G[tx - 1][ty - 1] == '#') continue;
                    if (dis[x][y] + 1 < dis[tx][ty]) 
                        dis[tx][ty] = dis[x][y] + 1, q.push(make_pair(-dis[tx][ty], P(tx, ty)));
                }
            }
            for (auto l : L) {
                if (!vis[l.first][l.second]) return "";
                res += dis[l.first][l.second];
            }
        }
        LL all = (LL)L.size() * F.size() * R.size(), g = gcd(res, all);
        stringstream ss;
        ss << res / g << "/" << all / g;
        return ss.str();
    }
};

// int main() {
//     MeetInTheMaze solver;
//     cout << solver.getExpected({ "#.#....#...#.#", 
//   "#...#..#......", 
//   ".L#...#R#..#F.", 
//   "#...#......#..", 
//   "#......#.....#", 
//   ".R.....F....L.", 
//   "##..#.......#.", 
//   "#........##...", 
//   ".F...##L#..#R#" });
// }