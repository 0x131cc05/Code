#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

vector<int> G[N];
vector<tuple<int, int, int>> ed[N];

void adde(int from, int to) {
    G[from].push_back(to), G[to].push_back(from);
}

int dp[N][11], dep[N], fa[10][N], id[N];

void dfs(int u, int f) {
    fa[0][u] = f, dep[u] = dep[f] + 1;
    for (int i = 1; i < 10; i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (int i = 0; i < G[u].size(); i++) if (G[u][i] != f) 
        dfs(G[u][i], u), id[G[u][i]] = i + 1;
}

int LCA(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 9; i >= 0; i--) if (dep[fa[i][a]] >= dep[b]) a = fa[i][a];
    if (a == b) return a;
    for (int i = 9; i >= 0; i--) if (fa[i][a] != fa[i][b]) a = fa[i][a], b = fa[i][b];
    return fa[0][a];
}

void dfs1(int u, int f) {
    for (auto v : G[u]) if (v != f) dfs1(v, u);
    static int val[1 << 10]; memset(val, 0, sizeof(val));
    for (auto v : G[u]) if (v != f) 
        val[1 << id[v] - 1] = dp[v][0];
    for (auto t : ed[u]) {
        int a = get<0>(t), b = get<1>(t), res = dp[a][0] + dp[b][0];
        while (u != a && fa[0][a] != u) 
            res += dp[fa[0][a]][id[a]], a = fa[0][a];
        while (u != b && fa[0][b] != u)
            res += dp[fa[0][b]][id[b]], b = fa[0][b];
        int st = 0;
        if (a != u) st |= 1 << id[a] - 1;
        if (b != u) st |= 1 << id[b] - 1;
        val[st] = max(val[st], res + get<2>(t));
    }
    int tot = G[u].size();
    assert(tot <= 10);
    for (int s = 1; s < 1 << tot; s++) {
        for (int i = 1; i <= tot; i++) if (s & (1 << i - 1)) 
            val[s] = max(val[s], val[s ^ (1 << i - 1)] + val[1 << i - 1]);
        for (int i = 1; i <= tot; i++) if (s & (1 << i - 1))
            for (int j = i + 1; j <= tot; j++) if (s & (1 << j - 1))
                val[s] = max(val[s], val[s ^ (1 << i - 1) ^ (1 << j - 1)] + val[(1 << i - 1) | (1 << j - 1)]);
    }
    for (int i = 1; i <= tot; i++)
        dp[u][i] = val[((1 << tot) - 1) ^ (1 << i - 1)];
    dp[u][0] = val[(1 << tot) - 1];
}

int main() {
//    freopen("training7.in", "r", stdin), freopen("training7.ans", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    vector<tuple<int, int, int>> t;
    for (int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        if (!c) adde(a, b);
        else t.push_back(make_tuple(a, b, c));
    }
    dfs(1, 0); int sum = 0;
    for (auto p : t) {
        int u = get<0>(p), v = get<1>(p);
        sum += get<2>(p);
        if ((dep[u] + dep[v]) % 2 == 1) continue;
        ed[LCA(u, v)].push_back(p);
    }
    dfs1(1, 0), printf("%d\n", sum - dp[1][0]);
}
