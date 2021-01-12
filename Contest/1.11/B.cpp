#include <bits/stdc++.h>
using namespace std;

const int N = 400010;

typedef pair<int, int> P;

struct node {
    int l, r, mn;
} T[N << 2]; 

void pushup(int rt) {
    T[rt].mn = min(T[rt << 1].mn, T[rt << 1 | 1].mn);
}

void build(int rt, int l, int r) {
    T[rt].mn = 1e9, T[rt].l = l, T[rt].r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
}

int query(int rt, int start, int end) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1, res = 1e9;
    if (start <= l && r <= end) return T[rt].mn;
    if (start <= mid) res = min(res, query(rt << 1, start, end));
    if (end > mid) res = min(res, query(rt << 1 | 1, start, end));
    return res;
}

void update(int rt, int pos, int x) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l == r) return T[rt].mn = x, void();
    if (pos <= mid) update(rt << 1, pos, x);
    else update(rt << 1 | 1, pos, x);
    pushup(rt);
}

set<int> s;
vector<int> G[N * 2];
vector<P> G1[N * 2];

int dfn[N * 2], dfsn, low[N * 2], n, scc[N * 2], vis[N * 2], tot;
vector<int> stk;

void tarjan(int u) {
    // cout << "tarjan: " << u << endl;
    dfn[u] = low[u] = ++dfsn, vis[u] = 1, stk.push_back(u);
    if (u <= n) s.erase(u), update(1, u, dfsn); // 0
    for (auto v : G[u]) 
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (vis[v]) low[u] = min(low[u], dfn[v]);
    for (auto v : G1[u]) {
        int l = v.first, r = v.second;
        while (233) {
            auto pos = s.lower_bound(l);
            if (pos != s.end() && *pos <= r) {
                int t = *pos; 
                tarjan(t), low[u] = min(low[u], low[t]);
            } else break;
        }
        low[u] = min(low[u], query(1, l, r));
    }
    if (low[u] >= dfn[u]) {
        tot++;
        while (stk.size()) {
            int v = stk.back(); stk.pop_back();
            vis[v] = 0, scc[v] = tot;
            if (v <= n) update(1, v, 1e9);
            if (u == v) break;
        }
    }
}

int wkr[N], zjk[N];

int main() {
    freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
    int m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int op, a, b; scanf("%d%d%d", &op, &a, &b);
        if (op == 1) G[a + n].push_back(b), G[b + n].push_back(a);
        else if (op == 2) G[a].push_back(b + n), G[b].push_back(a + n);
        else wkr[a] = max(wkr[a], b);
    }
    set<int> L, R;
    for (int i = 1; i <= n; i++) zjk[i] = 1e9;
    for (int i = 1; i <= n; i++) zjk[wkr[i]] = min(zjk[wkr[i]], i);
    for (int i = 1; i <= n; i++) L.insert(zjk[i]);
    for (int i = 1; i <= n; i++) {
        if (wkr[i]) R.insert(wkr[i]);
        if (L.size() && R.size()) {
            int l = *L.begin(), r = *R.rbegin();
            if (l <= i - 1) G1[i + n].push_back(P(l, i - 1));
            if (i + 1 <= r) G1[i + n].push_back(P(i + 1, r));
        } 
        L.erase(zjk[i]);
    }
    for (int i = 1; i <= n; i++) s.insert(i);
    build(1, 1, n); 
    for (int i = 1; i <= n * 2; i++) if (!dfn[i]) tarjan(i);
    // for (int i = 1; i <= n * 2; i++) cout << scc[i] << ' ';
    // cout << endl;
    for (int i = 1; i <= n; i++) if (scc[i] == scc[i + n]) return puts("-1"), 0;
    puts("1");
    for (int i = 1; i <= n; i++) 
        printf("%d ", scc[i] > scc[i + n]);
}