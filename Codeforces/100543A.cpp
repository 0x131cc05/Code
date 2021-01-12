#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

vector<int> G[N];

int dep[N], fa[N][12], bel[N];

void dfs(int u, int f) {
    dep[u] = dep[f] + 1, fa[u][0] = f;
    for (int i = 1; i < 10; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = 0; i < G[u].size(); i++) if (G[u][i] != f) 
        dfs(G[u][i], u), bel[G[u][i]] = i;
}

int LCA(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 9; i >= 0; i--) if (dep[fa[a][i]] >= dep[b]) a = fa[a][i];
    if (a == b) return a;
    for (int i = 9; i >= 0; i--) if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
    return fa[a][0];
}

int jump(int a, int lca) {
    for (int i = 9; i >= 0; i--) if (dep[fa[a][i]] > dep[lca]) a = fa[a][i];
    return a;
}

bitset<N> ok[N];

vector<int> fuck[N];

int A[N * N], B[N * N], tA[N * N], tB[N * N], dp[N];

void dfs1(int u, int f) {
    bitset<N> tmp;
    for (auto v : G[u]) if (v != f)
        dfs1(v, u), tmp |= ok[v], dp[u] += dp[v];
    int tot = G[u].size();
    vector<int> wkr(1 << tot);
    for (auto t : fuck[u]) {
        if (A[t] != u && !tmp[A[t]]) continue;
        if (B[t] != u && !tmp[B[t]]) continue;
        int cur = 0;
        if (A[t] != u) cur |= 1 << bel[tA[t]];
        if (B[t] != u) cur |= 1 << bel[tB[t]];
        assert(cur < (1 << tot));
        wkr[cur] = 1;
    }
    for (int s = 1; s < 1 << tot; s++) {
        int t = 1 << __builtin_ctz(s);
        wkr[s] = max(wkr[s], wkr[s ^ t] + wkr[t]);
        for (int i = 0; i < tot; i++) 
            if (t != (1 << i) && (s & (1 << i)))
                wkr[s] = max(wkr[s], wkr[s ^ t ^ (1 << i)] + wkr[t | (1 << i)]);
    }
    int hh = *max_element(wkr.begin(), wkr.end()), all = (1 << tot) - 1;
    dp[u] += hh;
    for (int s = 0; s < 1 << tot; s++) 
        if (wkr[s] == hh) all &= s;
    ok[u][u] = 1;
    for (int i = 0; i < G[u].size(); i++) if (G[u][i] != f && !(all & (1 << i))) 
        ok[u] |= ok[G[u][i]];
} 

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; i++) G[i].clear(), fuck[i].clear(), dp[i] = 0, ok[i].reset();
        for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), G[a].push_back(b), G[b].push_back(a);
        dfs(1, 0);
        int m; scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", &A[i], &B[i]);
            int lca = LCA(A[i], B[i]);
            if (A[i] != lca) tA[i] = jump(A[i], lca);
            if (B[i] != lca) tB[i] = jump(B[i], lca);
            // cout << lca << endl;
            fuck[lca].push_back(i);
        }
        dfs1(1, 0), printf("%d\n", dp[1]);
    }
}
