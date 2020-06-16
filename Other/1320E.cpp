#include <bits/stdc++.h>
using namespace std;

const int N = 60;

int n, rt;

namespace WEN {

vector<int> G[N]; int ind[N];

inline void adde(int from, int to) {
//    cout << "adde: " << from << ' ' << to << endl;
    ind[to]++, G[from].push_back(to);
}

inline bool check() {
    queue<int> q; int tot = 0;
    for (int i = 1; i <= n; i++) if (!ind[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop(); tot++;
        for (auto v : G[u])
            if (!--ind[v]) q.push(v);
    }
    for (int i = 1; i <= n; i++) G[i].clear(), ind[i] = 0;
    return tot == n;
}

}

vector<int> G1[N], G2[N]; int G[N][N], mark[N], tot, fuck[N][N];

void dfs(int u, int f, int ok) {
    if (ok) mark[u] = 1, tot++;
    else if (!mark[f]) WEN::adde(u, f);
    for (auto v : G1[u]) if (v != f) 
        dfs(v, u, ok & G[u][v]);
}

void dfs1(int u, int f) {
    if (!mark[u] && !mark[f]) WEN::adde(f, u);
    mark[u] = 0;
    for (auto v : G2[u]) if (v != f) dfs1(v, u);
}

inline void erase(vector<int> &t, int a) {
    for (auto &v : t) if (v == a) {
        swap(v, t.back()), t.pop_back(); return;
    }
    assert(0);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int res = 1e9; scanf("%d", &n);
        memset(G, 0, sizeof(G)), memset(fuck, 0, sizeof(fuck));
        for (int i = 1; i <= n; i++) G1[i].clear(), G2[i].clear();
        for (int i = 1, a, b; i < n; i++)
            scanf("%d%d", &a, &b), G1[a].push_back(b), G1[b].push_back(a), fuck[a][b] = fuck[b][a] = 1;
        for (int i = 1, a, b; i < n; i++)
            scanf("%d%d", &a, &b), G2[a].push_back(b), G2[b].push_back(a), G[a][b] = G[b][a] = 1;
        for (int i = 1; i <= n; i++) if (G1[i].size() == 1)
            for (int j = 1; j <= n; j++) if (j != i) {
                int v = G1[i].back(); G1[i].pop_back(), erase(G1[v], i);
                G1[i].push_back(j), G1[j].push_back(i), tot = 0;
                rt = i, dfs(i, 0, 1), dfs1(i, 0);
                G1[i].pop_back(), G1[i].push_back(v), G1[j].pop_back(), G1[v].push_back(i);
                if (WEN::check()) res = min(res, n - tot + !fuck[i][j]);
//                cout << "check: " << i << ' ' << j << ' ' << res << endl;
            }
        if (res <= n) printf("%d\n", res);
        else puts("-1");
    }
}
