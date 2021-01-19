#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int n, all;

int nxt(int x) {
    return (x ^ (x << 1) ^ (x >> (n - 1))) & all;
}

bitset<1 << 26> A, B;

struct DifferenceSequence {
    vector<LL> kthSmallestRepresentative(int n, LL k) {
        if (k == 1) return vector<LL>(n);
        all = (1 << n) - 1, ::n = n, k -= 2;
        vector<int> ans;
        for (int s = 0; s < 1 << n; s++) {
            if (B[s]) continue;
            int nw = s, res = 0;
            vector<int> pos;
            while (!A[nw]) A[nw] = 1, pos.push_back(nw), nw = nxt(nw);
            while (!B[nw]) B[nw] = 1, res = max(res, nw), nw = nxt(nw);
            for (auto t : pos) B[t] = 1;
            if (res > 0) ans.push_back(res);
        } 
        if (!ans.size()) return {};
        sort(ans.begin(), ans.end());
        LL per = k / ans.size(); int at = k % ans.size();
        vector<LL> res;
        for (int i = 1; i <= n; i++) 
            res.push_back(((ans[at] >> (n - i)) & 1) * (per + 1));
        return res;
    }
};

// int main() {
//     DifferenceSequence solver;
//     auto res = solver.kthSmallestRepresentative(4, 470000000000);
//     copy(res.begin(), res.end(), ostream_iterator<LL>(cout, " "));
// }