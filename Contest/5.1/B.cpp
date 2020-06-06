#include <bits/stdc++.h>
using namespace std;

const int N = 510;

int dp[N][N * 2], l[N], r[N], a[N];

inline int Abs(int x) {
    return x > 0 ? x : -x;
}

int stk[N];

int main() {
    int n, t = 0, res = 1e9; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i], &l[i], &r[i]), t = max(t, a[i]);
        a[i + n] = a[i], l[i + n] = l[i], r[i + n] = r[i];
    }
    for (int i = 1; i <= n; i++) {
        memset(dp, 0x3f, sizeof(dp));
        for (int j = l[i]; j <= r[i]; j++) 
            dp[1][j - a[i] + N] = 0;
        for (int j = i + 1; j < i + n; j++)
            for (int ls = -t; ls <= t; ls++) if (dp[j - i][ls + N] >= 0) {
                int L = max(l[j], -t - ls + a[j]), R = min(r[j], t + a[j] - ls);
                for (int k = L; k <= R; k++) 
                    dp[j - i + 1][k - a[j] + ls + N] = min(dp[j - i + 1][k - a[j] + ls + N], dp[j - i][ls + N] + Abs(ls));
            }
                
        res = min(res, dp[n][N]);
    }
    printf("%d\n", res);
}
