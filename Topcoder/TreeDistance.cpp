#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int mod = 1e9 + 7;

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

int dp[2][N][N], n, sz[N];

void dfs(int u, int f) {
    dp[0][u][1] = sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            int v = e[i].to;
            dfs(v, u);
            static int g[2][N]; 
            for (int j = 1; j <= sz[u] + sz[v]; j++) g[0][j] = g[1][j] = 0;
            for (int j = 1; j <= sz[v]; j++)
                for (int k = 1; k <= sz[u]; k++) {
                    g[0][j + k - 1] = (g[0][j + k - 1] + (LL)dp[0][v][j] * dp[0][u][k]) % mod;
                    g[1][j + k - 1] = (g[1][j + k - 1] + (LL)dp[1][v][j] * dp[0][u][k] + (LL)dp[0][v][j] * dp[1][u][k]) % mod;
                    g[0][j + k] = (g[0][j + k] + (LL)dp[1][v][j] * dp[0][u][k]) % mod;
                    g[1][j + k] = (g[1][j + k] + (LL)dp[1][v][j] * dp[1][u][k]) % mod;
                }
            sz[u] += sz[v];
            for (int i = 1; i <= sz[u]; i++) dp[0][u][i] = g[0][i], dp[1][u][i] = g[1][i];
        }
    for (int i = 1; i <= sz[u]; i++) dp[1][u][i] = (dp[1][u][i] + dp[0][u][i]) % mod;
}

int frac[N], inv[N];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

class TreeDistance {
public:
    int countTrees(vector<int> p, int k) {
        n = p.size() + 1;
        for (int i = 0; i < n - 1; i++) adde(p[i] + 1, i + 2);
        dfs(1, 0), frac[0] = inv[0] = 1;
        for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
        for (int i = 2; i <= n; i++) dp[1][1][i] = (LL)dp[1][1][i] * Pow(n, i - 2) % mod;
        dp[1][1][1] = 1;
        int res = 0;
        for (int i = 0; i <= k; i++) {
            int ans = 0;
            for (int j = 0; j <= i; j++) {
                int tmp = (LL)dp[1][1][j + 1] * C(n - j - 1, i - j) % mod;
                if ((j - i) & 1) tmp = mod - tmp;
                ans = (ans + tmp) % mod;
            }
            res = (res + ans) % mod;
        }
        return res;
    }
};

//int main() {
//    TreeDistance solver;
//    cout << solver.countTrees({0, 0, 0, 0, 2, 3, 1, 2, 3, 7, 3, 10, 8, 8, 9, 1, 2, 0, 7, 17, 19, 2, 17, 2, 0,
//6, 4, 9, 12, 14, 8, 12, 10, 30, 20, 30, 8, 36, 28, 22, 8, 2, 2, 13, 26, 14, 46, 6, 25},
//10) << endl;
//}
