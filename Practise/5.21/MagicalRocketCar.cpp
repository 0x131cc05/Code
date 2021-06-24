#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int dp[N][N * N];

struct MagicalRocketCar {
    double getmax(vector<int> x, vector<int> y) {
        int n = x.size(); vector<int> id(n);
        for (int i = 0; i < n; i++) if (x[i] > y[i]) swap(x[i], y[i]);
        for (int i = 0; i < n; i++) id[i] = i;
        int sum = 0;
        sort(id.begin(), id.end(), [&](int a, int b) {
            double A = (double)y[a] / x[a];
            double B = (double)y[b] / x[b];
            return A > B;
        });
        double res = 0;
        for (int i = 0; i < n; i++) res += x[i] * y[i] * 0.5;
        memset(dp, -0x3f, sizeof(dp));
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            int ty = y[id[i - 1]], tx = x[id[i - 1]];
            for (int j = 0; j <= sum; j++) if (dp[i - 1][j] >= 0) {
                dp[i][j + ty] = max(dp[i][j + ty], dp[i - 1][j] + tx * j);
                dp[i][j] = max(dp[i][j], dp[i - 1][j] + (sum - j) * tx);
            }
            sum += ty;
        }
            
        int mx = 0;
        for (int j = 0; j <= sum; j++) {
            int w = dp[n][j] + j * (sum - j);
            mx = max(mx, w);
        } 
        return res + mx;
    }
};

// int main() {
//     MagicalRocketCar solver;
//     cout << solver.getmax(	
// {62,57,64,80,25,42,16,20,73,46,48,81,61,65,70,24,83,82,100,81,87,99,81,47,6,37},
// {98,35,77,88,56,69,50,88,50,89,94,1,54,41,49,27,69,81,74,8,12,53,70,47,68,94}
// ) << endl;
// }