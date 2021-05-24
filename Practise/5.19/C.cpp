#include <bits/stdc++.h>
using namespace std;

const int N = 51;
const int M = 151;

typedef long long LL;

int mod;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int dp[2][M][M][N][N], g[M][M][N];

int main() {
    //freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
    int n, m, k, inv; cin >> n >> k >> m >> mod, inv = Pow(m, mod - 2);
    if (n <= 2) return puts("1"), 0;
    if ((n - 2) / 2 * k >= m) return puts("0"), 0;
    int cur = 1;
    for (int i = 0; i < m; i++)
        dp[cur][i][k + 1][1][0] = inv;
    int res = 0;
    for (int i = 2; i <= n; i++) {
        cur ^= 1;
        for (int j = 0; j < m; j++)
            for (int t = 0; t <= k + 1; t++)
                for (int a = 1; a < i; a++) {
                    g[j][t][a] = 0;
                    for (int b = 0; b < i; b++) dp[cur][j][t][a][b] = 0;
                }  
        for (int j = 0; j < m; j++)
            for (int t = 0; t <= k + 1; t++) {
                for (int a = 1; a < i; a++) {
                    static int h[N]; memset(h, 0, sizeof(h));
                    int l = max(j, j - t + k);
                    if (l >= m) continue;
                    for (int b = 0; b < i; b++) if (dp[cur ^ 1][j][t][a][b]) {
                        int w1 = (LL)dp[cur ^ 1][j][t][a][b] * inv % mod;
                        int lim = 0;
                        if (l == j - t + k) lim = max(lim, b);
                        if (l == j) lim = max(lim, a);
                        Inc(h[lim], w1);
                        if (l + 1 < m) Inc(g[l + 1][min(l + 1 - j, k + 1)][a], w1);
                    }
                    for (int b = 0; b < i; b++) {
                        if (b) Inc(h[b], h[b - 1]);
                        if (l < m) Inc(dp[cur][l][min(l - j, k + 1)][b + 1][a + (a > b)], h[b]);
                    }
                }
            }
        for (int j = 0; j < m; j++)
            for (int t = 0; t <= k + 1; t++)
                for (int a = 1; a < i; a++)
                    Inc(g[j + 1][min(t + 1, k + 1)][a], g[j][t][a]);
        for (int j = 0; j < m; j++)
            for (int t = 0; t <= k + 1; t++)
                for (int a = 1; a < i; a++)
                    for (int q = 0; q < i; q++)
                        Inc(dp[cur][j][t][q + 1][a + (a > q)], g[j][t][a]);
    }
    for (int j = 0; j < m; j++)
        for (int t = 0; t <= k + 1; t++)
            for (int a = 1; a <= n; a++) 
                for (int b = 0; b <= n; b++) Inc(res, dp[cur][j][t][a][b]);
    cout << res << endl;
}