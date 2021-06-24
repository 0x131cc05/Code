#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

int a[N], dp[N][N];

int main() {
    // freopen("in.in", "r", stdin);
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) dp[i][i] = 0;
    for (int t = 1, mn = 2; t <= k; t++) {
        for (int len = mn; len >= 2; len--) {
            for (int i = 1; i + len - 1 <= n; i++) {
                int j = i + len - 1; int pos = -1;
                for (int l = i; l < j; l++) {
                    int w = dp[i][l] + dp[l + 1][j] + a[j] - a[l];
                    if (w < dp[i][j]) dp[i][j] = w;
                }
            }
        }
        mn = min(mn * 2, n);
    }
    printf("%d\n", dp[1][n]);
}