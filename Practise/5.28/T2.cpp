#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

struct Tree {
    struct node {
        int l, r; LL sum, tag;
    } T[N << 2];

    void pushdown(int rt) {
        if (T[rt].tag) return;
        int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
        LL t = T[rt].tag;
        T[rt << 1].sum += t * (mid - l + 1), T[rt << 1 | 1].sum += t * (r - mid);
        T[rt << 1].tag += t, T[rt << 1 | 1].tag += t;
        T[rt].tag = 0;
    }

    void pushup(int rt) {
        T[rt].sum = T[rt << 1].sum + T[rt << 1 | 1].sum;
    }

    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r; int mid = (l + r) >> 1;
        if (l == r) return;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
    }

    void update(int rt, int start, int end, int x) {
        if (start > end) return;
        int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
        if (start <= l && r <= end) return T[rt].sum += (r - l + 1) * x, T[rt].tag += x, void();
        pushdown(rt);
        if (start <= mid) update(rt << 1, start, end, x);
        if (end > mid) update(rt << 1 | 1, start, end, x);
        pushup(rt);
    }

    LL query(int rt, int start, int end) {
        if (start > end) return 0;
        int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
        if (start <= l && r <= end) return T[rt].sum;
        pushdown(rt);
        LL res = 0;
        if (start <= mid) res += query(rt << 1, start, end);
        if (end > mid) res += query(rt << 1 | 1, start, end);
        return res;
    }
} T1, T2;

LL pre[N];

vector<int> in[N], out[N];

int a[N], b[N], tp[N]; LL sum;

void modifyA(int l, int r, int x) {
    sum += x * T2.query(1, l, r), T1.update(1, l, r, x);
}

void modifyB(int l, int r, int x) {
    sum += x * T1.query(1, l, r), T2.update(1, l, r, x);
}

int n;

void modify(int t, int dir, int x) {
    if (b[t] >= a[t]) {
        if (dir == 0) modifyA(a[t] + 1, b[t], x);
        else modifyB(b[t] + 1, n, x), modifyB(1, a[t], x);
    } else {
        if (dir == 0) modifyA(a[t] + 1, n, x), modifyA(1, b[t], x);
        else modifyB(b[t] + 1, a[t], x);
    }
}

LL calc(int a, int b, int dir) {
    LL t = pre[max(a, b)] - pre[min(a, b)];
    if ((b >= a) ^ dir) return t;
    return pre[n] - t;
}

LL tmp[N];

int main() {
    int m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &pre[i]), pre[i] += pre[i - 1];
    T1.build(1, 1, n), T2.build(1, 1, n);
    LL ans = 0;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &a[i], &b[i]);
        out[a[i]].push_back(i), in[b[i]].push_back(i);
        if (b[i] >= a[i]) {
            tp[i] = 0, modifyA(a[i] + 1, b[i], 1);
            tmp[i] = pre[b[i]] - pre[a[i]];
        } else {
            tp[i] = 1, modifyB(b[i] + 1, n, 1), modifyB(1, a[i], 1);
            tmp[i] = pre[n] - (pre[a[i]] - pre[b[i]]);
        }
        ans += tmp[i];
    }
    for (int i = 0; i < n; i++) {
        for (auto t : in[i]) {
            ans -= tmp[t], modify(t, tp[t], -1);
            if (tp[t]) tmp[t] = pre[n] - tmp[t], tp[t] = 0;
        } 
        for (auto t : out[i]) {
            ans -= tmp[t], modify(t, tp[t], -1);
            if (!tp[t]) tmp[t] = pre[n] - tmp[t], tp[t] = 1; 
        }
        if (!out[i].size() && !sum) {
            sort(in[i].begin(), in[i].end(), [&](int p, int q) { 
                int d1 = a[p] >= i ? a[p] - i : n - (i - a[p]), d2 = a[q] >= i ? a[q] - i : n - (i - a[q]);
                return d1 < d2;
            });
            for (int j = -1; j < in[i].size(); j++) {
                for (int k = 0; k < in[i].size(); k++)
                    if (k <= j)
            }
        }
        for (auto t : in[i]) ans += tmp[t], modify(t, tp[t], 1);
        for (auto t : out[i]) ans += tmp[t], modify(t, tp[t], 1);
    }
}