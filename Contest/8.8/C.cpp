#include <bits/stdc++.h>
using namespace std;

const int N = 20010;

typedef long long LL;

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

LL dp1[2][N][110], dp2[2][2010][2010]; int sz[N], l, r;

void chk(LL &x, LL y) {
    if (y > x) x = y;
}

void dfs1(int u, int f) {
    dp1[0][u][0] = dp1[1][u][0] = 0, sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            int v = e[i].to; dfs1(v, u);
            for (int k = min(sz[u] / 2, r); k >= 0; k--) if (dp1[1][u][k] >= -1e13)
                for (int j = min(sz[v], r - k); j >= 0; j--) if (dp1[1][v][j] >= -1e13){
                    chk(dp1[0][u][k + j], dp1[0][u][k] + dp1[1][v][j]);
                    chk(dp1[1][u][k + j + 1], dp1[0][u][k] + dp1[0][v][j] + e[i].w);
                    chk(dp1[1][u][k + j], dp1[1][u][k] + dp1[1][v][j]);
                    chk(dp1[1][u][k + j], dp1[0][u][k + j]);
                }
            sz[u] += sz[v];
        }
}

void dfs2(int u, int f) {
    dp2[0][u][0] = dp2[1][u][0] = 0, sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            int v = e[i].to; dfs2(v, u);
            for (int k = sz[u] / 2; k >= 0; k--) if (dp2[1][u][k] >= -1e13)
                for (int j = sz[v] / 2; j >= 0; j--) if (dp2[1][v][j] >= -1e13) {
                    chk(dp2[0][u][k + j], dp2[0][u][k] + dp2[1][v][j]);
                    chk(dp2[1][u][k + j + 1], dp2[0][u][k] + dp2[0][v][j] + e[i].w);
                    chk(dp2[1][u][k + j], dp2[1][u][k] + dp2[1][v][j]);
                    chk(dp2[1][u][k + j], dp2[0][u][k + j]);
                }
            sz[u] += sz[v];
        }
}

int main() {
    int t, n; scanf("%d%d%d%d", &t, &n, &l, &r);
    for (int i = 1, a, b, c; i < n; i++)
        scanf("%d%d%d", &a, &b, &c), adde(a, b, c);
    if (n <= 2000) {
        memset(dp2, -0x3f, sizeof(dp2)), dfs2(1, 0);
        for (int i = l; i <= r; i++) {
            if (dp2[1][1][i] < -1e13) printf("- ");
            else printf("%lld ", dp2[1][1][i]);
        }
    } else {
        memset(dp1, -0x3f, sizeof(dp1)), dfs1(1, 0);
        for (int i = l; i <= r; i++) {
            if (dp1[1][1][i] < -1e13) printf("- ");
            else printf("%lld ", dp1[1][1][i]);
        }
    }
}