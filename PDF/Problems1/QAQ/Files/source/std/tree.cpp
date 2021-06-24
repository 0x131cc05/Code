#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

int n;

struct Tree { int lson, rson; LL sum, tag; } _T[N * 18 * 18];

class TemplateTree {

private:
    struct Edge { int to, next, w; } e[N * 2];

    int head[N], ecnt, val[N], fa[N], son[N], top[N], dep[N], rk[N], tot;

    void DFS1(int u, int f) {
        fa[u] = f, sz[u] = 1, dep[u] = dep[f] + 1;
        for (int i = head[u]; i; i = e[i].next)
            if (e[i].to != f) {
                DFS1(e[i].to, u), val[e[i].to] = e[i].w, sz[u] += sz[e[i].to];
                if (sz[e[i].to] > sz[son[u]]) son[u] = e[i].to;
            } 
    }

    void DFS2(int u, int t) {
        top[u] = t, id[u] = ++tot, rk[tot] = u;
        if (son[u]) DFS2(son[u], t);
        for (int i = head[u]; i; i = e[i].next)
            if (e[i].to != fa[u] && e[i].to != son[u]) 
                DFS2(e[i].to, e[i].to);
    }

    int ncnt, RT[N];

    int build(int l, int r) {
        int rt = ++ncnt; 
        if (l == r) return _T[rt].sum = val[rk[l]], rt;
        int mid = (l + r) >> 1; 
        _T[rt].lson = build(l, mid), _T[rt].rson = build(mid + 1, r);
        return _T[rt].sum = _T[_T[rt].lson].sum + _T[_T[rt].rson].sum, rt;
    }

    int update(int rt, int l, int r, int start, int end, int x) {
        if (start > end) return rt;
        int mid = (l + r) >> 1;
        int nw = ++ncnt; _T[nw] = _T[rt], _T[nw].sum += (LL)x * (min(end, r) - max(start, l) + 1);
        if (start <= l && r <= end) return _T[nw].tag += x, nw;
        if (start <= mid) _T[nw].lson = update(_T[nw].lson, l, mid, start, end, x);
        if (end > mid) _T[nw].rson = update(_T[nw].rson, mid + 1, r, start, end, x);
        return nw;
    } 

    LL query(int rt, int l, int r, int start, int end) {
        if (start > end) return 0;
        int mid = (l + r) >> 1;
        if (start <= l && r <= end) return _T[rt].sum;
        LL res = (LL)_T[rt].tag * (min(r, end) - max(l, start) + 1);
        if (start <= mid) res += query(_T[rt].lson, l, mid, start, end);
        if (end > mid) res += query(_T[rt].rson, mid + 1, r, start, end);
        return res;
    }

public:
    int version, id[N], sz[N];

    inline void Adde(int from, int to, int w) {
        e[++ecnt] = (Edge){ to, head[from], w }, head[from] = ecnt;
        e[++ecnt] = (Edge){ from, head[to], w }, head[to] = ecnt;
    }

    inline void Build() { DFS1(1, 0), DFS2(1, 1), RT[0] = build(1, n); }

    inline int LCA(int a, int b) {
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            a = fa[top[a]];
        }
        return dep[a] < dep[b] ? a : b;
    }

    inline LL Dis(int version, int a, int b) {
        LL res = 0; 
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            res += query(RT[version], 1, n, id[top[a]], id[a]), a = fa[top[a]];
        }
        if (dep[a] > dep[b]) swap(a, b);
        res += query(RT[version], 1, n, id[a] + 1, id[b]);
        return res;
    }

    inline LL SubTree(int version, int a) {
        return query(RT[version], 1, n, id[a] + 1, id[a] + sz[a] - 1);
    }

    inline void Update(int a, int b, int x) {
        version++, RT[version] = RT[version - 1];
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            RT[version] = update(RT[version], 1, n, id[top[a]], id[a], x), a = fa[top[a]];
        }
        if (dep[a] > dep[b]) swap(a, b);
        RT[version] = update(RT[version], 1, n, id[a] + 1, id[b], x);
    }

} T;

int fa[N][19], version[N], dep[N], tot; LL dis[N], pos[N];

