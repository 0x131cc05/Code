#include <bits/stdc++.h>
using namespace std;

const int N = 300010;

typedef long long LL;

int n; LL num[N], all;

int c;

void solve() {
    int pos; LL all = 0;
    for (int i = 1; i <= n; i++) all += num[i];
    LL re = 0, res = 0, p = 0, lst = 0;
    for (int i = 1; i <= n; i++) {
        all -= num[i];
        LL nw = num[i] / c, t = num[i] % c;
        if (t <= re) re -= t;
        else t -= re, re = 0, res += t;
        res += nw * c, re += nw;
        lst = nw;
        if (re >= all) break;
    }
    LL fuck = re - all;
    LL h = fuck / (c + 1) * c;
    res -= h, fuck %= c + 1;
    // if (fuck >= 1) fuck--, res -= fuck;
    printf("%lld\n", res);
}

int main() {
    // freopen("b1_1.in", "r", stdin), freopen("b.out", "w", stdout);
    int q; scanf("%d%d%d", &n, &q, &c);
    for (int i = 1; i <= n; i++) scanf("%lld", &num[i]);
    solve();
    while (q--) {
        int a; LL b; scanf("%d%lld", &a, &b), num[a] = b;
        solve();
    }
}