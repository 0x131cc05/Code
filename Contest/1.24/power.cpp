#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> P;

int mod;

int Pow(int x, int y, int mod = ::mod) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int G(int x) {
    if (x == 2) return 1;
    for (int i = 2, flg = 1; i; i++, flg = 1) {
        for (int j = 2; j * j < x; j++) 
            if ((x - 1) % j == 0 && Pow(i, (x - 1) / j, x) == 1) { flg = 0; break; }
        if (flg) return i;
    }
}

int g, m, step;

unordered_map<int, int> mp;

void init() {
    g = G(mod), m = sqrt(mod) + 1;
    int nw = 1;
    for (int i = 1; i <= m; i++) 
        nw = (LL)nw * g % mod, mp[nw] = i;
    step = nw;
}

int x, y;

int exgcd(int a, int b) {
    if (!b) return x = 1, y = 0, a;
    int g = exgcd(b, a % b);
    int t = x; x = y, y = t - a / b * y;
    return g;
}

int solve(int x) {
    x = Pow(x, mod - 2);
    for (int i = 1, nw = x; i <= m; i++) {
        nw = (LL)nw * step % mod;
        if (mp.count(nw)) return i * m - mp[nw];
    }
    assert(0);
}

int wkr[2010];

int main() {
    freopen("power.in", "r", stdin), freopen("power.out", "w", stdout);
    int T; scanf("%d%d", &mod, &T), init();
    for (int i = max(1, mod - 2000), step = 1; i < mod; i++, step++) 
        wkr[step] = solve(i);
    while (T--) {
        int a; scanf("%d", &a);
        if (a == 1) { printf("%d\n", mod); continue; }
        vector<P> res;
        int lim = min(500000, mod - 1), mx = 0;
        for (int i = 0, nw = 1; i <= lim; i++) {
            if (nw > mx) res.push_back(P(i, nw)), mx = nw;
            nw = (LL)nw * a % mod;
        }
        int step = solve(a), g = exgcd(step, mod - 1), hh = (mod - 1) / g;
        for (int i = max(1, mod - 2000), fuck = 1; i < mod; i++, fuck++) {
            int p = wkr[fuck];
            if (p % g) continue;
            int tx = ((LL)x * (p / g) % hh + hh) % hh;
            res.push_back(P(tx, i));
        }
        sort(res.begin(), res.end()), res.push_back(P(mod, mod + 1));
        LL ans = 0;
        for (int i = 0; i + 1 < res.size(); i++) {
            int j = i;
            while (j + 1 < res.size() && res[j + 1].second <= res[i].second) j++;
            ans += (LL)(res[j + 1].first - res[i].first) * res[i].second;
            i = j;
        }
        printf("%lld\n", ans);
    }
}
