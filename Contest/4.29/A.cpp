#include <bits/stdc++.h>
using namespace std;

const int N = 110, M = 2010;

const int mod = 1e9 + 7;

typedef long long LL;

int dp[3][N][N][M], A[N];

inline void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int main() {
    int n, L; scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
    if (n == 1) return puts("1"), 0;
    sort(A + 1, A + n + 1);
    dp[0][0][0][0] = 1, A[0] = A[1];
    for (int i = 1; i <= n; i++) {
        int delta = A[i] - A[i - 1];
        for (int j = 0; j < i; j++) {
            for (int k = 0; k <= min(2, i - 1); k++) {
                int base = (2 * j - k) * delta;
                for (int l = 0; l <= L - base; l++) if (dp[k][i - 1][j][l]) {
                    Inc(dp[k][i][j + 1][l + base], (LL)dp[k][i - 1][j][l] * (j + 1 - k) % mod);
                    Inc(dp[k][i][j][l + base], (LL)dp[k][i - 1][j][l] * (2 * j - k) % mod);
                    if (j) Inc(dp[k][i][j - 1][l + base], (LL)dp[k][i - 1][j][l] * (j - 1) % mod);
                    if (k != 2) {
                        Inc(dp[k + 1][i][j + 1][l + base], (LL)dp[k][i - 1][j][l] * (2 - k) % mod);
                        Inc(dp[k + 1][i][j][l + base], (LL)dp[k][i - 1][j][l] * (2 - k) % mod);
                    }
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i <= L; i++) Inc(res, dp[2][n][1][i]);
    printf("%d\n", res);
    return 0;
}