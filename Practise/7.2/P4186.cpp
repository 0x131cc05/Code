#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

vector<int> G[N];

set<int> s[N];

int rt[N];

void merge(int u, int v) {
    if (s[rt[u]].size() < s[rt[v]].size()) swap(rt[u], rt[v]);
    for (auto t : s[rt[v]])
        s[rt[u]].insert(t);
    s[rt[v]].clear();
}

int dp[N], dep[N];

void dfs(int u, int f) {
    rt[u] = u, dep[u] = dep[f] + 1;
    if (G[u].size() == 1) {
        s[rt[u]].insert(dep[u]);
        dp[u] = 1;
        return;
    }
    dp[u] = 0;
    for (auto v : G[u]) if (v != f) 
        dfs(v, u), merge(u, v), dp[u] += dp[v];
    if (s[rt[u]].count(dep[u] * 2 - 1) || s[rt[u]].count(dep[u] * 2 - 2)) 
        dp[u] = 1;
}

int main() {
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        G[a].push_back(b), G[b].push_back(a);
    }
    if (G[k].size() == 1) return puts("1"), 0;
    dfs(k, 0), printf("%d\n", dp[k]);
}