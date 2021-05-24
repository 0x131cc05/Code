#include <bits/stdc++.h>
using namespace std;

const int N = 510;

int dp[7][1 << 7][N]; char s[10];

int main() {
    int n; scanf("%d", &n);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] = 0;
    for (int i = 1; i <= n + 1; i++) {
        if (i <= n) scanf("%s", s); 
        auto chkmin = [&](int &a, int b) {
            if (b < a) a = b;
        };
        int mx = 0;
        for (int j = 0; j < 7; j++) mx = max(mx, (int)s[j] - '0');
        for (int j = 0; j < 7; j++) if ((i != n + 1 && mx == s[j] - '0') || (i == n + 1 && j == 0)) {
            for (int s = 0; s < 1 << 7; s++) if ((s & 1) == 0)
                for (int lst = 0; lst < 7; lst++) if (dp[lst][s][i - 1] <= n) {
                    int w = dp[lst][s][i - 1];
                    int diff = j - lst; if (diff < 0) diff += 7;
                    for (int k = 0; k < 7; k++) if (k == 0 || (s & (1 << k))) {
                        int nxt = (k + diff) & 7, s1 = k ? (s ^ (1 << k)) : s; 
                        if (nxt == 0) chkmin(dp[j][s1][i], w);
                        else if (s1 & (1 << nxt)) chkmin(dp[j][s1 ^ (1 << nxt)][i], w);
                        else chkmin(dp[j][s1 ^ (1 << nxt)][i], w + 1);
                    }
                }
        }
    }
    int res = 1e9;
    for (int s = 0; s < 1 << 7; s++)
        res = min(res, dp[0][s][n + 1]);
    printf("%d\n", res);
}