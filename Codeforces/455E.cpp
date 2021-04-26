#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

struct Line { 
    LL k, b; 
    LL get(int x) { return k * x + b; }
} line[N];

struct node {
    int l, r; vector<int> v;
} T[N << 2];

bool check(Line a, Line b, Line c) {
    return (LL)(c.b - a.b) * (a.k - b.k) <= (LL)(b.b - a.b) * (a.k - c.k);
}

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return T[rt].v = { l }, void();
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
    vector<int> nw; 
    merge(T[rt << 1].v.begin(), T[rt << 1].v.end(), T[rt << 1 | 1].v.begin(), T[rt << 1 | 1].v.end(), 
        back_inserter(nw), [&](int a, int b) { 
            if (line[a].k != line[b].k) return line[a].k > line[b].k;
            return line[a].b < line[b].b; 
        });
    for (auto t : nw) {
        auto& v = T[rt].v;
        if (v.size() && line[t].k == line[v.back()].k) continue;
        if (v.size() < 2) { v.push_back(t); continue; }
        while (v.size() >= 2 && check(line[v[(int)v.size() - 2]], line[v[(int)v.size() - 1]], line[t])) 
            v.pop_back();
        v.push_back(t);
    }
}

LL query(int rt, int start, int end, int x) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) {
        auto &v = T[rt].v;
        LL res = line[*v.begin()].get(x); int tl = 1, tr = (int)v.size() - 1;
        while (tl <= tr) {
            int tmp = (tl + tr) >> 1; LL hh = line[v[tmp]].get(x);
            if (hh <= line[v[tmp - 1]].get(x)) res = min(res, hh), tl = tmp + 1;
            else tr = tmp - 1;
        }
        return res;
    }
    if (end <= mid) return query(rt << 1, start, end, x);
    if (start > mid) return query(rt << 1 | 1, start, end, x);
    return min(query(rt << 1, start, end, x), query(rt << 1 | 1, start, end, x));
}

int a[N], s[N];

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]), s[i] = s[i - 1] + a[i];
        line[i] = { a[i], i * a[i] - s[i] };
    }
    build(1, 1, n);
    int q; scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%lld\n", query(1, r - l + 1, r, l - r) + s[r]);
    }
}