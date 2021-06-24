#include <bits/stdc++.h>
using namespace std;

const int N = 12;
const int M = 152;

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

int dp[2][M][M][N][N];

int main() {
    int n, m, k, inv; cin >> n >> k >> m >> mod, inv = Pow(m, mod - 2);
    int cur = 1;
    for (int i = 0; i < m; i++)
        dp[cur][i][k + 1][1][0] = inv;
    int res = 0;
    for (int i = 2; i <= n; i++) {
        cur ^= 1, memset(dp[cur], 0, sizeof(dp[cur]));
        for (int j = 0; j < m; j++)
            for (int t = 0; t <= k + 1; t++)
                for (int a = 1; a <= n; a++)
                    for (int b = 0; b <= n; b++) if (dp[cur ^ 1][j][t][a][b]) {
                        int w1 = (LL)dp[cur ^ 1][j][t][a][b] * inv % mod;
                        for (int p = max(j, j - t + k); p < m; p++)
                            for (int q = 0; q < i; q++) {
                                if (p == j - t + k && q < b) continue;
                                if (p == j && q < a) continue;
                                if (i == n) Inc(res, w1);
                                Inc(dp[cur][p][min(p - j, k + 1)][q + 1][a + (a > q)], w1);
                            }
                    }
    }
    cout << res << endl;
}
