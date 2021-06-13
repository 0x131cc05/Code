#include <bits/stdc++.h>
using namespace std;

const int N = 80010;
const int MAGIC = 3000;
const int mod = 998244353;
const int inv2 = (mod + 1) / 2;

typedef long long LL;
typedef pair<int, int> P;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N << 2], wn[2][N << 2];

void pre(int len) {
    wn[0][0] = wn[1][0] = 1, wn[1][1] = Pow(3, (mod - 1) / len), wn[0][1] = Pow(wn[1][1], mod - 2);
    for (int i = 2; i < len; i++) {
        wn[0][i] = (LL)wn[0][1] * wn[0][i - 1] % mod;
        wn[1][i] = (LL)wn[1][1] * wn[1][i - 1] % mod;
    }
}

int Add(int x, int y) {
    return x + y >= mod ? x + y - mod : x + y;
}

void NTT(int a[], int len, int type) {
    for (int i = 1; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int step = len / mid;
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++) {
                int w = wn[type][(j - i) * step], t = (LL)w * a[j + (mid >> 1)] % mod;
                a[j + (mid >> 1)] = Add(a[j], mod - t), a[j] = Add(a[j], t);
            }
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt, d[N], fa[17][N];

void adde(int from, int to) {
    d[from]++, d[to]++;
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

int dep[N], dfn[N], ed[N], dfsn, _dep[N];

void dfs(int u, int f) {
    fa[0][u] = f, _dep[u] = _dep[f] + 1;
    for (int i = 1; i < 17; i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    dfn[u] = ++dfsn;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u);
    ed[u] = dfsn;
}

int vis[N];

void getDep(int u, int f) {
    dep[u] = dep[f] + 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !vis[e[i].to]) 
            getDep(e[i].to, u);
}

int sz[N], n;

void getSize(int u, int f) {
    sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !vis[e[i].to]) getSize(e[i].to, u), sz[u] += sz[e[i].to];
}

int getRoot(int u, int f, int tot) {
    for (int i = head[u], tmp = 0; i; i = e[i].next)
        if (e[i].to != f && !vis[e[i].to] && (tmp = getRoot(e[i].to, u, tot))) 
            return tmp;
    if (sz[u] >= (tot >> 1)) return u;
    return 0;
}

int jump(int u, int v) {
    for (int i = 16; i >= 0; i--) if (_dep[fa[i][u]] > _dep[v]) u = fa[i][u];
    return u;
}

int realSize(int u, int v, int t) {
    if (dfn[u] <= dfn[v] && dfn[v] <= ed[u]) 
        return n - (ed[t] - dfn[t] + 1);
    return ed[u] - dfn[u] + 1;
}

int realSize(int u, int v) { // u is in v's subtree
    if (dfn[u] <= dfn[v] && dfn[v] <= ed[u]) {
        int t = jump(v, u);
        return n - (ed[t] - dfn[t] + 1);
    }
    return ed[u] - dfn[u] + 1;
}

int res = 0, pw[N], iv[N], frac[N << 2], inv[N << 2];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int rt;

void dfsForBf(int u, int f, int d, int bl) {
    if (u < rt) {
        int sz = realSize(u, rt, f), sz1 = realSize(rt, u, bl);
        res = (res + (LL)pw[n - d - 1] * (C(sz + sz1, sz) - 1)) % mod;
    }
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !vis[e[i].to]) dfsForBf(e[i].to, u, d + 1, bl);
}

void bf(vector<int> p) {
    for (auto u : p) {
        rt = u;
        for (int i = head[u]; i; i = e[i].next)
            if (!vis[e[i].to]) dfsForBf(e[i].to, u, 1, e[i].to);
    }
}

vector<int> p;

void push(int u, int f) {
    p.push_back(u);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !vis[e[i].to]) push(e[i].to, u);
}

int A[N << 2], D[N << 2];

vector<P> B; int ctB, ctA;

void dfs(int u, int f, int rt, int d) {
    int pos = realSize(u, rt), w = (LL)iv[d] * inv[pos] % mod;
    res = (res + (LL)pw[n - 1 - d] * (C(pos + realSize(rt, u), pos) - 1)) % mod;
    B.push_back(P(pos, w)); ctB = Add(ctB, iv[d]);
    A[pos] = Add(A[pos], w), ctA = Add(ctA, iv[d]);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !vis[e[i].to]) 
            dfs(e[i].to, u, rt, d + 1);
}

int len;

