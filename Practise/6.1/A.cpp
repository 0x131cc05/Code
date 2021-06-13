#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 300010;

struct line {
    int k; LL b;
    line operator+ (line t) { return { k + t.k, b + t.b }; }
    LL get(LL x) { return x * k + b; }
} poolA[N * 2], poolB[N * 2], poolC[N * 2];

LL get(int &head, line* A, int sz, LL x) {
    while (head + 1 < sz && A[head + 1].get(x) >= A[head].get(x)) head++;
    return A[head].get(x);
}

bool check(line a, line b, line c) {
    return (double)(a.b - b.b) * (c.k - a.k) >= (double)(a.b - c.b) * (b.k - a.k);
}

line tmp[N]; int sz;

void push(line l) {
    if (l.b < -5e15) return;
    if (sz && l.k <= tmp[sz - 1].k) return;
    while (sz >= 2 && check(tmp[sz - 2], tmp[sz - 1], l)) sz--;
    tmp[sz++] = l;
}

void upd(line l) {
    tmp[l.k].b = max(tmp[l.k].b, l.b);
}

void add(line* A, int szA, line* B, int szB) { // single point
    int p = 0, q = 0;
    while (p + 1 < szA || q + 1 < szB) {
        if (p + 1 == szA) { upd(A[p] + B[q++]); continue; }
        if (q + 1 == szB) { upd(A[p++] + B[q]); continue; }
        upd(A[p] + B[q]);
        LL a = (LL)(A[p].b - A[p + 1].b) * (B[q + 1].k - B[q].k);
        LL b = (LL)(B[q].b - B[q + 1].b) * (A[p + 1].k - A[p].k);
        if (a <= b) p++;
        if (b <= a) q++;
    }
    upd(A[p] + B[q]);
}

void reduce() {
    int hh = sz; sz = 0;
    for (int i = 0; i < hh; i++) push(tmp[i]);   
}

int m;

struct query {
    LL ans, sufL, x;
    int l, r, id;
} q[N * 2];

void merge(line* A, int sz1, line *B, int sz2, line diff) {
    sz = sz1 + sz2;
    for (int i = 0; i < sz1; i++) tmp[i] = A[i];
    for (int i = 0; i < sz2; i++) tmp[sz1 + i] = B[i] + diff;
    reduce();
}

int num[N];

LL build(int rt, int l, int r, line* pre, int &sz1, line* suf, int &sz2, line* res, int &sz3, vector<int> &o) {
    LL sum;
    int mid = (l + r) >> 1;
    vector<int> w1, w2;
    if (l == r) {
        sz1 = sz2 = sz3 = 2;
        pre[0] = suf[0] = res[0] = { 0, 0 };
        pre[1] = suf[1] = res[1] = { 1, num[l] };
        sum = num[l];
    } else {
        int diff = (mid - l + 1) * 2;
        line *pre1 = pre + diff, *suf1 = suf + diff, *res1 = res + diff;
        int rsz1 = 0, rsz2 = 0, rsz3 = 0;
        for (auto t : o) {
            if (q[t].l <= l && q[t].r >= r) continue;
            if (q[t].l <= mid && q[t].r > mid) {
                w1.push_back(t), w2.push_back(t); 
            }
            if (q[t].r <= mid) w1.push_back(t);
            if (q[t].l > mid) w2.push_back(t);
        }
        LL lsum = build(rt << 1, l, mid, pre, sz1, suf, sz2, res, sz3, w1);
        LL rsum = build(rt << 1 | 1, mid + 1, r, pre1, rsz1, suf1, rsz2, res1, rsz3, w2);
        sz = r - l + 2;
        tmp[0] = { 0, 0 };
        for (int i = 1; i <= r - l + 1; i++) tmp[i] = { i, (LL)-1e16 };
        for (int i = 0; i < sz3; i++) upd(res[i]);
        for (int i = 0; i < rsz3; i++) upd(res1[i]);
        add(suf, sz2, pre1, rsz1);
        reduce();
        sz3 = sz;
        for (int i = 0; i < sz3; i++) res[i] = tmp[i];
        merge(pre, sz1, pre1, rsz1, { mid - l + 1, lsum });
        for (int i = 0; i < sz; i++) pre[i] = tmp[i];
        sz1 = sz;
        merge(suf1, rsz2, suf, sz2, { r - mid, rsum });
        for (int i = 0; i < sz; i++) suf[i] = tmp[i];
        sz2 = sz;
        sum = lsum + rsum;
    }
    int A = 0, B = 0, C = 0;
    for (auto t : o) {
        if (q[t].l <= l && q[t].r >= r) {
            LL p = get(A, pre, sz1, q[t].x);
            q[t].ans = max(q[t].ans, q[t].sufL + p);
            q[t].ans = max(q[t].ans, get(C, res, sz3, q[t].x));
            q[t].sufL = max(q[t].sufL + (r - l + 1) * q[t].x + sum, get(B, suf, sz2, q[t].x));
        }
    }
    return sum;
}

int ans[N * 2]; bool flag[N * 2];

int main() {
    int n; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    LL delta = 0;
    for (int i = 1; i <= m; i++) {
        int op, a, b; scanf("%d%d", &op, &a);
        if (op == 1) delta += a;
        else {
            scanf("%d", &b), flag[i] = 1;
            q[i].l = a, q[i].r = b, q[i].id = i, q[i].x = delta;
        }
    }
    sort(q + 1, q + m + 1, [&](query a, query b) { return a.x < b.x; });
    vector<int> all;
    for (int i = 1; i <= m; i++) if (q[i].id) 
        all.push_back(i), ans[q[i].id] = i;
    int a = 0, b = 0, c = 0;
    build(1, 1, n, poolA, a, poolB, b, poolC, c, all);
    for (int i = 1; i <= m; i++) if (flag[i]) printf("%lld\n", q[ans[i]].ans);
}
