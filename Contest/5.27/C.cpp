#include <bits/stdc++.h>
using namespace std;

const int N = 10010;

typedef pair<int, int> P;

vector<P> G[N]; int id[21][N], tot[21];

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt = 1, ncnt;

inline void adde(int from, int to, int w) {
//    cout << "adde: " << from << ' ' << to << ' ' << w << endl;
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

void build(int u, int f) {
    int last = u, t = 0;
    for (auto v : G[u]) if (v.first != f) t = v.first;
    for (auto v : G[u]) if (v.first != f) {
        build(v.first, u), adde(last, v.first, v.second);
        if (v.first != t) adde(last, ++ncnt, 0), last = ncnt;
    }
}

int mark[N], sz[N];

int tmp, cur;

void GetEG(int u, int f, int tot) {
    sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !mark[i]) {
            GetEG(e[i].to, u, tot), sz[u] += sz[e[i].to];
            if (abs(tot - 2 * sz[e[i].to]) < tmp) 
                tmp = abs(tot - 2 * sz[e[i].to]), cur = i;
        } 
}

int layer, t, p[21][N], mx;

void dfs(int u, int f, int dis, int sgn) {
    id[layer][u] = t, p[layer][u] = sgn * dis, sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !mark[i]) 
            dfs(e[i].to, u, dis + e[i].w, sgn), sz[u] += sz[e[i].to];
}

void Divide(int dep, int ed) {
    t = ++tot[dep], layer = dep, mark[ed] = mark[ed ^ 1] = 1, mx = max(mx, dep);
    dfs(e[ed].to, 0, 0, 1), dfs(e[ed ^ 1].to, 0, e[ed].w, -1);
    auto find = [&](int u) -> int {
        cur = -1, tmp = 1e9, GetEG(u, 0, sz[u]);
        return cur;
    };
    int L = find(e[ed].to), R = find(e[ed ^ 1].to);
    if (~L) Divide(dep + 1, L); if (~R) Divide(dep + 1, R);
}

void dfs1(int layer, int u, int f, int diff) {
    p[layer][u] += diff;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            if (id[layer][e[i].to] != id[layer][u]) dfs1(layer, e[i].to, u, p[layer][u] + e[i].w - p[layer][e[i].to]);
            else dfs1(layer, e[i].to, u, diff);
        }
}

int n;

inline void Divide() {
    ncnt = n, build(1, 0), tmp = 1e9, GetEG(1, 0, n), Divide(1, cur);
}

int main() {
    scanf("%d", &n);
    for (int i = 1, a, b, c; i < n; i++)
        scanf("%d%d%d", &a, &b, &c), G[a].push_back(P(b, c)), G[b].push_back(P(a, c));
    Divide();
    for (int i = 1; i <= mx; i++) dfs1(i, 1, 0, 0);
    printf("%d\n", mx);
    for (int i = 1; i <= n; i++, puts("")) 
        for (int j = 1; j <= mx; j++) printf("%d ", p[j][i]);
}
