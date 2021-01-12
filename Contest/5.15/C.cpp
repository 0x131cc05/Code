#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast")

const int N = 3510;

typedef pair<int, int> P;
typedef long long LL;

vector<int> G[N];

vector<P> fucked[N * 2]; 

int dfn[N], ed[N], dfsn, from[N * 2], to[N * 2], del[N], chg[N];

void dfs(int u) {
    dfn[u] = ++dfsn;
    for (auto v : G[u]) dfs(v);
    ed[u] = dfsn, fucked[del[u]].push_back(P(dfn[u], ed[u]));
    from[chg[u]] = dfn[u], to[chg[u]] = ed[u];
} 

struct Item {
    int a, b, c;
};

vector<Item> T[N << 2];

void push(int rt, int l, int r, int start, int end, Item t) {
//    if (rt == 1) cout << "push: " << start << ' ' << end << ' ' << t.a << ' ' << t.b << ' ' << t.c << endl;
    if (start > end) return;
    if (start <= l && r <= end) return T[rt].push_back(t), void();
    int mid = (l + r) >> 1;
    if (start <= mid) push(rt << 1, l, mid, start, end, t);
    if (end > mid) push(rt << 1 | 1, mid + 1, r, start, end, t);
}

int m, k;

LL ans[N], dp[15][N];

inline void insert(LL dp[], LL base[], LL a, LL b, LL c) {
    for (int i = 0; i <= m - c; i++) dp[i + c] = base[i] + a;
    for (int i = 0; i < c; i++) dp[i] = -1e18;
    int t = k - 1;
    if (t * c < m) { // fuck TLE!!!
        for (int i = 0; (1 << i) <= t; i++) {
            LL B = b << i, C = c << i; t -= 1 << i;
            if (C > m) break;
            for (int i = m - C; i >= 0; i--) dp[i + C] = max(dp[i + C], dp[i] + B);
        }
        if (t) {
            LL B = (LL)t * b, C = (LL)t * c;
            for (int i = m - C; i >= 0; i--) dp[i + C] = max(dp[i + C], dp[i] + B);
        }
    } else {
        for (int i = 0; i <= m - c; i++) 
            dp[i + c] = max(dp[i + c], dp[i] + b);
    }
    for (int i = 0; i <= m; i++) dp[i] = max(dp[i], base[i]);
}

LL tmp[N];

void solve(int rt, int l, int r, int dep) {
    for (int i = 0; i <= m; i++) dp[dep][i] = dp[dep - 1][i];
    for (auto t : T[rt]) {
        for (int i = 0; i <= m; i++) tmp[i] = dp[dep][i];
        insert(dp[dep], tmp, t.a, t.b, t.c);
    }
    if (l == r) return ans[l] = dp[dep][m], void();
    int mid = (l + r) >> 1;
    solve(rt << 1, l, mid, dep + 1), solve(rt << 1 | 1, mid + 1, r, dep + 1);
}

Item item[N * 2]; int tot, wkr[N][N];

int main() {
    int n, q; scanf("%d%d%d%d", &n, &q, &m, &k), tot = n;
    for (int i = 1; i <= n; i++) scanf("%d%d%d", &item[i].c, &item[i].a, &item[i].b);
    for (int i = 1; i <= n; i++) wkr[0][i] = i, from[i] = 1, to[i] = q + 1;
    for (int i = 1; i <= q; i++) {
        int s, p, x, y; scanf("%d%d%d%d", &s, &p, &x, &y);
        for (int j = 1; j <= n; j++) wkr[i][j] = wkr[s][j];
        del[i] = wkr[i][p], chg[i] = wkr[i][p] = ++tot;
        item[tot] = item[del[i]], item[tot].a = x, item[tot].b = y, G[s].push_back(i);
    }
    dfs(0);
    for (int i = 1; i <= tot; i++) {
        int ls = from[i] - 1;
        for (auto t : fucked[i]) 
            push(1, 1, q + 1, ls + 1, t.first - 1, item[i]), ls = t.second;
        push(1, 1, q + 1, ls + 1, to[i], item[i]);
    }
    solve(1, 1, q + 1, 1);
    for (int i = 1; i <= q; i++) printf("%lld\n", ans[dfn[i]]);
}
