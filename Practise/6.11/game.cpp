#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL calc(int k, int n) { // k days, sum = n, minimize sum ai^2
    int p = n / k, c = n % k;
    return (LL)p * p * k + (LL)(2 * p + 1) * c;   
}

int pre[1010][1010], dp[51][1010];

int main() {
    freopen("game.in", "r", stdin), freopen("game.out", "w", stdout);
    int n, m, k; cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int nw = k - i;
        for (int j = 1; j <= m; j++) {
            int l = 1, r = j, mid, pos = -1;
            while (l <= r) {
                mid = (l + r) >> 1;
                if (calc(mid, j) <= nw) pos = mid, r = mid - 1;
                else l = mid + 1;
            }    
            pre[i][j] = pos;
        }
    }
    memset(dp, 0x3f, sizeof(dp)), dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++) if (dp[i - 1][j] < 1e9) {
            for (int k = 0; j + k <= m && pre[j][k] != -1; k++) {
                dp[i][j + k] = min(dp[i][j + k], dp[i - 1][j] + pre[j][k]);
            }
        }
    if (dp[n][m] < 1e9) printf("%d\n", dp[n][m]);
    else puts("-1");
}
