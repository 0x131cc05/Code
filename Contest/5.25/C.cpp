#include <bits/stdc++.h>
using namespace std;

int G[6][6], n = 5;

bool flag = false;

int tx, ty;

void dfs(int x, int y, int step) {
    if (step == n * n) {
        if (x == tx && y == ty) {
//            cout << "find: " << tx << ' ' << ty << endl;
            flag = true;
        }
        return;
    }
    for (int i = -1; i <= 1; i++)
        for (int j = (i ? 0 : -1); j <= (i ? 0 : 1); j++) if (i || j) {
            int tx = x + i * 3, ty = y + j * 3;
            if (tx < 1 || ty < 1 || tx > n || ty > n) continue;
            if (G[tx][ty]) continue;
            G[tx][ty] = step + 1, dfs(tx, ty, step + 1);
            if (flag) return;
            G[tx][ty] = 0;
        }
    for (int i = -1; i <= 1; i += 2) 
        for (int j = -1; j <= 1; j += 2) {
            int tx = x + i * 2, ty = y + j * 2;
            if (tx < 1 || ty < 1 || tx > n || ty > n) continue;
            if (G[tx][ty]) continue;
            G[tx][ty] = step + 1, dfs(tx, ty, step + 1);
            if (flag) return;
            G[tx][ty] = 0;
        }
}

inline void clr() {
    memset(G, 0, sizeof(G)), flag = false;
}

const int N = 1010;

int ans[N][N];

int offset = 0;

inline void cpy(int x, int y) {
    for (int i = x + 1; i <= x + 5; i++)
        for (int j = y + 1; j <= y + 5; j++)
            ans[i][j] = G[i - x][j - y] + offset;
    offset += 25;
}

int main() {
    int n; scanf("%d", &n); int t = n / 5;
    G[1][1] = 1, tx = 3, ty = 3, dfs(1, 1, 1), cpy(0, 0), offset--, ans[3][3] = n * n;
    int x = 5, y = 3, cur = 1, X = 1, Y = 2, lst = 0;
    for (int i = 2; i <= t * t; i++) {
        if (lst|| (i <= t * (t - 1) && Y != t && (i == 2 || Y != 2)) || (i == t * (t - 1) + 1)) {
            clr(), G[x][y] = 1;
            if (cur == 1) tx = 5, ty = 5, dfs(x, y, 1), x = 5, y = 3, cpy((X - 1) * 5, (Y - 1) * 5);
            else tx = 5, ty = 1, dfs(x, y, 1), x = 5, y = 3, cpy((X - 1) * 5, (Y - 1) * 5);
            Y += cur, lst = 0;
        } else if (i <= t * (t - 1)){
            cur = -cur, clr(), G[x][y] = 1;
            tx = 5, ty = 5, dfs(x, y, 1), x = 3, y = 5, cpy((X - 1) * 5, (Y - 1) * 5);
            X++, lst = 1;
        } else {
            cur = -cur, clr(), G[x][y] = 1;
            tx = 1, ty = 3, dfs(x, y, 1), x = 3, y = 3, cpy((X - 1) * 5, (Y - 1) * 5);
            X--, lst = 0;
        }
    }
    for (int i = 1; i <= n; i++, puts(""))
        for (int j = 1; j <= n; j++) {
            printf("%d ", ans[i][j]);
        }
            
}
