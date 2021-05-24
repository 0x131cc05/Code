#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int dp[44][14][1 << 14], g[44][14][1 << 14];

struct BearDestroys {
    int sumUp(int n, int m, int mod) {
        dp[1][1][0] = 1;
        int all = 1 << (m + 1);
        for (int i = 1; i <= n + m - 1; i++)
            for (int j = 1; j <= m; j++) {
                int px = i - j + 1, ban = 0;
                if (px <= 0 || px > n) ban = 1;
                for (int s = 0; s < all; s++) if (dp[i][j][s] || g[i][j][s]) {
                    int right = 0, down = 0, keep = 0, w = dp[i][j][s], w1 = g[i][j][s];
                    if (!ban) { 
                        if (s & (1 << j)) keep++; // E
                        else if ((px == n || (s & (1 << (j - 1))))) {
                            if (j != m) down++;
                            else keep++;
                        } else right++;
                        if (s & (1 << j)) keep++; // S
                        else if (j == m && !(s & (1 << (j - 1)))) right++;
                        else if (j != m) down++;
                        else keep++;
                    } else keep = 1;
                    auto nxt = [&](int s) { 
                        return j == m ? ((s << 1) & (all - 1)) : s; 
                    };
                    auto Add = [&](int &x, LL y) {
                        x = (x + y) % mod;
                    };
                    int ti = j == m ? i + 1 : i, tj = j == m ? 1 : j + 1;
                    Add(dp[ti][tj][nxt(s & ~(1 << j))], (LL)w * keep);
                    Add(g[ti][tj][nxt(s & ~(1 << j))], (LL)w1 * keep);

                    if (!ban) {
                        Add(dp[ti][tj][nxt(s | (1 << (j - 1)))], (LL)w * right);
                        Add(g[ti][tj][nxt(s | (1 << (j - 1)))], (LL)w * right + (LL)w1 * right);

                        Add(dp[ti][tj][nxt(s | (1 << j))], (LL)w * down);
                        Add(g[ti][tj][nxt(s | (1 << j))], (LL)w * down + (LL)w1 * down);
                    }
                }
            }
        int res = 0;
        for (int s = 0; s < all; s++)
            res = (res + (LL)2 * g[n + m - 1][m][s]) % mod;
        return res;
    }
};

// int main() {
//     BearDestroys solver;
//     cout << solver.sumUp(11, 13, 5) << endl;
// }