inline void Link(LL a, int w) {
    int from = (a + n - 1) / n; tot++, pos[tot] = a, dep[tot] = dep[from] + 1, fa[tot][0] = from;
    LL d = T.Dis(version[from], 1, a - (LL)(from - 1) * n) + w; dis[tot] = dis[from] + d;
    for (int i = 1; i <= 18; i++) fa[tot][i] = fa[fa[tot][i - 1]][i - 1];
    version[tot] = T.version;
}

inline int Ancestor(LL a, int to) {
    int from = (a + n - 1) / n;
    if (from == to) return a - (LL)(to - 1) * n;
    for (int i = 18; i >= 0; i--) if (dep[fa[from][i]] > dep[to]) from = fa[from][i];
    return pos[from] - (LL)(to - 1) * n;
}

inline int LCA(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 18; i >= 0; i--) if (dep[fa[a][i]] >= dep[b]) a = fa[a][i];
    if (a == b) return a;
    for (int i = 18; i >= 0; i--) if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
    return fa[a][0];
}

inline LL Dis(LL a, LL b) {
    int A = (a + n - 1) / n, B = (b + n - 1) / n, ta = a - (LL)(A - 1) * n, tb = b - (LL)(B - 1) * n; 
    if (A == B) return T.Dis(version[A], ta, tb);
    int lca = LCA(A, B); 
    LL res = dis[A] + T.Dis(version[A], 1, ta) + T.Dis(version[B], 1, tb) + dis[B] - 2 * dis[lca];
    ta = Ancestor(a, lca), tb = Ancestor(b, lca);
    return res - 2 * T.Dis(version[lca], 1, T.LCA(ta, tb));
}

class Splay {

private:
    int fa[N * 4], num[N * 4], ch[2][N * 4], ncnt; LL sum[N * 4], val[N * 4];

    inline int child(int u) { return u == ch[1][fa[u]]; }
    inline void connect(int u, int f, int son) { fa[u] = f, ch[son][f] = u; }
    inline void pushup(int u) {
        sum[u] = val[u];
        if (ch[0][u]) sum[u] += sum[ch[0][u]];
        if (ch[1][u]) sum[u] += sum[ch[1][u]];
    }

    inline void rotate(int u) {
        int f = fa[u], ff = fa[f], tmp = child(u), tmp1 = child(f);
        connect(ch[tmp ^ 1][u], f, tmp), connect(f, u, tmp ^ 1), connect(u, ff, tmp1);
        pushup(f), pushup(u);
    }

    inline void splay(int &rt, int u, int t = 0) {
        for (int f; fa[u] != t; rotate(u))
            if (fa[f = fa[u]] != t)
                rotate(child(u) ^ child(f) ? u : f);
        if (!t) rt = u;
    }

    inline int pre(int rt, int x) {
        int nw = rt, mx = -1, pos = -1;
        while (233) {
            if (num[nw] < x && num[nw] > mx) mx = num[nw], pos = nw;
            int nxt = x > num[nw];
            if (!ch[nxt][nw]) return pos;
            nw = ch[nxt][nw]; 
        }
    }

    inline int nxt(int rt, int x) {
        int nw = rt, mn = 1e9 + 1, pos = -1;
        while (233) {
            if (num[nw] > x && num[nw] < mn) mn = num[nw], pos = nw;
            int nxt = x >= num[nw];
            if (!ch[nxt][nw]) return pos;
            nw = ch[nxt][nw];
        }
    }

public:
    inline void Init(int &rt) {
        rt = ++ncnt, num[ncnt] = 1e9, ncnt++, connect(ncnt, rt, 0);
    }

    inline void Insert(int &rt, int x, LL v) {
        int nw = rt;
        while (233) {
            if (num[nw] == x) return val[nw] += v, splay(rt, nw);
            int nxt = x > num[nw];
            if (!ch[nxt][nw]) { 
                ncnt++, connect(ncnt, nw, nxt), num[ncnt] = x, val[ncnt] = v;
                return splay(rt, ncnt);
            }
            nw = ch[nxt][nw];
        }
    }

    inline LL Query(int &rt, int l, int r) {
        splay(rt, pre(rt, l)), splay(rt, nxt(ch[1][rt], r), rt);
        if (!ch[0][ch[1][rt]]) return 0;
        return sum[ch[0][ch[1][rt]]];
    }

} T1;

int RT[N]; 

inline void Apply(int u, LL pos, LL x) { 
    pos = pos - (LL)(u - 1) * n;
    T1.Insert(RT[u], T.id[pos], x);
}

