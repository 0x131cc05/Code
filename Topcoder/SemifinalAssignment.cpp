#include <bits/stdc++.h>
using namespace std;

double dp[2][3][26][26];

struct SemifinalAssignment {
    vector<double> getProbability(vector<int> A, vector<int> B, int K) {
        int n = A.size(), mx = *max_element(B.begin(), B.end());
        vector<double> ans(n * 2);
        for (int t = 0; t <= mx; t++) {
            for (int p = 1; p <= n; p++) {
                memset(dp, 0, sizeof(dp)), dp[0][0][0][0] = 1;
                for (int i = 1; i <= n; i++) {     
                    int all = B[i - 1] - A[i - 1] + 1;
                    for (int j = 0; j < i && j <= K; j++) {
                        for (int a = 0; a <= 1; a++) {
                            for (int b = 0; b <= 2; b++) {
                                if (i <= p && b) continue;
                                double w = dp[a][b][i - 1][j];
                                double p1 = max(min((double)(B[i - 1] - t) / all, 1.), 0.); // >
                                double p2 = (double)(A[i - 1] <= t && t <= B[i - 1]) / all; // =
                                double p3 = 1 - p1 - p2; // <
                                int tb = i == p ? (((j & 3) == 0 || (j & 3) == 3) ? 1 : 2) : b;
                                dp[a][tb][i][j + 1] += w * p1;
                                if (i != p) dp[a][tb][i][j] += w * p3;
                                if (a) { if (i != p) dp[a][tb][i][j] += w * p2; } 
                                else dp[0][tb][i][j + 1] += w * p2, dp[1][tb][i][j + 1] += w * p2;
                            }
                        }
                    }
                }
                ans[p * 2 - 2] += dp[1][1][n][K], ans[p * 2 - 1] += dp[1][2][n][K];
            }
        }
        return ans;
    }
};

// int main() {
//     SemifinalAssignment solver;
//     auto tmp = solver.getProbability({ 3, 317, 25, 447, 96, 333, 361, 103 },
// { 947, 773, 601, 544, 594, 399, 786, 954 },
// 6);
//     for (auto t : tmp) cout << t << ' ';
// }
