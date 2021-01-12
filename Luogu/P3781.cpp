#include <bits/stdc++.h>
using namespace std;

const int N = 30010;
const int M = 128;
const int mod = 1e4 + 7;
const int inv2 = (mod + 1) / 2;

typedef array<int, M> WEN;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = x * x % mod) if (y & 1) res = res * x % mod; 
    return res;
}

int m;

struct FUCK {

WEN a, zero;

WEN operator = (WEN b) {
    for (int i = 0; i < m; i++)
        a[i] = b[i] ? b[i] : 1, zero[i] = !b[i]; 
    return b;
}

WEN get() {
    WEN res;
    for (int i = 0; i < m; i++)
        res[i] = zero[i] ? 0 : a[i];
    return res;
}

void operator *= (WEN b) {
    for (int i = 0; i < m; i++) {
        if (b[i]) a[i] = a[i] * b[i] % mod;
        else zero[i]++;
    }
}

void operator /= (WEN b) {
    for (int i = 0; i < m; i++) {
        if (b[i]) a[i] = a[i] * Pow(b[i], mod - 2) % mod;
        else zero[i]--;
    }
}

} F[N];

inline WEN mul(WEN a, WEN b) {
    for (int i = 0; i < m; i++) a[i] = a[i] * b[i] % mod;
    return a;
}

inline WEN add(WEN a, WEN b) {
    for (int i = 0; i < m; i++) 
        a[i] += b[i], a[i] -= a[i] >= mod ? mod : 0;
    return a;
}

inline WEN sub(WEN a, WEN b) {
    for (int i = 0; i < m; i++)
        a[i] = a[i] - b[i], a[i] += a[i] < 0 ? mod : 0;
    return a;
}

struct Matrix {

WEN G[2][2];

WEN* operator [] (int x) { return G[x]; }

Matrix operator * (Matrix b) {
    Matrix res;
    res[0][0] = mul(G[0][0], b[0][0]);
    res[0][1] = add(G[0][1], mul(G[0][0], b[0][1]));
    res[1][0] = add(b[1][0], mul(G[1][0], b[0][0]));
    res[1][1] = add(mul(G[1][0], b[0][1]), add(G[1][1], b[1][1]));
    return res;
}

};

struct node {
    int l, r; Matrix s;
} T[N << 2]; 

WEN G[N], one; int rk[N];

inline Matrix gen(int u) {
    Matrix res;
    res[0][0] = res[0][1] = res[1][0] = F[u].get();
    res[1][1] = add(F[u].get(), G[u]);
    return res;
}

inline void pushup(int rt) {
    T[rt].s = T[rt << 1 | 1].s * T[rt << 1].s;
}

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return T[rt].s = gen(rk[l]), void();
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r), pushup(rt);
}

void update(int rt, int pos) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l == r) return T[rt].s = gen(rk[l]), void();
    if (pos <= mid) update(rt << 1, pos);
    else update(rt << 1 | 1, pos);
    pushup(rt);
}

Matrix query(int rt, int start, int end) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) return T[rt].s;
    if (end <= mid) return query(rt << 1, start, end);
    if (start > mid) return query(rt << 1 | 1, start, end);
    return query(rt << 1 | 1, start, end) * query(rt << 1, start, end);
}

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int sz[N], son[N], dfn[N], top[N], fa[N], dfsn, val[N], dwn[N];

inline WEN wkr(int x) {
    WEN res; 
    for (int i = 0; i < m; i++) {
        int w = __builtin_popcount(i & x);
        if (w & 1) res[i] = mod - 1;
        else res[i] = 1;
    }
    return res;
}

inline WEN IFWT(WEN a) {
    for (int mid = 2; mid <= m; mid <<= 1)
        for (int i = 0; i < m; i += mid)
            for (int j = i; j < i + (mid >> 1); j++) {
                int A = a[j], B = a[j + (mid >> 1)];
                a[j] = (A + B) * inv2 % mod, a[j + (mid >> 1)] = (A - B + mod) * inv2 % mod;
            }
    return a;
}

void dfs1(int u, int f) {
    fa[u] = f, sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs1(e[i].to, u), sz[u] += sz[e[i].to];
            if (sz[e[i].to] > sz[son[u]]) son[u] = e[i].to;
        }
}

WEN f[N], g[N]; 

void dfs2(int u, int t) {
    top[u] = t, dwn[t] = u, dfn[u] = ++dfsn, top[u] = t, rk[dfsn] = u, f[u] = F[u] = wkr(val[u]);
    if (son[u]) dfs2(son[u], t), f[u] = mul(f[u], add(f[son[u]], one)), g[u] = add(g[u], g[son[u]]);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != fa[u] && e[i].to != son[u]) {
            dfs2(e[i].to, e[i].to);
            auto tmp = add(f[e[i].to], one);
            F[u] *= tmp, f[u] = mul(f[u], tmp);
            G[u] = add(G[u], g[e[i].to]), g[u] = add(g[u], g[e[i].to]);
        }
    g[u] = add(g[u], f[u]);
}

inline void Just_DOIT(int u, int x) {
    F[u] /= wkr(val[u]), F[u] *= wkr(x), update(1, dfn[u]), val[u] = x;
    while (top[u]) {
        int t = fa[top[u]];  
        Matrix res = query(1, dfn[top[u]], dfn[dwn[top[u]]]);
        if (t) F[t] /= add(f[top[u]], one), G[t] = sub(G[t], g[top[u]]);
        f[top[u]] = res[1][0], g[top[u]] = res[1][1];
        if (t) F[t] *= add(f[top[u]], one), G[t] = add(G[t], g[top[u]]), update(1, dfn[t]);
        u = t;
    }
}

int main() {
    int n; scanf("%d%d", &n, &m), one = wkr(0);
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
    for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), adde(a, b);
    dfs1(1, 0), dfs2(1, 1), build(1, 1, n);
    int q; scanf("%d", &q);
    while (q--) {
        char s[10]; int a, b; scanf("%s%d", s + 1, &a);
        if (s[1] == 'Q') {
            WEN res = IFWT(g[1]);
            printf("%d\n", res[a]);
        } else scanf("%d", &b), Just_DOIT(a, b);
    }
}
