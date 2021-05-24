#include <bits/stdc++.h>
using namespace std;

const int N = 600010;

typedef long long LL;

struct node {
    int l, r; LL mn, sum;
} T[N << 2];

LL num[N]; int c;

void pushup(int rt) {
    T[rt].mn = min(T[rt << 1].mn, T[rt << 1].sum + T[rt << 1 | 1].mn);
    T[rt].sum = T[rt << 1].sum + T[rt << 1 | 1].sum;
}

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) {
        LL A = num[l] % c, B = num[l] / c;
        T[rt].mn = -A, T[rt].sum = B - A;
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}

void update(int rt, int pos, LL x) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l == r) return T[rt].mn = -(x % c), T[rt].sum = x / c - x % c, void();
    if (pos <= mid) update(rt << 1, pos, x);
    else update(rt << 1 | 1, pos, x);
    pushup(rt);
}

LL get(int rt, int x) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l == r) return T[rt].sum;
    if (x <= mid) return get(rt << 1, x);
    return T[rt << 1].sum + get(rt << 1 | 1, x);
}

LL query(int rt, int end) { // prefix min
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (r <= end) return T[rt].mn;
    if (end < mid) return query(rt << 1, end);
    return min(T[rt << 1].mn, T[rt << 1].sum + query(rt << 1 | 1, end));
}

template<class T> void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

template<class T, typename... Tail> void read(T &x, Tail&... tail) {
    read(x), read(tail...);
}

int n; LL tree[N], tree1[N];

void upd(int x, LL y) {
    for (; x; x -= x & -x) tree[x] += y;
}

LL que(int x) {
    LL res = 0;
    for (; x <= n; x += x & -x) res += tree[x];
    return res;
}

void upd1(int x, LL y) {
    for (; x <= n; x += x & -x) tree1[x] += y;
}

LL que1(int x) {
    LL res = 0;
    for (; x; x -= x & -x) res += tree1[x];
    return res;
}

void work() {
    int l = 1, r = n, mid; LL res = 0, remain = 0, fk = 0, lst;
    while (l <= r) {
        mid = (l + r) >> 1;
        LL mn = query(1, mid), nw = get(1, mid);
        LL use = que(mid + 1);
        if (nw - mn >= use) res = -mn + que1(mid), lst = nw - mn - num[mid] / c, r = mid - 1, remain = nw - mn - use;
        else l = mid + 1;
    }
    LL t = remain / (c + 1) * c;
    res -= t, remain %= c + 1;
    if (remain >= 1) remain--, res -= min(lst, remain);
    printf("%lld\n", res);
}

int main() {
    // freopen("b1_1.in", "r", stdin), freopen("b.out", "w", stdout);
    int m; read(n, m, c);
    for (int i = 1; i <= n; i++) read(num[i]), upd(i, num[i]), upd1(i, num[i] / c * c);
    build(1, 1, n), work();
    while (m--) {
        int x; LL y; read(x, y), 
        update(1, x, y);
        upd(x, y - num[x]), upd1(x, y / c * c - num[x] / c * c), num[x] = y;
        work();
    }
}