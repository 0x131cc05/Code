#include <bits/stdc++.h>
using namespace std;

const int N = 3010;

typedef long long LL;

vector<int> v[N];

LL dp[21][N], all[N], res; int k; 

void solve(int layer, int l, int r) {
    if (l == r) {
        res = max(res, dp[layer][k]); LL tmp = v[l][0];
        for (int i = 0; i < k && i < v[l].size(); tmp += v[l][++i]) 
            res = max(res, dp[layer][k - i - 1] + tmp);
        return;
    }
    int mid = (l + r) >> 1;
    auto push = [&](int l, int r) {
        for (int i = 1; i <= k; i++) dp[layer + 1][i] = dp[layer][i];
        for (int i = l; i <= r; i++)
            for (int j = k; j >= v[i].size(); j--)
                dp[layer + 1][j] = max(dp[layer + 1][j], dp[layer + 1][j - v[i].size()] + all[i]);
    };
    push(l, mid), solve(layer + 1, mid + 1, r), push(mid + 1, r), solve(layer + 1, l, mid);
}

int main() {
    int n; scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        int t; scanf("%d", &t);
        for (int j = 1, a; j <= t; j++) scanf("%d", &a), v[i].push_back(a), all[i] += a;
    }
    solve(0, 1, n), printf("%lld\n", res);
}