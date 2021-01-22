#include <bits/stdc++.h>
using namespace std;

const int N = 160;

__float128 C[N][N];

struct BlindBoxSets {
    double expectedPurchases(int m, int n) {
        for (int i = 0; i <= n * max(m - 1, 1); i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++) C[i][j] = C[i - 1][j - 1] + C[i - 1][j]; 
        }
        __float128 ans = 0;
        for (int i = 1; i <= n; i++) {
            static __float128 dp[N][N]; memset(dp, 0, sizeof(dp)), dp[0][0] = 1;
            for (int j = 1; j <= i; j++)
                for (int k = 0; k <= (j - 1) * (m - 1); k++) if (dp[j - 1][k]) {
                    __float128 cur = 1;
                    for (int l = 0; l < m; l++) {
                        dp[j][k + l] += dp[j - 1][k] * cur * C[k + l][k];
                        cur /= i;
                    }
                }
            __float128 res = 0;
            for (int j = 0; j <= i * (m - 1); j++) res += dp[i][j] / i;
            res *= n * C[n][i];
            if (i & 1) ans += res;
            else ans -= res;
        }
        return (double)ans;
    }
};

// int main() {
//     BlindBoxSets solver;
//     printf("%.10Lf\n", solver.expectedPurchases(4, 49));
//     // cout <<  << endl;
// }