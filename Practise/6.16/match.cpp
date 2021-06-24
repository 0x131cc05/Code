#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

int a[N], dp[2][N][N], fuck[N];

int cur;

void solve(int j, int i1, int i2, int l, int r) {
    if (i1 > i2) return;
    int mid = (i1 + i2) >> 1, pos = -1;
    for (int t = max(mid, max(l, fuck[mid])); t <= min(j - 1, r); t++) {
        int w = dp[cur ^ 1][mid][t] + dp[cur ^ 1][t + 1][j] + a[j] - a[t];
        if (w < dp[cur][mid][j]) dp[cur][mid][j] = w, pos = t;
    }
    fuck[mid] = max(fuck[mid], pos);
    dp[cur][mid][j] = min(dp[cur][mid][j], dp[cur ^ 1][mid][j]);
    if (pos != -1) solve(j, i1, mid - 1, l, pos);
    solve(j, mid + 1, i2, max(l, pos), r);
}

int main() {
    freopen("match.in", "r", stdin), freopen("match.out", "w", stdout);
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) dp[0][i][i] = 0;
    cur = 0;
    for (int i = 1; i <= k; i++) {
        memset(fuck, 0, sizeof(fuck));
        cur ^= 1, memset(dp[cur], 0x3f, sizeof(dp[cur]));
        for (int j = 2; j <= n; j++) solve(j, 1, j, 1, j - 1);
    }
    printf("%d\n", dp[cur][1][n]);
}
