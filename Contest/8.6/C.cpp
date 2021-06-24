#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
typedef long long LL;
typedef unsigned long long uLL;

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

struct node {
    int l, r; uLL sum, lcm;
} T[N << 2];
void pushup(int rt) {
    LL A = T[rt << 1].lcm, B = T[rt << 1 | 1].lcm;
    if (max(A, B) > 1e17) T[rt].lcm = 1e18;
    else {
        LL tmp = A / gcd(A, B);
        if (tmp > 1e18 / B) T[rt].lcm = 1e18;
        else T[rt].lcm = tmp * B;
    }
    T[rt].sum = T[rt << 1].sum + T[rt << 1 | 1].sum;
}
LL num[N];
void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return T[rt].lcm = T[rt].sum = num[l], void();
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r), pushup(rt);
}
void update(int rt, int start, int end, LL x) {
    if (x % T[rt].lcm == 0) return;
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l == r) return T[rt].lcm = T[rt].sum = gcd(T[rt].sum, x), void();
    if (start <= mid) update(rt << 1, start, end, x);
    if (end > mid) update(rt << 1 | 1, start, end, x);
    pushup(rt);
}
uLL query(int rt, int start, int end) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (T[rt].lcm == 1) return min(r, end) - max(l, start) + 1;
    if (start <= l && r <= end) return T[rt].sum;
    uLL res = 0;
    if (start <= mid) res += query(rt << 1, start, end);
    if (end > mid) res += query(rt << 1 | 1, start, end);
    return res;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &num[i]);
    build(1, 1, n);
    while (m--) {
        int op, l, r; LL x; scanf("%d%d%d", &op, &l, &r);
        if (op == 1) scanf("%lld", &x), update(1, l, r, x);
        else printf("%llu\n", query(1, l, r));
    }
}
