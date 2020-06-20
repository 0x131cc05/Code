#include <bits/stdc++.h>
using namespace std;

const int N = 300010;

typedef long long LL;

struct node {
    int l, r, val;
} T[N << 2];

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
}

inline void pushdown(int rt) {
    if (T[rt].val) T[rt << 1].val = T[rt << 1 | 1].val = T[rt].val;
    T[rt].val = 0;
}

void update(int rt, int start, int end, int x) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) return T[rt].val = x, void();
    pushdown(rt);
    if (start <= mid) update(rt << 1, start, end, x);
    if (end > mid) update(rt << 1 | 1, start, end, x);
}

int query(int rt, int pos) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l == r) return T[rt].val;
    if (T[rt].val) return T[rt].val;
    if (pos <= mid) return query(rt << 1, pos);
    return query(rt << 1 | 1, pos);
}

LL h[N];

int main() {
    int n, m, q; scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++) scanf("%lld", &h[i]);
    LL res = 0; int tp = 0;
    build(1, 1, n);
    for (int i = 1; i <= q; i++) {
        int k; scanf("%d", &k);
        while (tp < k) {
            LL t = h[tp % m + 1]; tp++;
            int l = 1, r = n, mid, pos = n + 1;
            while (l <= r) {
                mid = (l + r) >> 1; int ls = query(1, mid);
                LL nw = h[(ls - 1) % m + 1] + (LL)(tp - ls) * mid;
                if (nw > t) pos = mid, r = mid - 1;
                else l = mid + 1;
            }
            res += n - pos + 1;
            if (pos <= n) update(1, pos, n, tp);
        }
        printf("%lld\n", res);
    }
}
