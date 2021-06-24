#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
const int mod = 1e9 + 7;

typedef long long LL;

int tp;

bitset<N> base[N];

bool insert(bitset<N> x) {
    for (int i = 1; i <= tp; i++) if (x[i]) {
        if (!base[i].any()) return base[i] = x, true;
        x ^= base[i];
    } 
    return false;
}

map<int, int> mp;

class PerfectSquare {
public:
    int ways(vector<int> x) {
        int n = sqrt(x.size());
        vector<bitset<N>> ins;
        tp = 2 * n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                int cur = (i - 1) * n + j - 1, tmp = x[cur];
                bitset<N> nw; nw[i] = nw[j + n] = 1;
                auto push = [&](int x) {
                    int pos = mp.count(x) ? mp[x] : mp[x] = ++tp;
                    nw[pos] = 1;
                };
                for (int t = 2; t * t <= tmp; t++) if (tmp % t == 0) {
                    int ct = 0;
                    while (tmp % t == 0) ct ^= 1, tmp /= t;
                    if (ct) push(t);
                }
                if (tmp != 1) push(tmp);
                ins.push_back(nw);
            }
        int ct = 0, res = 1;
        for (auto t : ins) if (!insert(t)) ct++, res = res * 2 % mod;
        bitset<N> lst;
        for (int i = 1; i <= 2 * n; i++) lst[i] = 1;
        if (insert(lst)) return 0;
        return res;
    }
};

// int main() {
//     PerfectSquare solver;
//     cout << solver.ways(
// {2, 3, 4, 5,
//  6, 7, 8, 9,
//  10,11,12,13,
//  14,15,16,17}
// ) << endl;
// }