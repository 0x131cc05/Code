#include <bits/stdc++.h>
using namespace std;

const int N = 50010;

int w[N], b[N];

int nxt[2][18][N];

inline int jump(int u, int type, int step) {
    for (int i = 17; i >= 0; i--) if (step & (1 << i))
        u = nxt[type][i][u];
    return u;
}

int to[2][810][N];

int main() {
    int n, q; scanf("%d%d", &n, &q); int sz = sqrt(n);
    for (int i = 1; i <= n; i++) 
        scanf("%d%d", &b[i], &w[i]), nxt[0][0][i] = b[i], nxt[1][0][i] = w[i];
    nxt[0][0][n + 1] = nxt[1][0][n + 1] = n + 1, nxt[0][0][n + 2] = nxt[1][0][n + 2] = n + 2;
    b[n + 1] = w[n + 1] = n + 1, b[n + 2] = w[n + 2] = n + 2;
    for (int i = 1; i <= 17; i++)
        for (int j = 1; j <= n + 2; j++) {
            nxt[0][i][j] = nxt[0][i - 1][nxt[0][i - 1][j]];
            nxt[1][i][j] = nxt[1][i - 1][nxt[1][i - 1][j]];
        }
    for (int i = 1; i <= sz; i++) to[0][i][n + 1] = to[1][i][n + 1] = n + 1, to[0][i][n + 2] = to[1][i][n + 2] = n + 2;
    for (int j = n; j >= 1; j--) {
        int A = b[j], B = w[j];
        for (int i = 1; i <= sz; i++) {
            to[0][i][j] = to[1][i][A], to[1][i][j] = to[0][i][B];
            A = b[A], B = w[B];
        }
    }
    while (q--) {
        int p, k, c; scanf("%d%d%d", &p, &k, &c);
        if (k <= sz) printf("%d\n", to[c][k][p] - n - 1);
        else {
            while (p != n + 1 && p != n + 2) 
                p = jump(p, c, k), c ^= 1;
            printf("%d\n", p - n - 1);
        }
    }
}
