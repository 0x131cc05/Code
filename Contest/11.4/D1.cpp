#include <bits/stdc++.h>
using namespace std;

const int N = 600010;
const int M = 900010;

struct edge {
    int to, next, id;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to, int id) {
    e[++ecnt] = { to, head[from], id }, head[from] = ecnt;
    e[++ecnt] = { from, head[to], id }, head[to] = ecnt;
}

int ind[N], flip[M], from[M], to[M];

template<class T> void read(T &x) {
    x = 0; char c = getchar(); bool flag = false;
    while (!isdigit(c)) flag |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (flag) x = -x;
}

template<class T, typename... Tail> void read(T &x, Tail&... tail) {
   read(x), read(tail...);
}

int fa[N], n, ed[N], fuck[M], F[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int top[M]; vector<int> G[M];

void dfs(int u, int f) {
    F[u] = f;
    if (f) {
        top[ed[u]] = ed[f];
        while (top[ed[u]] > ed[u]) top[ed[u]] = top[top[ed[u]]];
        G[top[ed[u]]].push_back(ed[u]);
    }
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            ed[e[i].to] = e[i].id, fuck[e[i].id] = e[i].to, dfs(e[i].to, u);
            if (flip[e[i].id]) ind[u] ^= 1;
        }
    if (f && !ind[u]) ind[u] ^= 1, flip[ed[u]] = 1; 
}

int main() {
    freopen("in.in", "r", stdin);
    int m; read(n, m);
    for (int i = 1; i <= m; i++) 
        read(from[i], to[i]), from[i]++, to[i]++, ind[from[i]] ^= 1, ind[to[i]] ^= 1;
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = m; i >= 1; i--) {
        int u = from[i], v = to[i];
        if (find(u) != find(v)) 
            adde(u, v, i), fa[find(u)] = find(v);
    }
    dfs(1, 0);
    if (n % 2 == 1) {
        set<int> s; int pos = 0;
        while (233) {
            int nxt = 1e9;
            for (auto v : G[pos]) if (flip[v]) 
                nxt = min(nxt, v);
            if (nxt > 1e8) break;
            pos = nxt;
        }
        pos = fuck[pos];
        while (pos) {
            flip[ed[pos]] ^= 1;
            pos = F[pos];
        }
    }
    for (int i = 1; i <= m; i++) putchar('0' + (flip[i] ^ 1));
}