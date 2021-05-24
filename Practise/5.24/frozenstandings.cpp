#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
const int mod = 1e9 + 7;

typedef long long LL;
typedef pair<int, int> P;

int dp[N];

struct FrozenStandings {
    int countStandings(int n, int a, int seed) {
        vector<P> vec;
        for (int i = 1; i <= n; i++) {
            seed = (LL)seed * 20142014 % mod;
            vec.push_back(P(-(seed % a), i));
        }
        sort(vec.begin(), vec.end()), dp[0] = 1;
        for (int i = 1, j = 1; i <= n; i++) {
            while (j < i && vec[j] < P(vec[i - 1].first - 1, vec[i - 1].second)) j++;
            dp[i] = dp[i - 1] * 2;
            if (j + 1 < i && vec[j - 1].first == vec[i - 1].first - 1) dp[i] -= dp[j];
            dp[i] = (dp[i] % mod + mod) % mod;
        }
        return dp[n];
    }
};

int main() {
    FrozenStandings solver;
    cout << solver.countStandings(8, 2, 667363653) << endl;
}
