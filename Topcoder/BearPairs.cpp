#include <bits/stdc++.h>
using namespace std;

const int N = 2510;

int f[2][8][7][N], g[2][8][7][N];

void chk(int &x, int y) {
    if (y < x) x = y;
}

struct BearPairs {
    int minCost(string s, vector<int> cost, int k) {
        memset(f, 0x3f, sizeof(f)), memset(g, 0x3f, sizeof(g));
        for (int i = 0; i < 6; i++) 
            f[0][0][i][0] = g[0][0][i][0] = 0;
        int cur = 0, n = s.size();
        for (int i = 1; i <= n; i++) {
            cur ^= 1, memset(f[cur], 0x3f, sizeof(f[cur])), memset(g[cur], 0x3f, sizeof(g[cur]));
            int c = s[i - 1] - 'a';
            for (int a = 0; a <= k; a++) {
                for (int b = 0; b < 6; b++) {
                    for (int t = 0; t < i; t++) {
                        if (b == c) {
                            chk(f[cur][a][b][t + 1] , f[cur ^ 1][a][b][t] + cost[i - 1]);
                            if (t) chk(g[cur][a][b][t - 1], g[cur ^ 1][a][b][t] + cost[i - 1]);
                        } else {
                            if (t) chk(f[cur][a][b][t - 1], f[cur ^ 1][a][b][t] + cost[i - 1]);
                            chk(g[cur][a][b][t + 1], g[cur ^ 1][a][b][t] + cost[i - 1]);
                        }
                        chk(f[cur][a + 1][b][t], f[cur ^ 1][a][b][t]);
                        chk(g[cur][a + 1][b][t], g[cur ^ 1][a][b][t]);
                    }
                }
            }
            for (int a = 0; a <= k; a++) {
                int mn = 1e9;
                for (int b = 0; b < 6; b++)
                    mn = min(mn, min(f[cur][a][b][0], g[cur][a][b][0]));
                for (int b = 0; b < 6; b++)
                    f[cur][a][b][0] = g[cur][a][b][0] = mn;
            }
            for (int a = 0; a <= k; a++)
                for (int b = 0; b < 6; b++)
                    for (int b1 = 0; b1 < 6; b1++) if (b != b1)
                        for (int t = 0; t <= i; t++) chk(g[cur][a][b1][t], f[cur][a][b][t]);
            for (int a = 0; a <= k; a++)
                for (int b = 0; b < 6; b++)
                    for (int t = 0; t <= i; t++) {
                        if (f[cur][a][b][t] < 1e9) f[cur][a][b][t] += t * 100;
                        if (g[cur][a][b][t] < 1e9) g[cur][a][b][t] += t * 100;
                    }
        }
        int res = min(f[cur][k][0][0], g[cur][k][0][0]);
        return res > 9.9e8 ? -1 : res;
    }
};