#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;
const int mod = 998244353;

typedef long long LL;

struct data {
    int mn, sum1, sum2;
};

inline int Add(int x, int y) {
    int t = x + y;
    return t >= mod ? t - mod : t;
}

inline void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

inline data Merge(data a, data b) {
    int mn = min(a.mn, b.mn); 
    if (a.mn != b.mn) return a.mn < b.mn ? a : b;
    return (data){ a.mn, Add(a.sum1, b.sum1), Add(a.sum2, b.sum2) };
}

struct node {
    int l, r, tag, tag1; data t;
} T[N << 2];

inline void pushup(int rt) {
    T[rt].t = Merge(T[rt << 1].t, T[rt << 1 | 1].t);
}

inline void wkr(int rt, int x) {
    T[rt].tag += x, T[rt].t.mn += x;
}

inline void zjk(int rt, int x) {
    T[rt].tag1 = (LL)T[rt].tag1 * x % mod;
    T[rt].t.sum1 = (LL)T[rt].t.sum1 * x % mod;
    T[rt].t.sum2 = (LL)T[rt].t.sum2 * x % mod;
}

inline void pushdown(int rt) {
    if (T[rt].tag) {
        wkr(rt << 1, T[rt].tag), wkr(rt << 1 | 1, T[rt].tag);
        T[rt].tag = 0;
    } 
    if (T[rt].tag1 != 1) {
        zjk(rt << 1, T[rt].tag1), zjk(rt << 1 | 1, T[rt].tag1);
        T[rt].tag1 = 1;
    }
}

int len[N], bk[N], n, ct[N];

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r, T[rt].tag1 = 1;
    if (l == r) return T[rt].t.mn = (!!ct[bk[l]]) || bk[l] > n, T[rt].t.sum1 = len[bk[l]], T[rt].t.sum2 = 1, void();
    int mid = (l + r) >> 1; build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}

void mul(int rt, int start, int end, int x) {
    if (start > end) return;
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) return zjk(rt, x), void();
    pushdown(rt);
    if (start <= mid) mul(rt << 1, start, end, x);
    if (end > mid) mul(rt << 1 | 1, start, end, x);
    pushup(rt);
}

void add(int rt, int start, int end, int x) {
    if (start > end) return;
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) return wkr(rt, x), void();
    pushdown(rt);
    if (start <= mid) add(rt << 1, start, end, x);
    if (end > mid) add(rt << 1 | 1, start, end, x);
    pushup(rt);
}

data query(int rt, int start, int end) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) return T[rt].t;
    pushdown(rt);
    if (end <= mid) return query(rt << 1, start, end);
    if (start > mid) return query(rt << 1 | 1, start, end);
    return Merge(query(rt << 1, start, end), query(rt << 1 | 1, start, end));
}

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

int dfn[N], dfsn, ed[N], inv[N], fa[N];

void dfs(int u, int f) {
    dfn[u] = ++dfsn, bk[dfsn] = u, fa[u] = f;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            len[e[i].to] = Add(len[u], e[i].w), dfs(e[i].to, u);
            if (e[i].to <= n) ct[u]++;
        }  
    ed[u] = dfsn; 
}

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

struct ZJKAK {
    int op, a, b;
} q[N];

inline void update(int u, int ls, int nw) {
    // cout << T[1].t.sum2 << endl;
    // cout << "update: " << u << ' ' << ls << ' ' << nw << endl;
    mul(1, dfn[u] + 1, ed[u], (LL)max(ls, 1) * max(inv[nw], 1) % mod);
    // cout << T[1].t.sum2 << endl;
}

template<class T> inline void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
    int m; scanf("%d%d", &n, &m); int ncnt = n;
    for (int i = 1; i <= n + m; i++) inv[i] = Pow(i, mod - 2);
    for (int i = 2; i <= n; i++) {
        int a, b; read(a), read(b);
        adde(a, i, b);
    }
    for (int i = 1; i <= m; i++) {
        read(q[i].op), read(q[i].a);
        if (q[i].op == 1) {
            int x; read(x);
            adde(++ncnt, q[i].a, x), q[i].b = ncnt;
        }
    }
    dfs(1, 0), build(1, 1, ncnt);
    for (int i = 1; i <= n; i++) 
        if (ct[i]) mul(1, dfn[i] + 1, ed[i], inv[ct[i]]);
    for (int i = 1; i <= m; i++) {
        if (q[i].op == 1) {
            if (++ct[q[i].a] == 1) add(1, dfn[q[i].a], dfn[q[i].a], 1);
            add(1, dfn[q[i].b], dfn[q[i].b], -1);
            update(q[i].a, ct[q[i].a] - 1, ct[q[i].a]);
        } else if (q[i].op == 2) {
            int u = q[i].a;
            add(1, dfn[u], ed[u], 1), ct[fa[u]]--, update(fa[u], ct[fa[u]] + 1, ct[fa[u]]);
            if (!ct[fa[u]]) add(1, dfn[fa[u]], dfn[fa[u]], -1);
        } else if (q[i].op == 3) {
            int u = q[q[i].a].a;
            // cout << "fuck: " << u << endl;
            add(1, dfn[u], ed[u], -1), ct[fa[u]]++, update(fa[u], ct[fa[u]] - 1, ct[fa[u]]);
            if (ct[fa[u]] == 1) add(1, dfn[fa[u]], dfn[fa[u]], 1);
        } else {
            int u = q[i].a; 
            data A = T[1].t, B = query(1, dfn[u], ed[u]), C = query(1, dfn[u], dfn[u]);
            int t1 = A.sum1, t2 = A.sum2;
            // cout << t1 << ' ' << t2 << ' ' << B.mn << ' ' << B.sum1 << ' ' << B.sum2 << endl;
            if (B.mn == 0) Inc(t1, mod - B.sum1), Inc(t2, mod - B.sum2);
            int other = (LL)t1 * Pow(t2, mod - 2) % mod, tim = Pow(C.sum2, mod - 2);
            printf("%d\n", Add((LL)other * (tim - 1) % mod, len[u]));
        }
    }
    return 0;
}