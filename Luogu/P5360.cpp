#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 110;
const int M = 10010;
const int C = N * M;

struct tcurts {
    int fa[C];
    int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        return fa[x] = y, true;
    }
} E;

struct node {
    int l, r, x, tag;
} T[C << 2];

void pushdown(int rt) { 
    T[rt << 1].tag = T[rt << 1 | 1].tag = T[rt << 1].x = T[rt << 1 | 1].x = T[rt].tag, T[rt].tag = -1; 
}

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
} 

void update(int rt, int start, int end, int x) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) return T[rt].tag = T[rt].x = x, void();
    if (T[rt].tag != -1) pushdown(rt);
    if (start <= mid) update(rt << 1, start, end, x);
    if (end > mid) update(rt << 1 | 1, start, end, x);
}

int query(int rt, int x) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l == r) return T[rt].x;
    if (T[rt].tag != -1) pushdown(rt);
    if (x <= mid) return query(rt << 1, x);
    return query(rt << 1 | 1, x);
}

struct edge {
    int to, next;
} e[C * 2];

int head[C], ecnt;

void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int dfn[C], ed[C], dfsn, dep[C], fa[C];

void dfs(int u, int f) {
    dfn[u] = ++dfsn, fa[u] = f, dep[u] = dep[f] + 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u);
    ed[u] = dfsn;
}

vector<int> pre[M], suf[M]; LL val1[M], val2[M];

int from[C * 4], to[C * 4], w[C * 4], tag[C * 4], p[C * 4];

pair<LL, vector<int>> kruskal(vector<int> ed, bool tag = true) {
    sort(ed.begin(), ed.end(), [&](int a, int b){ 
        if (w[a] == w[b]) return ::tag[a] > ::tag[b];
        return w[a] < w[b]; 
    });
    vector<int> U, V;
    if (tag) for (auto t : ed) U.push_back(query(1, dfn[from[t]])), V.push_back(query(1, dfn[to[t]]));
    else for (auto t : ed) U.push_back(from[t]), V.push_back(to[t]);
    int m = ed.size();
    for (int i = 0; i < m; i++) E.fa[U[i]] = U[i], E.fa[V[i]] = V[i];
    LL res = 0; vector<int> use;
    for (int i = 0; i < m; i++) if (E.merge(U[i], V[i])) 
        res += w[ed[i]], use.push_back(ed[i]);
    return make_pair(res, use);
}

vector<int> L[M], R[M], nw[M];

void fuck(vector<int> &tmp) {
    sort(tmp.begin(), tmp.end(), [&](int a, int b) { return dep[p[a]] < dep[p[b]]; });
    tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());
    for (auto t : tmp) if (tag[t]) update(1, dfn[p[t]], ed[p[t]], p[t]);
}

void push(vector<int> &a, vector<int> b) {
    for (auto t : b) a.push_back(t);
}

void cut(int id) {
    vector<int> tmp = L[id]; push(tmp, R[id]), push(tmp, nw[id]), fuck(tmp);
}

LL extend(vector<int> base, vector<int> &nw, vector<int> ed, int id) {
    update(1, 1, 1e9, 1), cut(id);
    for (auto t : ed) base.push_back(t);
    auto [A, B] = kruskal(base);
    LL res = 0;
    for (auto t : B) {
        if (!tag[t]) nw.push_back(t);
        else res += w[t];
    }
    return res;
}

unsigned int SA, SB, SC; int lim;
int getweight() { SA ^= SA << 16, SA ^= SA >> 5, SA ^= SA << 1; unsigned int t = SA; SA = SB, SB = SC, SC ^= t ^ SA; return SC % lim + 1; }

int main() {
    int n, m, cnt = 0; scanf("%d%d%u%u%u%d", &n, &m, &SA, &SB, &SC, &lim);
    auto id = [&](int i, int j) { return (i - 1) * m + j; };
    vector<int> all;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int w = getweight(); cnt++, from[cnt] = id(i, j), R[j].push_back(cnt), ::w[cnt] = w, all.push_back(cnt);
            if (j < m) to[cnt] = id(i, j + 1), L[j + 1].push_back(cnt);
            else to[cnt] = id(i, 1), L[1].push_back(cnt);
        }
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++) {
            int w = getweight(); cnt++, from[cnt] = id(i, j), to[cnt] = id(i + 1, j), all.push_back(cnt);
            nw[j].push_back(cnt), ::w[cnt] = w;
        }
    // for (auto t : all) cout << from[t] << ' ' << to[t] << ' ' << w[t] << endl;
    auto [A, B] = kruskal(all, false);
    for (auto t : B) tag[t] = 1, adde(from[t], to[t]);
    int sz = n * m; build(1, 1, sz), dfs(1, 0);
    for (auto t : B) p[t] = dep[from[t]] < dep[to[t]] ? to[t] : from[t];
    for (auto t : nw[1]) if (tag[t]) val1[1] += w[t]; else pre[1].push_back(t);
    for (auto t : nw[m]) if (tag[t]) val2[m] += w[t]; else suf[m].push_back(t);
    for (int i = 2; i < m; i++) {
        vector<int> tmp = L[i]; push(tmp, nw[i]);
        val1[i] = val1[i - 1] + extend(pre[i - 1], pre[i], tmp, i);
    }
    for (int i = m - 1; i > 1; i--) {
        vector<int> tmp;
        for (auto t : R[i]) tmp.push_back(t);
        for (auto t : nw[i]) tmp.push_back(t);
        val2[i] = val2[i + 1] + extend(suf[i + 1], suf[i], tmp, i);
    }
    // for (auto t : suf[3]) cout << from[t] << ' ' << to[t] << ' ' << w[t] << endl;
    // cout << "fuck: " << val2[3] << endl;
    int q; scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        update(1, 1, 1e9, 1);
        vector<int> t = L[l]; push(t, R[r]), push(t, R[m]), fuck(t); 
        vector<int> tmp = R[m]; LL res = val1[l - 1] + val2[r + 1];
        for (auto t : pre[l - 1]) tmp.push_back(t);
        for (auto t : suf[r + 1]) tmp.push_back(t);
        auto [A, B] = kruskal(tmp);
        for (auto t : B) res += w[t];
        printf("%lld\n", res);
    }
}