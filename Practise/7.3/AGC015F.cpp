#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> P;

const int mod = 1e9 + 7;

LL fib[110];

vector<P> ok[110];

LL X, Y;

int mx;

void calc() {
    LL x = 1, y = 2; mx = 0;
    while (x <= X && y <= Y) 
        mx++, x += y, swap(x, y);
    mx = max(mx, 1);
}

LL count(LL x, LL y, int layer) {
    if (x > y) swap(x, y);
    if (x > X || y > Y) return 0;
    int delta = mx - layer;
    LL tx = x * fib[delta] + y * fib[delta + 1], ty = x * fib[delta - 1] + y * fib[delta];
    if (tx > ty) swap(tx, ty);
    if (tx > X || ty > Y) return 0;
    LL res = 0;
    if (y <= X) {
        if (layer + 1 != mx) for (int i = 1; i; i++) {
            LL w = count(x + y * i, y, layer + 1);
            if (!w) break;
            res += w;
        } else {
            ok[mx].push_back(P(x, y));
            return (Y - x) / y + (X - x) / y;
        }
    }
    return res;
}

int main() {
    fib[1] = fib[2] = 1;
    for (int i = 3; i <= 88; i++) fib[i] = fib[i - 1] + fib[i - 2];
    for (int i = 1; i <= 84; i++) {
        X = Y = fib[i + 4] - 1;
        calc(), count(1, 1, 0);
    }
    int q; scanf("%d", &q);
    while (q--) {
        LL x, y; scanf("%lld%lld", &x, &y);
        if (x > y) swap(x, y);
        X = x, Y = y, calc(); 
        int lst = mx; LL res = 0;
        if (mx == 1) res = x * y;
        else for (auto t : ok[mx])
            if (t.second <= X) 
                res += (X - t.first) / t.second + (Y - t.first) / t.second;
        printf("%d %lld\n", lst, res % mod);
    }
}