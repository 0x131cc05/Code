#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

typedef long long LL;

int num[N], L[N], R[N];

vector<int> ok[N];

LL dp[2][10][N];

int main() {
    freopen("sequence1_4.in", "r", stdin);
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    for (int i = 1; i <= n; i++) 
        L[i] = num[i] == num[i - 1] ? L[i - 1] : i;
    for (int i = n; i >= 1; i--)
        R[i] = num[i] == num[i + 1] ? R[i + 1] : i;
    for (int i = 1; i <= n; i++) {
        ok[i].push_back(num[i]), ok[i].push_back(num[i] - 1);
        ok[i].push_back(num[L[i] - 1]);
        ok[i].push_back(num[R[i] + 1]);
        ok[i].push_back(num[L[i] - 1] - 1);
        ok[i].push_back(num[R[i] + 1] - 1);
        if (L[i] > 1) {
            ok[i].push_back(num[L[L[i] - 1] - 1]);
            ok[i].push_back(num[L[L[i] - 1] - 1] - 1);
        }
        if (R[i] < n) {
            ok[i].push_back(num[R[R[i] + 1] + 1]);
            ok[i].push_back(num[R[R[i] + 1] + 1] - 1);
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < ok[1].size(); i++)
        if (ok[1][i] <= num[1]) dp[0][i][1] = dp[1][i][1] = num[1] - ok[1][i];
    for (int i = 2; i <= n; i++) 
        for (int t = 0; t <= 1; t++)
            for (int a = 0; a < ok[i - 1].size(); a++) if (dp[t][a][i - 1] < 1e17) {
                LL w = dp[t][a][i - 1];
                for (int b = 0; b < ok[i].size(); b++) if (ok[i][b] <= num[i]) {
                    int nxt = t;
                    if (ok[i][b] != ok[i - 1][a]) {
                        if ((ok[i][b] > ok[i - 1][a]) == t) continue;
                        nxt = t ^ 1;
                    }
                    dp[nxt][b][i] = min(dp[nxt][b][i], w + num[i] - ok[i][b]);
                }
            }
    LL res = 1e18;
    for (int t = 0; t <= 1; t++)
        for (int i = 0; i < ok[n].size(); i++)
            res = min(res, dp[t][i][n]);
    printf("%lld\n", res);
}
 