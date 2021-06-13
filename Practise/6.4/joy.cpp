#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

int num[N];

struct RMQ {
    struct node {
        int l, r, mn;
    } T[N << 2];

    void pushup(int rt) {
        T[rt].mn = min(T[rt << 1].mn, T[rt << 1 | 1].mn);
    }

    void build(int rt, int l, int r) {
        T[rt].l = l, T[rt].r = r;
        if (l == r) return T[rt].mn = num[l - 1] - num[l], void();
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r), pushup(rt);
    }

    void update(int rt, int pos, int x) {
        int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
        if (l == r) return T[rt].mn = x, void();
        if (pos <= mid) update(rt << 1, pos, x);
        else update(rt << 1 | 1, pos, x);
        pushup(rt);
    }

    int query(int rt, int start, int end) {
        int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
        if (start <= l && r <= end) return T[rt].mn;
        int res = 1e9;
        if (start <= mid) res = min(res, query(rt << 1, start, end));
        if (end > mid) res = min(res, query(rt << 1 | 1, start, end));
        return res;
    }
} rmq;

int ls[N * 32], rs[N * 32], sz[N * 32], tot; LL sum[N];

void update(int &rt, int l, int r, int pos, int x) {
    if (!rt) rt = ++tot;
    sz[rt] += x, sum[rt] += x * pos;
    if (l == r) return;
    int mid = ((LL)l + r) / 2;
    if (pos <= mid) update(ls[rt], l, mid, pos, x);
    else update(rs[rt], mid + 1, r, pos, x);
}

int find(int rt, int l, int r, LL x) {
    if (x <= 0) return 0;
    if (!rt || sum[rt] < x) return -1;
    if (l == r) return 1;
    int mid = ((LL)l + r) / 2;
    if (sum[rs[rt]] >= x) return find(rs[rt], mid + 1, r, x);
    return sz[rs[rt]] + find(ls[rt], l, mid, x - sum[rs[rt]]);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
        LL res = 0;
        for (int i = 2; i <= n; i++) 
            res += max(0, num[i] - num[i - 1]);
        for (int i = 1; i <= tot; i++) sz[i] = ls[i] = rs[i] = sum[i] = 0;
        for (int i = 1; i <= n; i++) {
            
        }
        tot = 0;
        rmq.build(1, 1, n);
        while (m--) {
            
        }
    }
}