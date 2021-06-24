#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

typedef long long LL;

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to, int w) {
    e[++ecnt] = { to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = { from, head[to], w }, head[to] = ecnt;
}

vector<LL> cir, dis; int vis[N];

bool dfs(int u, int f, int t) {
    if (u == t) return cir.push_back(t), true;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && dfs(e[i].to, u, t)) 
            return cir.push_back(u), dis.push_back(e[i].w), true;
    return false;
}

LL mx; int p;

void dfs1(int u, int f, LL d) {
    if (d >= mx) mx = d, p = u;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !vis[e[i].to]) dfs1(e[i].to, u, d + e[i].w);
}

int fa[N], A[N], B[N], fk[N], pos[N]; LL maxlen[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) {
        int a, b; scanf("%d%d", &a, &b), A[i] = a, B[i] = b;
        if (find(i) == find(a)) fk[i] = 1;
        else fa[find(i)] = find(a), adde(i, a, b);
    }
    for (int i = 1; i <= n; i++) if (fk[i])
        pos[find(A[i])] = i;
    LL res = 0;
    for (int i = 1; i <= n; i++) if (fa[i] == i) {
        mx = 0, dfs1(i, 0, 0);
        mx = 0, dfs1(p, 0, 0);
        if (!pos) { res += mx; continue; }
        LL tmp = mx; int u = pos[i], v = A[pos[i]], w = B[pos[i]];
        cir.clear(), dis.clear(), dfs(u, 0, v);
        // for (auto t : cir) cout << t << ' ';
        // cout << endl;
        for (int i = 1; i < dis.size(); i++) dis[i] += dis[i - 1];
        LL all = dis.back();
        for (auto t : cir) vis[t] = 1;
        for (auto t : cir) {
            mx = 0, dfs1(t, 0, 0), maxlen[t] = mx;
        }
        LL wkr = 0;
        for (int i = 0; i + 1 < cir.size(); i++) {
            wkr = max(wkr, (i ? dis[i - 1] : 0) + maxlen[cir[i]]);
            LL hh = wkr + all - dis[i] + w + maxlen[cir[i + 1]];
            tmp = max(tmp, hh);
        }
        res += tmp;
    }
    printf("%lld\n", res);
}