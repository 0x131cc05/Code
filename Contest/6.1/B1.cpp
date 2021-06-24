#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline int Add(int x, int y) {
    x += y; return x >= mod ? x - mod : x;
}

inline void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int C1[11][11];

struct WEN {

int coef[11];

WEN() { memset(coef, 0, sizeof(coef)); }

inline WEN wkr(int k, int s) { // (x + s) ^ k
    for (int i = k, w = 1; i >= 0; i--, w = (LL)w * s % mod) 
        coef[i] = (LL)w * C1[k][i] % mod;
    return *this;
}

WEN operator + (const WEN &b) {
    WEN res;
    for (int i = 0; i <= 10; i++)
        res.coef[i] = Add(coef[i], b.coef[i]);
    return res;
}

WEN operator - (const WEN &b) {
    WEN res;
    for (int i = 0; i <= 10; i++)
        res.coef[i] = Add(coef[i], mod - b.coef[i]);
    return res;
}

inline int get(int x) {
    int res = 0;
    for (int i = 0, w = 1; i <= 10; i++, w = (LL)w * x % mod)
        res = (res + (LL)w * coef[i]) % mod;
    return res;
}

} A[11][N], B[11][N], C[11][N], D[11][N], sum[11][N];

vector<int> G[N], leaf;

WEN tmp[11]; int ct[N], l[N], r[N], fa[N][18], dep[N], dfn[N], dfsn, to[N], ed[N];

void pre(int u, int f) {
    fa[u][0] = f, dfn[u] = ++dfsn, to[dfsn] = u, dep[u] = dep[f] + 1;
    for (int i = 1; i < 18; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    if (!G[u].size()) ct[u] = 1, leaf.push_back(u), l[u] = r[u] = leaf.size() - 1;
    else l[u] = 1e9;
    for (auto v : G[u]) 
        pre(v, u), l[u] = min(l[u], l[v]), r[u] = max(r[u], r[v]), ct[u] += ct[v];
    ed[u] = dfsn;
}

inline int LCA(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 17; i >= 0; i--) if (dep[fa[a][i]] >= dep[b]) a = fa[a][i];
    if (a == b) return a;
    for (int i = 17; i >= 0; i--) if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
    return fa[a][0];
}

inline int jump(int a, int lca) {
    for (int i = 17; i >= 0; i--) if (dep[fa[a][i]] > dep[lca]) a = fa[a][i];
    return a;
}

void dfs1(int u, int f) {
    for (int k = 0; k <= 10; k++) {
        A[k][u] = tmp[k];
        B[k][u] = B[k][f] + WEN().wkr(k, r[u]);
    }  
    for (auto v = G[u].rbegin(); v != G[u].rend(); v++) 
        dfs1(*v, u);
    for (int k = 0; k <= 10; k++) 
        tmp[k] = tmp[k] + WEN().wkr(k, ct[u]);
//    cout << "dfs1: " << u << ' ' << A[0][u].get(0) << endl;
}

void dfs2(int u, int f) {
    for (int k = 0; k <= 10; k++) {
        C[k][u] = tmp[k];
        D[k][u] = D[k][f] + WEN().wkr(k, l[u]);
    }
    for (auto v = G[u].begin(); v != G[u].end(); v++) 
        dfs2(*v, u);
    for (int k = 0; k <= 10; k++) 
        tmp[k] = tmp[k] + WEN().wkr(k, ct[u]);
}

inline int solve(int L, int R, int k) {
    L = lower_bound(leaf.begin(), leaf.end(), L) - leaf.begin();
    R = upper_bound(leaf.begin(), leaf.end(), R) - leaf.begin() - 1;
    if (L >= R) return 0;
    int t1 = leaf[L], t2 = leaf[R], tot = R - L + 1;
    int lca = LCA(t1, t2), l1 = jump(t1, lca), r1 = jump(t2, lca);
//    cout << "find: " << lca << ' ' << l1 << ' ' << r1 << endl;
    WEN inside = sum[k][dfn[r1] - 1] - sum[k][ed[l1]] + A[k][t1] - A[k][l1] + C[k][t2] - C[k][r1];
    int all = (sum[0][dfn[r1] - 1] - sum[0][ed[l1]] + A[0][t1] - A[0][l1] + C[0][t2] - C[0][r1]).get(0);
//    cout << all << endl;
    int res = inside.get(mod - tot);
    if (k & 1) res = mod - res;
    Inc(res, inside.get(0));
    WEN outside1 = B[k][t1] - B[k][lca], outside2 = D[k][t2] - D[k][lca];
    int tmp = outside1.get(mod - (L - 1));
    int tmp1 = outside2.get(mod - (R + 1)); if (k & 1) tmp1 = mod - tmp1;
    Inc(res, Add(tmp, tmp1));
    tmp = outside1.get(mod - (tot + L - 1)); if (k & 1) tmp = mod - tmp;
    tmp1 = outside2.get(tot - R - 1 + mod); 
    Inc(res, Add(tmp, tmp1));
    Inc(all, (B[0][t1] - B[0][lca] + D[0][t2] - D[0][lca]).get(0));
//    cout << all << endl;
    res = (LL)res * Pow(Pow(tot, k), mod - 2) % mod;
    return Add(all, mod - res);
}

int main() {
    int type, n, q; scanf("%d%d%d", &type, &n, &q);
    for (int i = 2, a; i <= n; i++) scanf("%d", &a), G[a].push_back(i);
    for (int i = 0; i <= 10; i++) {
        C1[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C1[i][j] = Add(C1[i - 1][j - 1], C1[i - 1][j]);
    }
    pre(1, 0), dfs1(1, 0);
    for (int i = 0; i <= 10; i++) tmp[i] = WEN();
    dfs2(1, 0);
    for (int k = 0; k <= 10; k++)
        for (int i = 1; i <= n; i++)
            sum[k][i] = sum[k][i - 1] + WEN().wkr(k, ct[to[i]]);
    int lastans = 0;
    while (q--) {
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        if (type) l ^= lastans, r ^= lastans;
        printf("%d\n", lastans = solve(l, r, k));
    }
}

