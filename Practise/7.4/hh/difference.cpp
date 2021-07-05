#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

typedef long long LL;

const LL INF = 1e18;

template<class T> void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

set<LL> s; LL l, r, add, val[N];
int sgn;

LL w[N], delta[N];
bool ok[N];

int main() {
    freopen("difference.in", "r", stdin), freopen("difference.out", "w", stdout);
    int n; LL C; read(n), read(C);
    for (int i = 1; i <= n - 2; i++) read(w[i]);
    l = 0, r = w[1];
    auto check = [&]() {
        if (l <= r) return true;
        return !s.empty();
    };
    auto get = [&]() {
        if (l <= r) return l;
        if (s.size()) {
            LL t = *s.begin();
            if (sgn) t = -t;
            return t + add;
        }
        return INF;
    };
    for (int i = 1; i <= n - 2; i++) {
        r = min(r, w[i]);
        auto cover = [&](LL x) {
            if (l <= x && x <= r) return true;
            LL tmp = x - add;
            if (sgn) tmp = -tmp;
            return !!s.count(tmp);
        };
        auto insert = [&](LL x) {
            x -= add;
            if (sgn) x = -x;
            s.insert(x);
        };
        while (s.size()) {
            LL a = sgn ? *s.begin() : *s.rbegin();
            LL t = sgn ? -a : a;
            if (t + add > w[i]) s.erase(a);
            else break;
        }
        val[i] = get();
        bool cL = cover(w[i]);
        bool L = check();
        LL l1 = l, r1 = r;
        r = w[i] - l1, l = w[i] - r1;
        sgn ^= 1, add = w[i] - add;
        if (L) insert(w[i]);
        if (cL) l = 0, r = w[i], s.clear(), sgn = add = 0, ok[i] = 1;
    }
    if (check()) puts("YES");
    else return puts("NO"), 0;
    delta[n - 1] = get();
    for (int i = n - 2; i >= 1; i--) {
        LL lst = delta[i + 1];
        if (w[i] != abs(lst)) {
            if (ok[i]) lst = lst < 0 ? w[i] : -w[i];
            else lst = lst < 0 ? -w[i] - lst : w[i] - lst;
        } else {
            lst = lst < 0 ? val[i] : -val[i];
        }
        delta[i] = lst;
    }
    LL mn = 0;
    for (int i = 1; i <= n - 1; i++) 
        delta[i] += delta[i - 1], mn = min(mn, delta[i]);
    for (int i = 0; i <= n - 1; i++) 
        printf("%lld ", delta[i] - mn); 
}