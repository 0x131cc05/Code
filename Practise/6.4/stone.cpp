#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef pair<int, int> P;
typedef long long LL;

struct node {
    int l, r, mn; 
} T[N << 2];

void pushup(int rt) {
    T[rt].mn = min(T[rt << 1].mn, T[rt << 1 | 1].mn);
}

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r, T[rt].mn = 1e9; 
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
}

void push(int rt, int x, int y, int tp) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l == r) {
        if (tp) T[rt].mn = y;
        else T[rt].mn = 1e9;
        return;
    }
    if (x <= mid) push(rt << 1, x, y, tp);
    else push(rt << 1 | 1, x, y, tp);
    pushup(rt);
}

int find(int rt, int x) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l == r) return T[rt].mn;
    if (x > mid) return find(rt << 1 | 1, x);
    return min(find(rt << 1, x), T[rt << 1 | 1].mn);
}

int v[N], col[N], n; set<int> appear[N];

LL tree[N];

void upd(int x, int y) {
    for (; x <= n; x += x & -x) tree[x] += y;
}

LL que(int x) {
    LL res = 0;
    for (; x; x -= x & -x) res += tree[x];
    return res;
}

LL que(int l, int r) {
    return que(r) - que(l - 1);
}

bool buk[N]; int mx[N];

int main() {
    freopen("stone.in", "r", stdin), freopen("stone.out", "w", stdout);
    int m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &col[i], &v[i]), upd(i, v[i]);
        appear[col[i]].insert(i);
    }
    build(1, 1, n);
    for (int i = 1; i <= n; i++) if (appear[i].size() > 1) {
        int ls = 0;
        for (auto t : appear[i]) {
            if (ls) push(1, ls, t, 1);
            ls = t;
        }
    }
    while (m--) {
        int op, a, b, c; scanf("%d%d%d", &op, &a, &b);
        if (op == 1) {
            scanf("%d", &c);
            auto pos = appear[col[a]].find(a);
            int l = 0, r = 0;
            if (pos != appear[col[a]].begin()) {
                auto tmp = pos; tmp--, l = *tmp;
                push(1, *tmp, a, 0);
            }
            auto tmp = pos; tmp++;
            if (tmp != appear[col[a]].end()) {
                r = *tmp, push(1, a, *tmp, 0);
            }
            if (l && r) push(1, l, r, 1);
            appear[col[a]].erase(a);
            col[a] = b, l = 0, r = 0;
            appear[col[a]].insert(a);
            pos = appear[col[a]].find(a);
            if (pos != appear[col[a]].begin()) {
                auto tmp = pos; tmp--, l = *tmp;
            }
            tmp = pos; tmp++;
            if (tmp != appear[col[a]].end()) r = *tmp;
            if (l && r) push(1, l, r, 0);
            if (l) push(1, l, a, 1);
            if (r) push(1, a, r, 1);
            upd(a, c - v[a]), v[a] = c;
        } else {
            int ct = 0, pos = a, r = n;
            vector<int> fuck; vector<P> era;
            while (233) {
                pos = find(1, a), ct++;
                if (pos > n || ct > b) {
                    r = min(n, pos - 1); break;
                }
                int l = *--appear[col[pos]].find(pos);
                push(1, l, pos, 0), era.push_back(P(l, pos));
                fuck.push_back(pos);
            }
            for (auto t : era) push(1, t.first, t.second, 1);
            vector<int> c;
            for (auto t : fuck) 
                if (!buk[col[t]])
                    buk[col[t]] = 1, c.push_back(col[t]);
            for (auto t : c) buk[t] = 0;
            for (auto t : c) 
                fuck.push_back(*appear[t].lower_bound(a));
            LL res = que(a, r);
            for (auto t : fuck) 
                mx[col[t]] = max(mx[col[t]], v[t]), res -= v[t];
            for (auto t : c) res += mx[t], mx[t] = 0;
            printf("%lld\n", res);
        }
    }
}