#include <bits/stdc++.h>
using namespace std;

const int N = 22;
const int M = 152;

typedef long long LL;

int mod, inv[M];

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int dp[M][N][M][N][N];

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int main() {
    // freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
    int n, k, m, res = 0; cin >> n >> k >> m >> mod;
    for (int i = 1; i <= max(n, m); i++) inv[i] = Pow(i, mod - 2);
    dp[0][0][0][0][0] = 1;
    for (int i = 0; i < m; i++) 
        for (int j = 0; j <= n; j++)
            for (int t = 0; t <= i; t++)
                for (int l = 0; l <= j; l++)
                    for (int p = 0; p <= j; p++) if (dp[i][j][t][l][p]) {
                        int w = dp[i][j][t][l][p];
                        if (i == m - 1 && j == n) { Inc(res, w); continue; }
                        bool type = l != 0 && t + k > i; // end
                        if (type) Inc(dp[i + 1][j][t][l][0], w);
                        else Inc(dp[i + 1][j][0][0][0], w);
                        int c = (LL)inv[m] * w % mod;
                        for (int q = p; q <= j; q++) {
                            if (type || l > q) {
                                if (t + k < m) Inc(dp[t + k][j + 1][i][q + 1][l + (l > q)], c);
                                else if (j + 1 == n) Inc(res, c);
                            } else {
                                Inc(dp[i][j + 1][i][q + 1][q + 1], c);
                            }
                        }
                    }
    printf("%d\n", res);
}