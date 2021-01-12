#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int M = 100;
const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int frac[N], inv[N];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int dp[2][N], mark[N], a, m;

void dfs(int u, int f) {
    dp[0][u] = 1;
    if (!mark[u]) dp[1][u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u);
            int A = dp[0][u], B = dp[1][u];
            dp[0][u] = (LL)A * dp[1][e[i].to] % mod * a % mod;
            dp[0][u] = (dp[0][u] + (LL)A * dp[0][e[i].to] % mod * (m - a - 1)) % mod;
            dp[1][u] = (LL)B * dp[0][e[i].to] % mod * (m - a) % mod;
            dp[1][u] = (dp[1][u] + (LL)B * dp[1][e[i].to] % mod * (a - 1)) % mod;
        }
}

int f[M], g[M], S[M][M];

int main() {
//    freopen("A.in", "r", stdin);
    int n, k, t; scanf("%d%d%d%d", &n, &m, &k, &t);
    for (int i = 1, a; i <= t; i++) scanf("%d", &a), mark[a] = 1;
    for (int i = 1, a, b; i < n; i++) 
        scanf("%d%d", &a, &b), adde(a, b);
    frac[0] = inv[0] = S[0][0] = 1;
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= i; j++)
            S[i][j] = (S[i - 1][j - 1] + (LL)S[i - 1][j] * j) % mod;
    for (int i = 1; i <= max(n, m); i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 0; i <= k; i++) 
        ::a = i, dfs(1, 0), f[i] = ((LL)dp[1][1] * i + (LL)dp[0][1] * (m - i)) % mod;
    for (int i = 0; i <= k; i++) {
        int res = 0;
        for (int j = 0; j <= i; j++) {
            int w = (LL)f[j] * C(i, j) % mod;
            if (j & 1) res = (res + mod - w) % mod;
            else res = (res + w) % mod;
        }
        g[i] = (LL)res * C(m, i) % mod;
    }
    int res = 0;
    for (int i = 0; i <= k; i++) 
        res = (res + (LL)g[i] * S[k][i] % mod * frac[i]) % mod;
    printf("%d\n", res);
}