int all = 0;

class LCT {

private:
    int fa[N], sz[N], ch[N][2], tmp[N]; LL val[N], tag[N];

    inline int isroot(int u) { return u != ch[fa[u]][0] && u != ch[fa[u]][1]; }
    inline int child(int u) { return u == ch[fa[u]][1]; }
    inline void connect(int u, int f, int son) { fa[u] = f, ch[f][son] = u; }
    inline void pushup(int u) { sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + 1 + tmp[u]; }
    inline void pushdown(int u) {
        if (ch[u][0]) tag[ch[u][0]] += tag[u], val[ch[u][0]] += tag[u];
        if (ch[u][1]) tag[ch[u][1]] += tag[u], val[ch[u][1]] += tag[u];
        tag[u] = 0;
    }

    inline void rotate(int u) {
        int f = fa[u], ff = fa[f], tmp = child(u), tmp1 = child(f);
        if (!isroot(f)) connect(u, ff, tmp1);
        fa[u] = ff, connect(ch[u][tmp ^ 1], f, tmp), connect(f, u, tmp ^ 1), pushup(f), pushup(u);
    }

    inline void splay(int u) {
        static int st[N]; int top = 0, nw = u; st[++top] = u;
        while (!isroot(nw)) st[++top] = nw = fa[nw];
        while (top) pushdown(st[top--]);
        for (int f; !isroot(u); rotate(u))
            if (!isroot(f = fa[u]))
                rotate(child(u) ^ child(f) ? u : f);
        pushup(u);
    }

    inline int top(int u) {
        while (ch[u][0]) u = ch[u][0];
        return u;
    }

    inline void access(int u) {
        int ls = u; u = fa[u];
        for (; u; u = fa[ls = u]) {
            tmp[u]++, splay(u);
            if (sz[ls] > sz[ch[u][1]]) {
                int t = 0;
                if (ch[u][1]) t = top(ch[u][1]), Apply(u, pos[t], val[u]);
                val[u] = 0, tmp[u] += sz[ch[u][1]] - sz[ls], ch[u][1] = ls, pushup(u);
            }
        }
    }

public:
    inline void Update(int u, LL x) {
        while (u) {
            splay(u); int f = fa[u], t = top(u); 
            all++;
            if (ch[u][0]) val[ch[u][0]] += x, tag[ch[u][0]] += x;
            if (f) Apply(f, pos[t], x);
            u = fa[u], splay(t);
        }
    }

    inline void Link(int u, int v) {
        fa[v] = u, sz[v] = 1, access(v);
    }

    inline void Pushdown(int u) {
        splay(u); 
        if (ch[u][1]) Apply(u, pos[top(ch[u][1])], val[u]);
        val[u] = 0;
    }

    inline void Init() { sz[1] = 1; }

} T2;

inline LL SubTree(LL a) {
    int A = (a + n - 1) / n, ta = a - (LL)(A - 1) * n; 
    LL res = T.SubTree(version[A], ta);
    T2.Pushdown(A);
    return res + T1.Query(RT[A], T.id[ta], T.id[ta] + T.sz[ta] - 1);
}

inline void Copy(LL a, int w) {
    Link(a, w), T2.Link((a + n - 1) / n, tot);
    T1.Init(RT[tot]), T2.Update(tot, w + T.SubTree(version[tot], 1));
}

inline void Init() { T.Build(), dep[1] = 1, tot = 1, version[1] = 0, T1.Init(RT[1]), T2.Init(); }

template<class T> inline void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
    freopen("tree.in", "r", stdin), freopen("tree.out", "w", stdout);
    int q, t; read(n), read(q), read(t);
    for (int i = 1, a, b, c; i < n; i++) 
        read(a), read(b), read(c), T.Adde(a, b, c);
    Init(); LL ls = 0;
    while (q--) {
        int op; LL a, b, c; read(op), read(a), a ^= ls * t;
        if (op == 1) {
            read(b), read(c), b ^= ls * t, c ^= ls * t;
            T.Update(a, b, c);
        } else if (op == 2) {
            read(b), b ^= ls * t, Copy(a, b);
        } else if (op == 3) {
            read(b), b ^= ls * t, printf("%lld\n", ls = Dis(a, b));
        } else if (op == 4) {
            printf("%lld\n", ls = SubTree(a));
        }
    }
    return 0;
}
