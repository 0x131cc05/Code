#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define per(i, r, l) for(int i = (r); i >= (l); i--)
#define mem(a, b) memset(a, b, sizeof a)
#define For(i, l, r) for(int i = (l), i##e = (r); i < i##e; i++)
#define pb push_back
#define upd(a, b) (a = max(a, b))

using namespace std;

const int N = 1e3 + 5, M = N * 5;

int n, m, a[M], b[M], w[M];

int d[N], lca[N][N], L[N][N], R[N][N];
vector<int> G[N], s[N], T[N], id[N];
int f[N][N], g[1024];

void dfs(int u, int fa) {
    T[u].pb(u);
    for(int v : G[u]) if(v ^ fa) {
        d[v] = d[u] + 1, dfs(v, u), s[u].pb(v);
        T[u].insert(T[u].end(), T[v].begin(), T[v].end());
    }
    For(i, 0, s[u].size()) for(int v : T[s[u][i]])
        lca[u][v] = u, L[u][v] = -1, R[u][v] = i;
    For(i, 0, s[u].size()) For(j, i + 1, s[u].size())
    for(int v1 : T[s[u][i]]) for(int v2 : T[s[u][j]])
        lca[v1][v2] = u, L[v1][v2] = i, R[v1][v2] = j;
}
void Dfs(int u) {
    for(int v : s[u]) Dfs(v);
    int sz = s[u].size(), all = (1 << sz) - 1;
    rep(S, 0, all) g[S] = 0;
    For(i, 0, sz) g[1 << i] = f[s[u][i]][s[u][i]];
    for(int i : id[u]) {
        int j = L[a[i]][b[i]], k = R[a[i]][b[i]];
        if(~j) upd(g[1 << j | 1 << k], f[s[u][j]][a[i]] + f[s[u][k]][b[i]] + w[i]);
        else upd(g[1 << k], f[s[u][k]][b[i]] + w[i]);
    }
    rep(S, 0, all) for(int T = S; T; --T &= S)
        upd(g[S], g[T] + g[S ^ T]);
    f[u][u] = g[all];
    For(i, 0, sz) for(int v : T[s[u][i]])
        f[u][v] = g[all ^ 1 << i] + f[s[u][i]][v];
}
int main() {
    freopen("training.in", "r", stdin);
#ifndef local
    freopen("training.out", "w", stdout);
#endif
    cin >> n >> m;
    int su = 0;
    rep(i, 1, m) {
        scanf("%d%d%d", &a[i], &b[i], &w[i]), su += w[i];
        if(!w[i]) G[a[i]].pb(b[i]), G[b[i]].pb(a[i]);
    }
    dfs(1, 0);
    rep(i, 1, m) if(w[i] && (d[a[i]] + d[b[i]]) % 2 == 0) {
        if(!lca[a[i]][b[i]]) swap(a[i], b[i]);
        id[lca[a[i]][b[i]]].pb(i);
    }
    Dfs(1);
    cout << su - f[1][1];
    return 0;
}