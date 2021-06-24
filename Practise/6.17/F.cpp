#include <bits/stdc++.h>
#include "atcoder/mincostflow.hpp"
using namespace std;

using namespace atcoder;

const int N = 500020;

typedef long long LL;

typedef pair<int, int> P;

int main() {
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    mcf_graph<int, LL> g(N);
    vector<P> p(n + 1);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &p[i].first, &p[i].second);
    sort(p.begin() + 1, p.end(), [&](P a, P b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });
    int ct = 0;
    for (int i = 1; i <= n; i++) {
        if (ct && p[i].first == p[ct].first) continue;
        while (ct && p[i].second >= p[ct].second) ct--;
        p[++ct] = p[i];
    }
    n = ct, p.resize(n + 1);
    int s = N - 10;
    g.add_edge(s, 1, k, 0);
    for (int i = 2; i <= n + 1; i++) 
        g.add_edge(i, i - 1, 1e9, 0);
    for (int i = 1; i <= n; i++)
        g.add_edge(i, i + n + 1, 1e9, 0), g.add_edge(i + 2 * n + 1, i + 1, 1e9, 0);
    for (int i = 2; i <= n; i++)
        g.add_edge(i + n, i + n + 1, 1e9, p[i - 1].second - p[i].second);
    for (int i = n; i >= 2; i--)
        g.add_edge(i + 2 * n, i + 2 * n + 1, 1e9, p[i].first - p[i - 1].first);
    int ncnt = 3 * n + 1;
    for (int i = 1; i <= m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        int A = ++ncnt, B = ++ncnt; g.add_edge(A, B, 1, 0);
        int l = lower_bound(p.begin() + 1, p.end(), P(-1e9, y), [&](P a, P b) {
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        }) - p.begin();
        if (l <= n) g.add_edge(l + n + 1, A, 1, 0);
        if (l != 1) g.add_edge(l + n, A, 1, p[l - 1].second - y);
        int r = upper_bound(p.begin() + 1, p.end(), P(x, 1e9)) - p.begin() - 1;
        if (r >= 1) g.add_edge(B, r + 2 * n + 1, 1, 0);
        if (r != n) g.add_edge(B, r + 2 * n + 2, 1, p[r + 1].first - x);
    }
    auto res = g.flow(s, n + 1); 
    printf("%lld\n", res.second);
}