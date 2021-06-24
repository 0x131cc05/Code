#include <bits/stdc++.h>
using namespace std;
 
const int N = 200010;
 
typedef long long LL;
 
struct edge {
    int to, next;
} e[N * 2];
 
int head[N], ecnt;
 
inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}
 
int dep[N], fa[N][18], dfn[N], dfsn;
 
void dfs(int u, int f) {
    fa[u][0] = f, dep[u] = dep[f] + 1, dfn[u] = ++dfsn;
    for (int i = 1; i <= 17; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u);
}
 
inline int LCA(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 17; i >= 0; i--) if (dep[fa[a][i]] >= dep[b]) a = fa[a][i];
    if (a == b) return a;
    for (int i = 17; i >= 0; i--) if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
    return fa[a][0];
}
 
inline int Dis(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[LCA(a, b)];
}
 
typedef pair<int, int> P;
 
int col[N], remain[N], s[N], mark[N]; LL turn[N];
 
vector<P> G[N]; vector<int> pool;
 
inline void adde(int from, int to, int w) {
    // cout << "adde: " << from << ' ' << to << ' ' << w << endl;
    pool.push_back(from), pool.push_back(to);
    G[from].push_back(P(to, w)), G[to].push_back(P(from, w));
}
 
inline void clear() {
    for (auto t : pool) 
        col[t] = remain[t] = turn[t] = mark[t] = 0, G[t].clear();
    pool.clear();
}
 
inline int build(vector<int> p) {
    sort(p.begin(), p.end(), [](int a, int b) { return dfn[a] < dfn[b]; });
    p.resize(unique(p.begin(), p.end()) - p.begin()); 
    static int stk[N]; int top = 0, lca;
    for (auto v : p) {
        if ((!top) || (lca = LCA(v, stk[top])) == stk[top]) { stk[++top] = v; continue; }
        while (top >= 2 && dep[stk[top - 1]] >= dep[lca]) 
            adde(stk[top], stk[top - 1], dep[stk[top]] - dep[stk[top - 1]]), top--;
        if (stk[top] != lca) adde(stk[top], lca, dep[stk[top]] - dep[lca]), stk[top] = lca;
        stk[++top] = v;
    }
    for (int i = 1; i < top; i++) adde(stk[i], stk[i + 1], dep[stk[i + 1]] - dep[stk[i]]);
    return stk[1];
}
 
int k;
 
inline int get(int r, int v, int d) {
    if (d <= r) return 0;
    return (d - r + v - 1) / v;
}
 
void up(int u, int f) {
    for (auto v : G[u]) if (v.first != f) {
        up(v.first, u);
        if ((!col[v.first]) || mark[u]) continue;
        int t = get(remain[v.first], s[col[v.first]], v.second); LL nxt = (LL)t * k + turn[v.first];
        if ((!col[u]) || nxt < turn[u]) 
            turn[u] = nxt, col[u] = col[v.first], remain[u] = remain[v.first] + (LL)t * s[col[v.first]] - v.second;
    }
}
 
void down(int u, int f) {
    assert(col[u]);
    for (auto v : G[u]) if (v.first != f) {
        int t = get(remain[u], s[col[u]], v.second); LL nxt = t * k + turn[u];
        if ((!mark[v.first]) && (turn[v.first] > nxt || !col[v.first]))
            turn[v.first] = nxt, col[v.first] = col[u], remain[v.first] = remain[u] + (LL)t * s[col[u]] - v.second;
        down(v.first, u);
    }
}
 
int main() {
    int n; scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), adde(a, b);
    int q; scanf("%d", &q), dfs(1, 0);
    while (q--) {
        vector<int> tmp = {1}, ask;
        int m; scanf("%d%d", &k, &m);
        for (int i = 1; i <= k; i++) {
            int a; scanf("%d%d", &a, &s[i]), tmp.push_back(a);
            col[a] = turn[a] = i, remain[a] = s[i], mark[a] = 1;
        }
        for (int i = 1; i <= m; i++) {
            int a; scanf("%d", &a), ask.push_back(a), tmp.push_back(a);
        }
        if (n <= 10) {
            for (int i = 1; i <= n; i++) {
                pool.push_back(i);
                for (int j = head[i]; j; j = e[j].next)
                    if (i < e[j].to) adde(i, e[j].to, 1); 
            }
        } else build(tmp);
        up(1, 0), down(1, 0);
        for (auto t : ask) printf("%d ", col[t]);
        clear(), puts("");
    }
    return 0;
}
