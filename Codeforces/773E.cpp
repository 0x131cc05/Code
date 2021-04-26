#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

struct node {
    int l, r, tag, x, y;
} T[N << 2];

void pushup(int rt) {
    T[rt].x = min(T[rt << 1].x, T[rt << 1 | 1].x);
    T[rt].y = max(T[rt << 1].y, T[rt << 1 | 1].y);
}

void pushdown(int rt) {
    if (!T[rt].tag) return;
    T[rt << 1].x -= T[rt].tag, T[rt << 1 | 1].x -= T[rt].tag;
    T[rt << 1].y += T[rt].tag, T[rt << 1 | 1].y += T[rt].tag;
    T[rt << 1].tag += T[rt].tag, T[rt << 1 | 1].tag += T[rt].tag;
    T[rt].tag = 0;
}

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return T[rt].x = T[rt].y = l, void();
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r), pushup(rt);
}

void update(int rt, int start, int end) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) return T[rt].tag++, T[rt].x--, T[rt].y++, void();
    pushdown(rt);
    if (start <= mid) update(rt << 1, start, end);
    if (end > mid) update(rt << 1 | 1, start, end);
    pushup(rt);
}

int find(int rt) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (T[rt].y < 0) return -1e9;
    if (l == r) return l;
    pushdown(rt);
    if (T[rt << 1].y >= 0) return find(rt << 1);
    return find(rt << 1 | 1);
}

int query(int rt, int start) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l) return T[rt].x;
    pushdown(rt);
    if (start > mid) return query(rt << 1 | 1, start);
    return min(T[rt << 1 | 1].x, query(rt << 1, start));
}

int tree[N], mn, mx;

void upd(int x) {
    for (x -= mn - 1; x <= mx - mn + 1; x += x & -x) tree[x]++;
}

int que(int x) {
    int res = 0;
    for (x -= mn - 1; x; x -= x & -x) res += tree[x];
    return res;
}

int main() {
    int n; scanf("%d", &n), mn = 0, mx = 0;
    vector<int> v;
    for (int i = 1, a; i <= n; i++) 
        scanf("%d", &a), v.push_back(a), mn = min(mn, a), mx = max(mx, a);
    build(1, mn, mx);
    for (int i = 1; i <= n; i++) {
        int a = v[i - 1]; update(1, a, 1e9), upd(a);
        int pos = find(1);
        if (pos == -1e9) printf("%d\n", -i);
        else {
            int t = que(pos), tmp = max(pos, -t) + i - t, res = query(1, pos) + i;
            printf("%d\n", min(tmp, res));
        }
    } 
}