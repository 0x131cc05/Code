#include <bits/stdc++.h>
using namespace std;

const int N = 250010;
const int mod = 998244353;

int dp[N], a[N], ans[N];

int main() {
    // freopen("sequence.in", "r", stdin), freopen("sequence.out", "w", stdout);
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    a[n + 1] = a[n];
    dp[a[n]] = 1;
    for (int i = n; i >= 0; i--) {
        dp[0] = 0;
        int *nw = &dp[a[i + 1] - 1], *lst = &dp[a[i + 1]];
        for (int j = a[i + 1] - 1; j >= 0; j--) {
            *nw += *lst;
            *nw -= *nw >= mod ? mod : 0;
            lst = nw, nw--;
        }
        ans[i] = dp[0];
    }
    for (int i = 0; i <= n; i++) printf("%d ", ans[i]);
}
