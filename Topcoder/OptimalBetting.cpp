#include <bits/stdc++.h>
using namespace std;

struct tcurts { int l, r; double v; };

const int N = 100010;
const double eps = 1e-8;

double wkr[6][N * 2], dp[6][N * 2], sum[N * 2];

bool chk(double a, double b) {
    return fabs(a - b) < eps;
}

struct OptimalBetting {
    double findProbability(int a, int b, int k) {
        vector<tcurts> seg[6]; 
        seg[0].push_back({0, b - 1, 0}), seg[0].push_back({ b, b * 2, 1 });
        for (int i = b; i <= b * 2; i++) wkr[0][i] = 1;
        static int vis[N * 2];
        for (int i = 1; i <= k; i++) {
            memset(vis, 0, sizeof(vis));
            for (auto a : seg[i - 1]) for (auto b : seg[i - 1]) {
                int p = (a.l + b.l + 1) / 2; double w = (a.v + b.v) / 2;
                vis[p] = 1, wkr[i][p] = max(w, wkr[i][p]);
            }
            for (int l = 0; l <= b; l++) {
                int r = l; assert(vis[l]);
                while (r < b * 2 && !vis[r + 1]) wkr[i][r + 1] = wkr[i][l], r++;
                seg[i].push_back({ l, r, wkr[i][l] }), l = r;
            }
        }
        for (int i = 0; i <= 2 * b; i++) dp[0][i] = 1;
        for (int i = 1; i <= k; i++) {
            sum[0] = 1;
            for (int j = 1; j <= 2 * b; j++) sum[j] = sum[j - 1] + dp[i - 1][j];
            for (auto t : seg[i]) {
                int l = t.l, r = t.r;
                if (l >= b) continue;
                for (auto a : seg[i - 1]) for (auto b : seg[i - 1]) if (a.l <= b.l) {
                    if (!chk(a.v + b.v, t.v * 2)) continue;
                    for (int j = l; j <= r; j++) {
                        int mn = max(max(b.l - j, j - a.r), 0), mx = min(b.r - j, j - a.l);
                        if (mn <= mx) {
                            dp[i][j] += sum[j + mx] + sum[j - mn];
                            if (j + mn - 1 >= 0) dp[i][j] -= sum[j + mn - 1];
                            if (j - mx - 1 >= 0) dp[i][j] -= sum[j - mx - 1];
                        }
                    }
                }
            }
            for (int j = 0; j < b; j++) dp[i][j] /= 2 * (j + 1);
            for (int j = b; j <= 2 * b; j++) dp[i][j] = 1;
        }
        return dp[k][a];
    }
};

// int main() {
//     OptimalBetting solver;
//     cout << solver.findProbability(50123, 87654, 5) << endl;
// }