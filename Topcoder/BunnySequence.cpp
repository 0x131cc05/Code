#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
const int mod = 1e9 + 9;

typedef long long LL;

int dp[N], pre[N];

struct BunnySequence {
    int getNumber(int m, int n) {
        dp[0] = pre[0] = 1;
        for (int i = 1; i <= n; i++) {
            dp[i] = pre[i - 1];
            if (i - m >= 1) dp[i] = (dp[i] - pre[i - m - 1] + mod) % mod;
            pre[i] = (pre[i - 1] + dp[i]) % mod;
        }
        if (m > n) return dp[n];
        return (dp[n] - dp[n - m] + mod) % mod;
    }
};

// int main() {
//     BunnySequence solver;
//     cout << solver.getNumber(3, 3);
// }