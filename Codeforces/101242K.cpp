#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int dp[N][N][2];

int calc(int l, int r) {
    return (l + r) * (r - l + 1) / 2;
}

int main() {
    int n; cin >> n; vector<int> num(n + 1);
    for (int i = 1; i <= n; i++) cin >> num[i];
    int mx = *max_element(num.begin(), num.end());
    for (int t = mx; t >= 1; t--) {
        memset(dp, 0, sizeof(dp)), dp[0][t + 1][0] = 1;
        for (int i = 1; i <= n; i++) 
            for (int j = t + 1; j >= 1; j--) 
                for (int p = 0; p <= 1; p++) if (dp[i - 1][j][p]) {
                    for (int k = 1; k <= t + 1; k++) {
                        if (i != n && k == t + 1) continue;
                        int w = calc(1, j - 1) + calc(1, k - 1);
                        if (num[i] == w || (num[i] >= w && (num[i] - w) % 2 == 0 && t != 1)) dp[i][k][1] = 1;
                    }
                    if (p) for (int k = j + 1; k <= t + 1; k++) {
                        if (i != n && k == t + 1) continue;
                        int w = calc(j, k - 1);
                        if (num[i] == w) dp[i][k][1] = 1;
                    }
                    for (int k = 1; k <= j - 1; k++) {
                        int w = calc(k, j - 1);
                        if (num[i] == w) dp[i][k][0] = 1;
                    }
                }
        if (dp[n][t + 1][1]) {
            cout << t << endl;
            return 0;
        }
    }
    cout << "no quotation" << endl;
    return 0;
}