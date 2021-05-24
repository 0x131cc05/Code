#include <bits/stdc++.h>
using namespace std;

const int N = 600010;

typedef long long LL;

struct node {
    int l, r, mx; LL res;
} T[N * 2];

LL query(int rt, int x) {
    if (T[rt].mx <= x) return 0;
    int l = T[rt].l, r = T[rt].r;
    if (l == r) return T[rt].mx;
    if (T[rt << 1].mx <= x) return query(rt << 1 | 1, x);
    return T[rt].res - T[rt << 1].res + query(rt << 1, x);
}

void _pushup(int rt) {
    T[rt].mx = max(T[rt << 1].mx, T[rt << 1 | 1].mx);
    T[rt].res = T[rt << 1].res + query(rt << 1 | 1, T[rt << 1].mx);
}

int num[N];

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return T[rt].mx = T[rt].res = num[l], void(); 
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
    _pushup(rt);
}

void update(int rt, int x, int v) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l == r) return T[rt].mx = T[rt].res = v, void();
    if (x <= mid) update(rt << 1, x, v);
    else update(rt << 1 | 1, x, v);
    _pushup(rt);
}

int lst;

LL query(int rt, int start, int end) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) {
        LL res = query(rt, lst);
        lst = max(lst, T[rt].mx);
        return res;
    }
    LL res = 0;
    if (start <= mid) res += query(rt << 1, start, end);
    if (end > mid) res += query(rt << 1 | 1, start, end);
    return res; 
}

LL query(int rt, int start, int end, int x) {
    if (start > end) return 0;
    return lst = x, query(rt, start, end);
}

int fa[N], ch[2][N], sz[N], b[N], ncnt;

int child(int u) { return u == ch[1][fa[u]]; }
void connect(int u, int f, int son) { fa[u] = f, ch[son][f] = u; }
void pushup(int u) { sz[u] = 1 + sz[ch[0][u]] + sz[ch[1][u]]; }

void rotate(int u) {
    int f = fa[u], ff = fa[f], tmp = child(u), tmp1 = child(f);
    connect(ch[tmp ^ 1][u], f, tmp), connect(f, u, tmp ^ 1), connect(u, ff, tmp1);
    pushup(f), pushup(u);
}

void splay(int u, int t = 0) {
    for (int f; fa[u] != t; rotate(u))
        if (fa[f = fa[u]] != t) rotate(child(u) ^ child(f) ? u : f);
}

int st[19][N], lg[N];

int Max(int x, int y) {
    return num[x] > num[y] ? x : y;
}

void build(int n) {
    for (int i = 1; i <= n; i++) st[0][i] = i;
    for (int i = 1; i < 19; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st[i][j] = Max(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    int lst = 0;
    ncnt++, connect(ncnt, lst, 0), lst = ncnt, sz[ncnt] = 1;
    for (int i = n; i >= 1; i--) 
        ncnt++, connect(ncnt, lst, 0), lst = ncnt, b[ncnt] = i, sz[ncnt] = 1;
    ncnt++, connect(ncnt, lst, 0), lst = ncnt, sz[ncnt] = 1;
    splay(lst);
}

int find(int u, int x) {
    int l = sz[ch[0][u]];
    if (x <= l) return find(ch[0][u], x);
    if (l + 1 == x) return u;
    return find(ch[1][u], x - l - 1);
}

int get(int l, int r) {
    int len = lg[r - l + 1];
    return Max(st[len][l], st[len][r - (1 << len) + 1]);
}

void merge(int b1, int b2, int b3) {
    if (b1 == b2 || b2 == b3) return;
    int A = get(b1 + 1, b2), B = get(b2 + 1, b3);
    if (num[A] > num[B]) swap(A, B);
    update(1, A, 0);
}

void modify(int l, int r) {
    int b1, b2, b3;
    int t = find(ch[0][0], l); b1 = b[t], splay(t);
    t = find(ch[0][0], l + 2), b3 = b[t], splay(t, ch[0][0]);
    int &d = ch[0][t];
    b2 = b[d], fa[d] = 0, d = 0, merge(b1, b2, b3);
    pushup(t), pushup(ch[0][0]);
    t = find(ch[0][0], r), splay(t); 
    int tmp = b[t];
    t = find(ch[0][0], r + 1), splay(t, ch[0][0]);
    ncnt++, connect(ncnt, t, 0), sz[ncnt] = 1, b[ncnt] = tmp;
    pushup(t), pushup(ch[0][0]);
}

int main() {
    freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    build(n), build(1, 1, n);
    while (m--) {
        int op, l, r; scanf("%d%d%d", &op, &l, &r);
        if (op == 1) { if (l != r) modify(l, r); continue; }
        int t = find(ch[0][0], l + 1), t1 = find(ch[0][0], r + 1);
        int mx = num[get(l, b[t])];
        printf("%lld\n", mx + query(1, b[t] + 1, b[t1], mx));
    }
}