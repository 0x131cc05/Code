#include <bits/stdc++.h>
using namespace std;

const int N = 60;

struct PointErasing {
    vector<int> getOutcomes(vector<int> y) {
        int mx = *max_element(y.begin(), y.end()), mn = *min_element(y.begin(), y.end()), n = y.size();
        int L = -1, R = 0, ct = 0;
        for (int i = 0; i < y.size(); i++) {
            if (y[i] == mx || y[i] == mn) {
                if (!~L) L = i;
                R = i, ct++;
            }
        }
        auto process = [&](int l, int r, int pos, int useless) {
            vector<int> p, seg[N];
            for (int i = l; i <= r; i++) if (y[i] == pos) p.push_back(i);
            auto push = [&](int L, int R) {
                int a = upper_bound(p.begin(), p.end(), L) - p.begin();
                int b = lower_bound(p.begin(), p.end(), R) - p.begin() - 1;
                if (a <= b) seg[b].push_back(a);
            };
            for (int i = l; i <= r; i++) if (y[i] != pos) {
                for (int j = i + 1; j <= r; j++) if (y[j] != pos) {
                    if (min(y[i], y[j]) < pos && max(y[i], y[j]) > pos) 
                        push(i, j);
                }
                if (useless < i) push(useless, i);
                else push(i, useless);
            }       
            static int dp[N][N]; memset(dp, 0, sizeof(dp)), dp[0][0] = 1;
            for (int i = 1; i <= p.size(); i++) {
                for (int j = 1; j <= i; j++) dp[i][j] = dp[i - 1][j - 1];
                for (auto t : seg[i - 1]) {
                    for (int j = 0; j <= i; j++) dp[i][j] |= dp[t][j];
                }
            }
            vector<int> res;
            for (int i = 0; i <= p.size(); i++)
                if (dp[p.size()][i]) res.push_back(i);
            return res;
        };
        auto A = process(0, L - 1, y[0], 1e9), B = process(R + 1, n - 1, y.back(), 0);
        vector<int> res;
        for (auto a : A) for (auto b : B) res.push_back(a + b + ct);
        sort(res.begin(), res.end()), res.resize(unique(res.begin(), res.end()) - res.begin());
        return res;
    }
};

// int main() {
//     PointErasing solver;
//     auto res = solver.getOutcomes({ 5, 5, 4, 4, 5, 8, 5, 5, 5, 5, 5, 9, 2, 0, 9, 4, 5, 5, 3, 4, 4, 4, 4, 7, 4 });
//     copy(res.begin(), res.end(), ostream_iterator<int>(cout, ", "));
// }