#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

int dp[N][N], pre[N];

int main() {
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) 
        scanf("%d", &pre[i]), pre[i] += pre[i - 1];
    memset(dp, 0x3f, sizeof(dp)), dp[0][0] = -1e9;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < k; j++)
            for (int k = j; k < i; k++)
                dp[i][j + 1] = min(dp[i][j + 1], max(pre[i] - pre[k], dp[k][j]));
    printf("%d\n", dp[n][k]);
}