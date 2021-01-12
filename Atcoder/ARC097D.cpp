#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt, dep[N], tot[N], ind[N], val[N], res;

char col[N];

inline void adde(int from, int to, int w) {
    res += w * 2;
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
    ind[from]++, ind[to]++;
} 

vector<int> G[N];

void dfs(int u, int f) {
    dep[u] = dep[f] + 1; 
    for (auto v : G[u]) if (v != f) {
        dfs(v, u), tot[u] += tot[v];
    }
}

void build(int u, int f, int t) {
    if (tot[u]) {
        if (t) adde(u, t, dep[u] - dep[t]);
        t = u;
    } 
    for (auto v : G[u]) if (v != f) 
        build(v, u, t);
}

int mx = -1, A[N], B[N];

inline void update(int u, int x) {
    if (A[u] < x) B[u] = A[u], A[u] = x;
    else if (B[u] < x) B[u] = x; 
}

void dfs1(int u, int f) {
    int t = (col[u] == 'B') ^ (ind[u] & 1);
    if (t) val[u] = -1;
    else res++, val[u] = 1;
    A[u] = B[u] = val[u];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs1(e[i].to, u);
            mx = max(mx,A[u] + A[e[i].to] + e[i].w);
            A[u] = max(A[u],A[e[i].to] + e[i].w + val[u]);
        }
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++) 
        scanf("%d%d", &a, &b), G[a].push_back(b), G[b].push_back(a);
    scanf("%s", col + 1);
    int rt = -1;
    for (int i = 1; i <= n; i++) if (col[i] == 'W') rt = i, tot[i]++;
    if (rt == -1) return puts("0"), 0;
    dfs(rt, 0), build(rt, 0, 0), dfs1(rt, 0);
    printf("%d\n", res - mx - 1);
    return 0;
}