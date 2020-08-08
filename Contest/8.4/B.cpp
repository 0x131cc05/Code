#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int mod = 998244353;

typedef long long LL;

int dp[N][N][N], num[N], g[N][N][N];

int dfs(int l, int r, int k);

int sum(int l, int r, int k) {
    if (l > r) return 1;
    if (l == r) return num[l] == num[r + 1] ? 0 : k;
    if (g[l][r][k] != -1) return g[l][r][k];
    int &res = g[l][r][k]; res = 0;
    for (int i = 1; i <= k; i++) res = (res + dfs(l, r, i)) % mod;
    return res;
}

int dfs(int l, int r, int k) {
    if (dp[l][r][k] != -1) return dp[l][r][k];
    int &res = dp[l][r][k]; res = 0;
    for (int i = l; i <= r; i++) if (num[i] != num[r + 1])
        res = (res + (LL)sum(l, i - 1, k - 1) * sum(i + 1, r, k)) % mod;
    return res;
}

int main() {
    memset(dp, -1, sizeof(dp)), memset(g, -1, sizeof(g));
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 1, a; i <= n; i++) scanf("%d", &num[i]);
    printf("%d\n", dfs(1, n, k)); 
}