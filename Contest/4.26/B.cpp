#include <bits/stdc++.h>
using namespace std;

const int N = 5010;

typedef long long LL;

int num[N]; LL dp[2][N];

int main() {
    int n; scanf("%d", &n);
    if (n > 5000) return 0;
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    memset(dp, -0x3f, sizeof(dp)), dp[0][0] = 0; int cur = 0;
    for (int i = 1; i <= n; i++) {
        cur ^= 1, memset(dp[cur], -0x3f, sizeof(dp[cur]));
        for (int j = 0; j < i; j++) {
            int nw = j & 1 ? -num[i] : num[i];
            dp[cur][j + 1] = max(dp[cur][j + 1], dp[cur ^ 1][j] + nw);
            dp[cur][j] = max(dp[cur][j], dp[cur ^ 1][j]);
        }
    }
    for (int i = 1; i <= n; i++) printf("%lld ", dp[cur][i]);
    return 0;
}