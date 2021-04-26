#include <bits/stdc++.h>
using namespace std;

const int N = 300010;

typedef pair<int, int> P;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt; 
}

int dfn[N], dfsn, dep[N], fa[20][N];

void dfs(int u, int f) {
    dfn[u] = ++dfsn, dep[u] = dep[f] + 1, fa[0][u] = f;
    for (int i = 1; i < 20; i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u);
}

int LCA(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 19; i >= 0; i--) if (dep[fa[i][a]] >= dep[b]) a = fa[i][a];
    if (a == b) return a;
    for (int i = 19; i >= 0; i--) if (fa[i][a] != fa[i][b]) a = fa[i][a], b = fa[i][b];
    return fa[0][a];
}

int dis(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[LCA(a, b)];
}

int main() {
    int n; scanf("%d", &n), n++;
    for (int i = 2, a; i <= n; i++) scanf("%d", &a), adde(a, i);
    dfs(1, 0); int t1 = 1, t2 = 1, d = 0;
    set<P> s; s.insert(P(dfn[1], 1));
    for (int i = 2; i <= n; i++) {
        int A = dis(t1, i), B = dis(t2, i);
        if (max(A, B) > d) {
            d = max(A, B), t1 = d == A ? t1 : t2, t2 = i;
            P nw(dfn[i], i);
            while (233) {
                auto pre = s.lower_bound(nw), suf = s.upper_bound(nw); int a, b;
                if (pre == s.begin()) a = s.rbegin() -> second;
                else a = (--pre) -> second;
                b = suf == s.end() ? s.begin() -> second : suf -> second;
                if (dis(a, i) < d) s.erase(P(dfn[a], a));
                else if (dis(i, b) < d) s.erase(P(dfn[b], b));
                else break;
            }
        } 
        if (max(A, B) >= d) s.insert(P(dfn[i], i));
        printf("%d\n", s.size());
    }
}

