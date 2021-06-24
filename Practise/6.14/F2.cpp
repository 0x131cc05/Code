#include <bits/stdc++.h>
using namespace std;

const int N = 400010;

typedef pair<int, int> P;

vector<int> G[N], G1[N];

int scc[N], tot, dfn[N], low[N], dfsn, vis[N], stk[N], top;

void tarjan(int u) {
    dfn[u] = low[u] = ++dfsn, vis[u] = 1, stk[++top] = u;
    for (auto v : G[u]) 
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (vis[v]) low[u] = min(low[u], dfn[v]);
    if (low[u] >= dfn[u]) {
        tot++;
        while (233) {
            int v = stk[top--];
            vis[v] = 0, scc[v] = tot;
            if (u == v) break;
        }
    } 
}

int l[N], r[N], id[N], mark[N];

int n, m;

int ID(int x, int y) {
    return (x - 1) * m + y;
}

vector<string> mp;

int nxt[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

set<int> s[N];

int main() {
    scanf("%d%d", &n, &m), mp.resize(n + 1);
    for (int i = 1; i <= n; i++) 
        mp[i].resize(m + 2), scanf("%s", &mp[i][1]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) if (mp[i][j] == '#') s[j].insert(i);
    for (int i = 1; i <= m; i++) {
        int lst = 0;
        for (int j = n; j >= 1; j--) if (mp[j][i] == '#') {
            if (lst) G[ID(j, i)].push_back(ID(lst, i));
            id[ID(j, i)] = i;
            if (j != 1 && mp[j - 1][i] == '#') G[ID(j, i)].push_back(ID(j - 1, i));
            lst = j;
            if (i != 1) {
                auto a = s[i - 1].lower_bound(j);
                if (a != s[i - 1].end()) G[ID(j, i)].push_back(ID(*a, i - 1));
            }
            if (i != m) {
                auto a = s[i + 1].lower_bound(j);
                if (a != s[i + 1].end()) G[ID(j, i)].push_back(ID(*a, i + 1));
            }
        }
    }
        
    for (int i = 1; i <= n * m; i++) 
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n * m; i++)
        for (auto j : G[i]) 
            if (scc[i] != scc[j]) 
                G1[scc[j]].push_back(scc[i]);
    for (int i = 1; i <= tot; i++) l[i] = m, r[i] = 1;
    for (int i = 1; i <= n * m; i++) {
        int t = id[i], cur = scc[i];
        l[cur] = min(l[cur], t), r[cur] = max(r[cur], t);
    }
    for (int i = 1; i <= m; i++) {
        int a; scanf("%d", &a);
        for (int j = n, ct = 0; j >= 1; j--) if (mp[j][i] == '#') {
            if (++ct == a) {
                mark[scc[ID(j, i)]] = 1;
                break;
            }
        }
    }
    vector<P> vec;
    for (int i = tot; i >= 1; i--) {
        for (auto v : G1[i]) {
            l[i] = min(l[i], l[v]), r[i] = max(r[i], r[v]);
        }
        if (mark[i]) vec.push_back(P(l[i], r[i]));
    }
    sort(vec.begin(), vec.end(), [&](P a, P b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second < b.second;
    });
    int r = 0, res = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].first <= r) continue;
        else r = vec[i].second, res++;
    }   
    printf("%d\n", res);
}