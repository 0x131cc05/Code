#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
const int mod = 1e9 + 7;

typedef long long LL;
typedef pair<LL, LL> P;

int dp[N], L[N], R[N];

bool check(P a, P b) {
    return a.second < b.first || a.first > b.second;
}

vector<int> seg[N];

struct FrozenStandings {
    int countStandings(int n, int a, int seed) {
        vector<P> vec;
        for (int i = 1; i <= n; i++) {
            seed = (LL)seed * 20142014 % mod;
            int x = seed % a;
            vec.push_back(P((LL)-(x + 1) * mod + i, (LL)-x * mod + i));
        }
        sort(vec.begin(), vec.end());
        for (int i = 1, j = 1; i <= n; i++) {
            while (check(vec[j - 1], vec[i - 1])) j++;
            L[i] = j;
        }
        for (int i = n, j = n; i >= 1; i--) {
            while (check(vec[j - 1], vec[i - 1])) j--;
            R[i] = j, seg[R[i]].push_back(L[i]);
        }
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i - 1] * 2 % mod;
            for (auto t : seg[i]) dp[i] = (dp[i] - dp[t - 1] + mod) % mod;
        }
        return dp[n];
    }
};

// int main() {
//     FrozenStandings solver;
//     cout << solver.countStandings(20, 4, 765276374) << endl;
// }