void divide(int u, int all) {
    if (all < MAGIC) {
        p.clear(), push(u, 0), bf(p);
        return;
    }
    u = getRoot(u, 0, all), vis[u] = 1, ctA = 0;
    for (int i = 0; i < len; i++) A[i] = 0;
    int tot = 0;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) {
            B.clear(), ctB = 0;
            dfs(e[i].to, u, u, 1);
            if (B.size() < MAGIC) {
                for (auto a : B) for (auto b : B) 
                    tot = (tot - (LL)a.second * b.second % mod * frac[a.first + b.first]) % mod;
            } else {
                for (int t = 0; t < len; t++) D[t] = 0;
                for (auto a : B) 
                    D[a.first] = Add(D[a.first], a.second);
                NTT(D, len, 1);
                for (int i = 0; i < len; i++) D[i] = (LL)D[i] * D[i] % mod;
                NTT(D, len, 0);
                for (int i = 0; i < len; i++) 
                    tot = (tot - (LL)D[i] * frac[i]) % mod;
            }
            tot = (tot + (LL)ctB * ctB) % mod;
        }
    NTT(A, len, 1);
    for (int i = 0; i < len; i++) A[i] = (LL)A[i] * A[i] % mod;
    NTT(A, len, 0);
    for (int i = 0; i < len; i++) 
        tot = (tot + (LL)A[i] * frac[i]) % mod;
    tot = (tot - (LL)ctA * ctA % mod + mod) % mod;
    res = (res + (LL)tot * pw[n - 1] % mod * inv2) % mod;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) getSize(e[i].to, u), divide(e[i].to, sz[e[i].to]); 
}

int one() {
    int tot = 0;
    for (int i = 1; i <= n; i++)
        for (int j = head[i]; j; j = e[j].next)
            if (e[j].to < i) 
                tot = Add(tot, C(realSize(e[j].to, i) + realSize(i, e[j].to), realSize(i, e[j].to)) - 1);
    return tot;
}

int two() {
    int tot = 0;
    for (int i = 1; i <= n; i++) 
        if (d[i] < MAGIC) {
            for (int j = head[i]; j; j = e[j].next)
                for (int k = e[j].next; k; k = e[k].next)
                    tot = Add(tot, C(realSize(e[j].to, e[k].to, i) + realSize(e[k].to, e[j].to, i), realSize(e[k].to, e[j].to, i)) - 1);
        } else {
            int tmp = 0, sum = 0;
            for (int i = 0; i < len; i++) A[i] = 0;
            for (int j = head[i]; j; j = e[j].next) {
                int w = realSize(e[j].to, i);
                A[w] = Add(A[w], inv[w]), sum++;
                tmp = Add(tmp, mod - C(w + w, w) + 1);
            }
            NTT(A, len, 1);
            for (int i = 0; i < len; i++) A[i] = (LL)A[i] * A[i] % mod;
            NTT(A, len, 0);
            for (int i = 0; i < len; i++) tmp = (tmp + (LL)frac[i] * A[i]) % mod;
            tmp = (tmp - (LL)sum * sum) % mod;
            tot = (tot + (LL)tmp * inv2) % mod;
            tot = (tot + mod) % mod;
        }
    return tot;
}

int main() {
    int m; scanf("%d%d", &n, &m);
    len = 1; int l = 0;
    while (len <= n * 2) len <<= 1, l++;
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    frac[0] = inv[0] = pw[0] = iv[0] = 1, pre(len);
    for (int i = 1; i < len; i++) 
        frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 1; i <= n; i++)
        pw[i] = (LL)pw[i - 1] * (m + 1) % mod, iv[i] = Pow(pw[i], mod - 2);
    for (int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b), adde(a, b);
    }
    dfs(1, 0), getSize(1, 0), divide(1, sz[1]);
    int A = one(), B = two(), C = (Pow(2, n) - 1 - (A - B)) % mod;
    int ans = (LL)C * pw[n - 1] % mod + 1;
    ans = (ans + (LL)res * ((1 - 2 * (m + 1) + (LL)(m + 1) * (m + 1)) % mod)) % mod;
    ans = (ans - (LL)(m + 1) * (m + 1) % mod * B % mod * pw[n - 3]) % mod;
    ans = (ans - ((LL)(m + 1) * (m + 1) - 2 * (m + 1)) % mod * A % mod * pw[n - 2]) % mod;
    ans = (ans + mod) % mod;
    printf("%d\n", ans);
}