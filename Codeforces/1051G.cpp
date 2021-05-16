#include <bits/stdc++.h>
using namespace std;

const int N = 400010;

typedef long long LL;

struct node {
    int ls, rs, sz; LL res, sum;
} T[N * 32];

int ncnt;

void pushup(int rt) {
    int ls = T[rt].ls, rs = T[rt].rs;
    T[rt].sum = T[ls].sum + T[rs].sum, T[rt].sz = T[ls].sz + T[rs].sz;
    T[rt].res = T[ls].res + T[rs].res + (LL)T[rs].sz * T[ls].sum; 
}

void update(int &rt, int l, int r, int x) {
    if (!rt) rt = ++ncnt;
    if (l == r) return T[rt].sum = T[rt].res = x, T[rt].sz = 1, void();
    int mid = (l + r) >> 1;
    if (x <= mid) update(T[rt].ls, l, mid, x);
    else update(T[rt].rs, mid + 1, r, x);
    pushup(rt);
}

void merge(int &x, int y, int l, int r) {
    if (!x || !y) return x |= y, void();
    assert(l != r);
    int mid = (l + r) >> 1;
    merge(T[x].ls, T[y].ls, l, mid), merge(T[x].rs, T[y].rs, mid + 1, r), pushup(x);
}

int rt[N], fa[N], sz[N]; LL res[N], sum[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

set<int> s;

int main() {
    int n; scanf("%d", &n);
    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        int a, b, f; scanf("%d%d", &a, &b);
        auto pos = s.upper_bound(a);
        if (pos == s.begin()) f = fa[a] = a, s.insert(a);
        else {
            pos--;
            if (*pos + sz[*pos] >= a) f = *pos;
            else f = fa[a] = a, s.insert(a);
        }
        ans -= T[rt[f]].res, update(rt[f], 1, n, b), ans += T[rt[f]].res;
        LL tmp = (LL)(a - f + 1) * b; ans -= tmp, res[f] += tmp, sz[f]++, sum[f] += b;
        while (233) {
            int nxt = f + sz[f];
            if (fa[nxt]) {
                int t = find(nxt);
                ans -= T[rt[f]].res + T[rt[t]].res, merge(rt[f], rt[t], 1, n), ans += T[rt[f]].res;
                ans += res[f] + res[t], sz[f] += sz[t], fa[t] = f, s.erase(t);
                res[f] += res[t] + (LL)(t - f) * sum[t], sum[f] += sum[t], ans -= res[f];
            } else break;
        }
        printf("%lld\n", ans);
    } 
}