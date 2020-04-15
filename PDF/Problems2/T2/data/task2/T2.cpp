#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

typedef pair<int, int> P;

inline P merge(const P &a, const P &b) {
    P res = P(min(a.first, b.first), 0);
    if (res.first == a.first) res.second += a.second;
    if (res.first == b.first) res.second += b.second;
    return res;
}

struct node {
    int l, r, tag; P t;
} T[N << 2];

inline void pushup(int rt) {
    T[rt].t = merge(T[rt << 1].t, T[rt << 1 | 1].t);
}

inline void dec(int rt, int x) {
    T[rt].t.first -= x, T[rt].tag += x;
} 

inline void pushdown(int rt) {
    if (!T[rt].tag) return;
    dec(rt << 1, T[rt].tag), dec(rt << 1 | 1, T[rt].tag), T[rt].tag = 0;
}

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return T[rt].t = P(l, 1), void();
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r), pushup(rt);
}

void update(int rt, int start, int end, int x) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) 
        return dec(rt, x), void();
    pushdown(rt);
    if (start <= mid) update(rt << 1, start, end, x);
    if (end > mid) update(rt << 1 | 1, start, end, x);
    pushup(rt);
}

inline int get() {
    return T[1].t.first == 1 ? T[1].t.second : 0;
}

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){to, head[from]}, head[from] = ecnt;
    e[++ecnt] = (edge){from, head[to]}, head[to] = ecnt;
}

int fa[N], num[N]; set<int> s[N];

void dfs(int u, int f) {
    fa[u] = f;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) 
            s[u].insert(num[e[i].to]), dfs(e[i].to, u);
}

int lst[N], n; set<P> zjk; int orz[N];

inline void Just_DOIT(int u, int A) {
    int tmp = max(A, num[u]);
    if (!lst[u]) lst[u] = tmp, update(1, lst[u], n, 1);
    else if (lst[u] != tmp) 
        update(1, lst[u], n, -1), update(1, lst[u] = tmp, n, 1);
}

inline void Make_Your_Dream_COMETRUE(int u, int B) {
    if (B == -1) return;
    int tmp = max(B, num[u]);
    if (!orz[u]) orz[u] = tmp, zjk.insert(P(tmp, u));
    else if (orz[u] != tmp) 
        zjk.erase(P(orz[u], u)), zjk.insert(P(orz[u] = tmp, u));
}

inline void check(int u) {
    if (u == 0 || !s[u].size()) return;
    int A = *s[u].begin(), B = s[u].size() > 1 ? *s[u].upper_bound(A) : -1;
    Just_DOIT(u, A), Make_Your_Dream_COMETRUE(u, B);
}

inline int solve() {
    if (!zjk.size()) return get();
    int l = zjk.begin() -> first, p = zjk.begin() -> second, r = fa[p] ? num[fa[p]] - 1 : n;
    update(1, l, r, 1); int tmp = get(); update(1, l, r, -1);
    return tmp;
}

#define open(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)

int main() {
    open("data10");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), adde(a, b);
    dfs(1, 0), build(1, 1, n);
    for (int i = 1; i <= n; i++) check(i);
    int q; scanf("%d", &q);
    while (q--) {
        int u, v; scanf("%d%d", &u, &v);
        if (fa[u]) s[fa[u]].erase(num[u]); if (fa[v]) s[fa[v]].erase(num[v]);
        swap(num[u], num[v]);
        if (fa[u]) s[fa[u]].insert(num[u]); if (fa[v]) s[fa[v]].insert(num[v]);
        check(u), check(v), check(fa[u]), check(fa[v]);
        printf("%d\n", solve());
    }
    return 0;
}
