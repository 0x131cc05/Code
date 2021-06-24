#include <bits/stdc++.h>
using namespace std;

const int N = 2010;

int dp[N][N], s1[N], s2[N]; char A[N], B[N];

int main() {
    freopen("irony.in", "r", stdin), freopen("irony.out", "w", stdout);
    int T; scanf("%d", &T);
    while (T--) {
        int n, m; scanf("%d%d%s%s", &n, &m, A + 1, B + 1);
        if (n <= 2000 && m <= 2000) {
            for (int i = 0; i <= n; i++)
                for (int j = 0; j <= m; j++) dp[i][j] = 0;
            for (int i = 1; i <= n; i++) s1[i] = s1[i - 1] + (A[i] == '(');
            for (int i = 1; i <= m; i++) s2[i] = s2[i - 1] + (B[i] == '(');
            for (int i = 0; i <= n; i++)
                for (int j = 0; j <= m; j++) {
                    int t = dp[i][j], R = s1[i] + s2[j] - t;
                    if (i != n) dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + (A[i + 1] == ')' && R));
                    if (j != m) dp[i][j + 1] = max(dp[i][j + 1], dp[i][j] + (B[j + 1] == ')' && R));
                }
            printf("%d\n", n + m - dp[n][m] * 2);
        } else {
            int stk = 0, L1 = 0, R1 = 0, L2 = 0, R2 = 0;
            for (int i = 1; i <= n; i++) {
                if (A[i] == '(') stk++;
                else {
                    if (stk) stk--;
                    else L1++;
                }
            }
            R1 = stk, stk = 0;
            for (int i = 1; i <= m; i++) {
                if (B[i] == '(') stk++;
                else {
                    if (stk) stk--;
                    else L2++;
                }
            }
            R2 = stk;
            int t = max(min(R1, L2), min(R2, L1));
            printf("%d\n", L1 + R1 + L2 + R2 - t * 2);
        }
    }
}
