#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const int mod = 1e9 + 7;

int mx[N][N], dp[N][N][N];

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

class AlienAndPermutation {
public:
    int getNumber(vector<int> p, int k) {
        int n = p.size();
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++)
                mx[i][j] = max(mx[i][j - 1], p[j - 1]);
        dp[0][0][0] = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= n; j++)
                for (int t = 0; t <= k; t++) if (dp[i][j][t]) {
                    for (int l = 0; l + j <= n && (l == 0 || p[i] >= mx[min(j + 1, i + 1)][max(j + l, i + 1)]); l++) {
                        int offset = !!l;
                        if (l == 1 && i == j) offset = 0;
                        if (t + offset <= k) 
                            Inc(dp[i + 1][j + l][t + offset], dp[i][j][t]);
                    }
                }
        int res = 0;
        for (int t = 0; t <= k; t++) Inc(res, dp[n][n][t]);
        return res; 
    }
};




















'
// int main() {
//     AlienAndPermutation solver;
//     cout << solver.getNumber({8, 3, 1, 5, 10, 4, 7, 9, 6, 2},
// 3) << endl;
// }