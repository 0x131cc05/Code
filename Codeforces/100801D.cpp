#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL pw[70];

vector<LL> dfs(LL n, int a, int b) {
    if (a < 0 || b < 0) return {};
    if (n == 1) return { 1 };
    if (n % 2 == 0) {
        auto res = dfs(n / 2, a - 1, b);
        for (auto &t : res) t *= 2;
        return res;
    }
    if (n % 3 == 0) {
        auto res = dfs(n / 3, a, b - 1);
        for (auto &t : res) t *= 3;
        return res;
    }
    for (int i = b; i >= 1; i--) {
        LL tmp = pw[i];
        if (tmp > n) continue;
        if ((n - tmp) % 2 == 0) {
            auto res = dfs((n - tmp) / 2, a - 1, i - 1);
            if (!res.size()) continue;
            for (auto &t : res) t *= 2;
            res.push_back(tmp);
            return res;
        }
    }
    return {};
}

int main() {
    freopen("distribution.in", "r", stdin), freopen("distribution.out", "w", stdout);
    int T; scanf("%d", &T), pw[0] = 1;
    for (int i = 1; i <= 40; i++) pw[i] = pw[i - 1] * 3;
    while (T--) {
        LL n; scanf("%lld", &n); int a = 0, b = 0;
        LL tmp = n;
        while (tmp) a++, tmp /= 2;
        tmp = n;
        while (tmp) b++, tmp /= 3;
        // cout << a << ' ' << b << endl;
        auto res = dfs(n, a, b);
        printf("%d\n", res.size());
        for (auto t : res) printf("%lld ", t);
        puts("");
    }
}