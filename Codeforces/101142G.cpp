#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

int fa[18][N], dfn[N], ed[N], rk[N], dfsn, dep[N];

void dfs(int u, int f) {
    fa[0][u] = f, dfn[u] = ++dfsn, dep[u] = dep[f] + 1, rk[dfsn] = u;
    for (int i = 1; i <= 17; i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u);
    ed[u] = dfsn;
}

int LCA(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 17; i >= 0; i--) if (dep[fa[i][a]] >= dep[b]) a = fa[i][a];
    if (a == b) return a;
    for (int i = 17; i >= 0; i--) if (fa[i][a] != fa[i][b]) a = fa[i][a], b = fa[i][b];
    return fa[0][a];
}

int jump(int a) {
    for (int i = 17; i >= 0; i--) if (fa[i][a] > 1) a = fa[i][a];
    return a;
}

set<int> s[N];

int pre[N], belong[N], lca[N];

int get(int l, int r) {
    return pre[r] - pre[l - 1];
}

int main() {
    freopen("gangsters.in", "r", stdin), freopen("gangsters.out", "w", stdout);
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 2, a; i <= n; i++) scanf("%d", &a), adde(a, i);
    dfs(1, 0);
    for (int i = 1; i <= n; i++) 
        pre[i] = pre[i - 1] + (dfn[rk[i]] == ed[rk[i]]), belong[i] = jump(i);
    int A = 0, B = 0, tot = 0;
    while (q--) {
        char op[5]; int u; scanf("%s%d", op + 1, &u);
        int top = belong[u];
        if (op[1] == '+') {
            if (lca[top]) B -= get(dfn[lca[top]], ed[lca[top]]);
            else A++;
            // cout << dfn[u] << endl;
            s[top].insert(dfn[u]), lca[top] = LCA(rk[*s[top].begin()], rk[*s[top].rbegin()]);
            // cout << *s[top].begin() << ' ' << *s[top].rend() << endl;
            // cout << lca[top] << endl;
            B += get(dfn[lca[top]], ed[lca[top]]), tot++;
        } else {
            B -= get(dfn[lca[top]], ed[lca[top]]);
            if (s[top].size() == 1) A--;
            s[top].erase(dfn[u]), tot--;
            if (s[top].empty()) lca[top] = 0;
            else {
                lca[top] = LCA(rk[*s[top].begin()], rk[*s[top].rbegin()]);
                B += get(dfn[lca[top]], ed[lca[top]]);
            }
        }
        printf("%d %d\n", A, B - tot);
    }
    return 0;
}