#include <bits/stdc++.h>
using namespace std;

const int N = 60;

class EllysLamps {
public:
    int getMin(string lamp) {
        int n = lamp.size();
        static int dp[N]; memset(dp, 0, sizeof(dp));
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            int ct = 0;
            for (int j = i; j >= 1; j--) {
                ct += lamp[j - 1] == 'Y';
                dp[i] = max(dp[i], dp[j - 1] + ((ct & 1) && (i != j)));
            }
        }
        return dp[n];
    }
};

// int main() {
//     EllysLamps solver;
//     cout << solver.getMin("YNYYYNNNY") << endl;
// }