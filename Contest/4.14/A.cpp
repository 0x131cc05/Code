#include <bits/stdc++.h>
using namespace std;

const int N = 2510;
const int mod = 1e9 + 7;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to, int w) {
    e[++ecnt] = (edge){to, head[from], w}, head[from] = ecnt;
    e[++ecnt] = (edge){from, head[to], w}, head[to] = ecnt;
}

int sz[N], n, m, res;

int C[N][N], T[N][N], pw[N][N];

void dfs(int u, int f) {
    sz[u] = 1; 
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u); int r = sz[e[i].to], tmp = 0, h = (LL)pw[r][m] * pw[n - r][m] % mod;
            for (int i = 0; i <= m; i++) {
                int t = (LL)pw[r][i] * pw[n - r][m - i] % mod * C[m][i] % mod;
                int t1 = (LL)pw[r][m - i] * pw[n - r][i] % mod * C[m][i] % mod;
                tmp = (tmp + (LL)t * T[r][i] + (LL)t1 * T[n - r][i]) % mod;
                tmp = (tmp - (LL)h * C[m][i] % mod * C[m][i] % mod * i) % mod;
            }
            tmp = (tmp + mod) % mod;
            res = (res + (LL)e[i].w * 2 * tmp) % mod;
            sz[u] += r;
        }
}

inline void pre() {
    for (int i = 0; i <= m; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
            if (C[i][j] >= mod) C[i][j] -= mod;
        }
    }
    for (int i = 1; i <= n; i++) {
        pw[i][0] = 1, pw[i][1] = i;
        for (int j = 2; j <= m; j++) pw[i][j] = (LL)pw[i][j - 1] * i % mod;
    }
    for (int i = 1; i < n; i++)
        for (int j = 0; j <= m; j++) {
            if (j) T[i][j] = T[i][j - 1];
            T[i][j] = (T[i][j] + (LL)pw[i][m - j] * pw[n - i][j] % mod * C[m][j] % mod * j) % mod;
        }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, a, b, c; i < n; i++) scanf("%d%d%d", &a, &b, &c), adde(a, b, c);
    pre(), dfs(1, 0), printf("%d\n", res);
    return 0;
}