#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef pair<int, int> P;
typedef long long LL;

struct node {
    int l, r, mn, ct, tag;
} T[N << 2];

void pushup(int rt) {
    T[rt].mn = min(T[rt << 1].mn, T[rt << 1 | 1].mn), T[rt].ct = 0;
    if (T[rt].mn == T[rt << 1].mn) T[rt].ct += T[rt << 1].ct;
    if (T[rt].mn == T[rt << 1 | 1].mn) T[rt].ct += T[rt << 1 | 1].ct;
}

void pushdown(int rt) {
    T[rt << 1].tag += T[rt].tag, T[rt << 1 | 1].tag += T[rt].tag;
    T[rt << 1].mn += T[rt].tag, T[rt << 1 | 1].mn += T[rt].tag, T[rt].tag = 0;
}

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return T[rt].mn = 0, T[rt].ct = 1, void();
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r), pushup(rt);
}

void update(int rt, int start, int end, int x) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) return T[rt].tag += x, T[rt].mn += x, void();
    if (T[rt].tag) pushdown(rt);
    if (start <= mid) update(rt << 1, start, end, x);
    if (end > mid) update(rt << 1 | 1, start, end, x);
    pushup(rt);
}

vector<int> G[N];

int dfn[N], dfsn, ed[N];

void dfs(int u) {
    dfn[u] = ++dfsn;
    for (auto v : G[u]) dfs(v);
    ed[u] = dfsn;
}

string mp[N]; bool flag[N];
vector<P> add[N], del[N];

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> mp[i];
    auto id = [&](int i, int j) { return (i - 1) * m + j; };
    auto adde = [&](int a, int b) {
        G[a].push_back(b), flag[b] = 1;
    };
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c = mp[i][j - 1];
            if (c == 'U') {
                if (i != 1) adde(id(i - 1, j), id(i + 1, j));
                if (i != n - 1) adde(id(i + 2, j), id(i, j));
            } else if (c == 'L') {
                if (j != 1) adde(id(i, j - 1), id(i, j + 1));
                if (j != m - 1) adde(id(i, j + 2), id(i, j));
            }
        }
    int all = n * m; build(1, 1, all);
    for (int i = 1; i <= all; i++) if (!flag[i]) dfs(i);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c = mp[i][j - 1]; int u = -1, v = -1;
            if (c == 'U') u = id(i, j), v = id(i + 1, j);
            else if (c == 'L') u = id(i, j), v = id(i, j + 1);
            if (u != -1) {
                if ((i + j) & 1) swap(u, v);
                add[dfn[u]].push_back(P(dfn[v], ed[v]));
                del[ed[u] + 1].push_back(P(dfn[v], ed[v]));
            }
        }
    LL res = 0;
    for (int i = 1; i <= all; i++) {
        for (auto v : add[i]) update(1, v.first, v.second, 1);
        for (auto v : del[i]) update(1, v.first, v.second, -1);
        if (T[1].mn == 0) res += all - T[1].ct;
        else res += all;
    }
    cout << res << endl;
}