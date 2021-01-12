#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> P;
typedef long long LL;

int main() {
    map<P, vector<P>> go; map<P, int> cost[2];
    int n, d; scanf("%d%d", &n, &d);
    for (int i = 1, ls = -1; i <= d; i++) {
        int a; scanf("%d", &a);
        if (~ls) {
            if (ls < a) go[P(ls, a)].push_back(P(i, 0));
            else go[P(a, ls)].push_back(P(i, 1));
        }
        ls = a;
    }
    int m; scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        char s[5]; int x, y, c; scanf("%d%d%s%d", &x, &y, s + 1, &c);
        int type = s[1] == 'R';
        if (!cost[type].count(P(x, y))) cost[type][P(x, y)] = 1e9;
        cost[type][P(x, y)] = min(cost[type][P(x, y)], c);
    }
    auto get = [&](int type, int from, int to) -> LL {
        if (cost[type].count(P(from, to))) return cost[type][P(from, to)];
        return 1e15;
    };
    LL res = 0;
    for (auto [A, B] : go) {
        int u = A.first, v = A.second;
        LL A0 = get(0, u, v), B0 = get(0, v, u), A1 = get(1, u, v), B1 = get(1, v, u);
        A0 = min(A0, A1), B0 = min(B0, B1), A1 = min(A1, A0 + B0), B1 = min(B1, B0 + A0);
        // cout << u << ' ' << v << ' ' << A0 << ' ' << B0 << ' ' << A1 << ' ' << B1 << endl;
        auto tmp = B;
        if (A1 > B1) {
            swap(A0, B0), swap(A1, B1);
            for (auto &t : tmp) t.second ^= 1;
        }
        int c0 = 0, c1 = 0, ct = 0;
        for (auto t : tmp) {
            if (!t.second) c0++;
            else {
                if (c0) c0--, ct++;
                else c1++;
            }
        }
        int c2 = min(c0, c1);
        res += (LL)ct * A1 + (LL)c2 * B1 + (LL)(c0 - c2) * A0 + (LL)(c1 - c2) * B0;
    }
    printf("%lld\n", res);
}