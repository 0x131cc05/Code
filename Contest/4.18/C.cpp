#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int M = 1000010;

int fa[N + M], mx[N + M], at[N + M], v[N + M], ch[2][N + M], rev[N + M];
 
inline void connect(int u, int f, int son) { fa[u] = f, ch[son][f] = u, fa[0] = 0; }

inline bool isroot(int u) { return (u != ch[1][fa[u]] && u != ch[0][fa[u]]) || !u; }

inline bool child(int u) { return u == ch[1][fa[u]]; }

inline void pushdown(int u) {
    if (!rev[u]) return;
    swap(ch[0][u], ch[1][u]), rev[ch[0][u]] ^= 1, rev[ch[1][u]] ^= 1, rev[u] = 0;
}

inline void pushup(int u) {
    if (mx[ch[0][u]] < mx[ch[1][u]]) mx[u] = mx[ch[1][u]], at[u] = at[ch[1][u]];
    else mx[u] = mx[ch[0][u]], at[u] = at[ch[0][u]];
    if (v[u] > mx[u]) mx[u] = v[u], at[u] = u;
}

inline void rotate(int u) {
    int f = fa[u], ff = fa[f], tmp = child(u), tmp1 = child(f);
    if (!isroot(f)) connect(u, ff, tmp1);
    fa[u] = ff, connect(ch[tmp ^ 1][u], f, tmp), connect(f, u, tmp ^ 1);
    pushup(f), pushup(u);
}

int st[N + M];

inline void splay(int u) {
    int now = u, top = 0; st[++top] = u;
    while (!isroot(now)) st[++top] = now = fa[now];
    while (top) pushdown(st[top--]);
    for (; !isroot(u); rotate(u))
        if (!isroot(fa[u])) 
            rotate((child(u) ^ child(fa[u])) ? u : fa[u]);
}

inline void access(int u) {
    for (int ls = 0; u; u = fa[ls = u]) splay(u), ch[1][u] = ls, pushup(u);
}

inline int findroot(int u) {
    access(u), splay(u);
    while (ch[0][u]) u = ch[0][u];
    return u;
}

inline void makeroot(int u) { 
    access(u), splay(u), rev[u] ^= 1; 
}

inline void split(int a, int b) { 
    makeroot(a), access(b), splay(b); 
}

inline void link(int a, int b) { 
    makeroot(a), fa[a] = b; 
}

int n;

struct ed {

int u, v, k;

bool operator < (const ed &b) const {
    return k < b.k;
}

};

vector<ed> A, B;

int _fa[N], ncnt;

int find(int x) { return x == _fa[x] ? x : _fa[x] = find(_fa[x]); }

inline int update(int a, int b, int w) { // 返回整棵树权值的变化量
    int id = ++ncnt; split(a, b); 
    if (mx[b] < -1e9) return INT_MAX;
    int t = at[b], delta = w - mx[b]; 
    makeroot(t), ch[0][t] = ch[1][t] = fa[ch[0][t]] = fa[ch[1][t]] = 0;
    v[id] = mx[id] = -1e9 - 1, at[id] = id, link(id, a), link(id, b);
    return delta;
}

typedef long long LL;
typedef pair<int, int> P;

vector<P> fuck;

inline LL pushall() {
    ncnt = n, mx[0] = -1e9 - 2; LL val = 0;
    for (int i = 1; i <= n; i++) _fa[i] = i, v[i] = mx[i] = -1e9 - 1, at[i] = i;
    sort(A.begin(), A.end());
    for (auto t : A) 
        if (find(t.u) != find(t.v)) {
            ncnt++, v[ncnt] = mx[ncnt] = t.k, at[ncnt] = ncnt, val += t.k;
            link(ncnt, t.u), link(ncnt, t.v), _fa[find(t.u)] = find(t.v);
        }
    return val;
}

LL zjk[N];

int main() {
    freopen("dat.in", "r", stdin), freopen("orz.out", "w", stdout);
    int a, b, q; scanf("%d%d%d%d", &n, &a, &b, &q);
    for (int i = 1; i <= a; i++) {
        int u, v, k; scanf("%d%d%d", &u, &v, &k);
        A.push_back((ed){ u, v, k });
    }
    for (int i = 1; i <= b; i++) {
        int u, v, k; scanf("%d%d%d", &u, &v, &k);
        B.push_back((ed){ u, v, k });
    }
    LL base = pushall(); sort(B.begin(), B.end()); int tp = 0;
    fuck.push_back(P(-1e9, 0));
    for (auto t : B) {
        if (tp == n - 1) break;
        int delta = update(t.u, t.v, t.k);
        // cout << t.u << ' ' << t.v << endl;
        if (delta != INT_MAX) {
            int t = (delta + 1) / 2;
            // cout << t << endl;
            fuck.push_back(P(t, delta));
        }
    }
    sort(fuck.begin(), fuck.end()), zjk[0] = base;
    for (int i = 1; i < fuck.size(); i++) zjk[i] = zjk[i - 1] + fuck[i].second;
    for (int i = 1; i <= q; i++) {
        int x, l = 0, r = fuck.size() - 1, pos = 0; scanf("%d", &x);
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (fuck[mid].first <= x) pos = mid, l = mid + 1;
            else r = mid - 1;
        }
        printf("%lld\n", zjk[pos] + (LL)(n - 1 - 2 * pos) * x);
    }
    return 0;
}
