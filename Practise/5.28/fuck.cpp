#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> P;

LL x, y;

LL exgcd(LL a, LL b) {
    if (!b) return x = 1, y = 0, a;
    LL g = exgcd(b, a % b), t = x;
    x = y, y = t - a / b * y;
    return g;
}

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    int n, a, b; cin >> n >> a >> b;
    int g = exgcd(a, b);
    LL base = n * g / gcd(g, n);
    LL X1 = x * base / g, Y1 = y * base / g, X2 = b / g, Y2 = -a / g;
    int g1 = exgcd(Y1, n); LL x1 = x;
    int g2 = exgcd(Y2, n); LL x2 = x;
    int dy1 = abs(n / g1), dy2 = abs(n / g2);
    int g3 = exgcd(dy1, dy2); LL x3 = x;
    vector<P> res;
    for (int a1 = 0; a1 < n; a1++) {
        int t1 = (LL)a1 * X1 % n, t2 = (LL)a1 * X2 % n;
        if (t1 % g1 || t2 % g2) continue;
        LL y1 = x1 * (-t1 / g1), dy1 = abs(n / g1);
        LL y2 = x2 * (-t2 / g2), dy2 = abs(n / g2);
        y1 = (y1 % dy1 + dy1) % dy1, y2 = (y2 % dy2 + dy2) % dy2;
        if ((y1 - y2) % g3) continue;
        LL d = y2 - y1; LL hh = x3 * (d / g3), t = dy2 / g3;
        hh = (hh % t + t) % t;
        for (; dy1 * hh + y1 < n; hh += t)
            res.push_back(P(a1, dy1 * hh + y1));
    }
//    printf("%d\n", res.size());
    for (auto t : res) printf("%d %d\n", t.first, t.second);
}
