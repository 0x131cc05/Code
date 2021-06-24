#include <bits/stdc++.h>
using namespace std;

const int N = 50010;

typedef long long LL;

struct Line { LL b, k; int id; };

struct Convex {
    vector<Line> l, stk;
    
    void push(Line line) { l.push_back(line); }
    void clear() { l.clear(); }
    void build() {
        stk.clear();
        auto check = [](Line a, Line b, Line c) {
            return (b.b - a.b) * (a.k - c.k) > (c.b - a.b) * (a.k - b.k);
        };
        for (auto t : l) {
            if (stk.size() && stk.back().k == t.k) continue;
            while (stk.size() >= 2 && check(stk[(int)stk.size() - 2], stk.back(), t)) stk.pop_back();
            stk.push_back(t);
        }
    }

    double query(double pos, int &id) {
        int l = 1, r = (int)stk.size() - 1, mid, res = 0;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (stk[mid - 1].b - stk[mid].b < pos * (stk[mid].k - stk[mid - 1].k)) res = mid, l = mid + 1;
            else r = mid - 1;
        }
        id = stk[res].id;
        return stk[res].b + stk[res].k * pos;
    }
} wkr[300];

int n;

struct BIT {
    LL tree[N];
    void upd(int x, int y) { for (; x <= n; x += x & -x) tree[x] += y; }
    LL que(int x) {
        LL res = 0;
        for (; x; x -= x & -x) res += tree[x];
        return res;
    }
} T[2];

int belong[N], sz, num[N];

void rebuild(int bl) {
    int L = (bl - 1) * sz + 1, R = min(n, bl * sz);
    wkr[bl].clear(); 
    LL A = 0, B = 0;
    for (int i = L; i <= R; i++) {
        if (num[i] < 0) A += num[i];
        else B += num[i];
        wkr[bl].push((Line){ A, B, i });
    }
    wkr[bl].build();
}

void update(int x, int v) {
    bool type = num[x] > 0;
    T[type].upd(x, -abs(num[x])), type = v > 0, T[type].upd(x, abs(v)), num[x] = v, rebuild(belong[x]);
}

int query() {
    LL A = T[0].que(n), B = T[1].que(n); double res = -1e18, p = (double)A / B; int pos = 0;
    for (int i = 1; i <= belong[n]; i++) {
        int l = (i - 1) * sz + 1, tmp;
        LL s0 = T[0].que(l - 1), s1 = T[1].que(l - 1);
        double nw = wkr[i].query(p, tmp) - (double)s0 + (double)s1 * p;
        if (nw > res + 1e-10) res = nw, pos = tmp;
    }
    return pos;
}

int main() {
    freopen("joker.in", "r", stdin), freopen("joker.out", "w", stdout);
    int m; scanf("%d%d", &n, &m), sz = sqrt(n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &num[i]), belong[i] = (i + sz - 1) / sz;
        int t = num[i] > 0;
        T[t].upd(i, abs(num[i]));
    }
    for (int i = 1; i <= belong[n]; i++) rebuild(i);
    printf("%d\n", query());
    while (m--) {
        int a, b; scanf("%d%d", &a, &b), update(a, b);
        printf("%d\n", query());
    }
}