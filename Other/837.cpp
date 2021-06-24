#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef long long LL;

LL num[N];

int main() {
    int n; LL m, k; cin >> n >> m >> k;
    auto get = [&](int a, int t) {
        int res = ((a - t) % n + n) % n;
        return res ? res : n;
    };
    LL turn = m / k + 1, pos = (turn - 1) % n + 1, tmp = m % k, step = (n + k - 1) / k;
    LL first = (n - tmp + k - 1) / k;
    int t = get(pos, first);
    if (first * k + tmp <= m) for (int i = 1; i <= n; i++) num[i]++;
    num[t] += tmp + first * k - n, pos = get(t, step);
    if ((first + step) * k + tmp > m) {
        for (int i = 1; i <= n; i++) printf("%d ", num[i]);
        return 0;
    }
    LL delta = step * k - n, all = ((m - tmp) / k - first) / step;
    vector<LL> fuck = {pos}; LL nw = pos; 
    while (233) {
        nw = get(nw, step);
        if (nw == pos) break;
        fuck.push_back(nw);
    }
    LL hh = all / fuck.size();
    for (auto t : fuck) num[t] += delta * hh;
    for (LL nw = pos, t = hh * fuck.size() + 1; t <= all; t++) {
        num[nw] += delta;
        nw = ((nw - step) % n + n) % n;
        if (nw == 0) nw = n;
    }
    for (int i = 1; i <= n; i++) printf("%lld ", num[i] + all);
}