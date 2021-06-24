#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int M = 200010;

struct edge {
    int to, next;
} e[M];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int BFS(int u) {
    static int vis[N]; memset(vis, 0, sizeof(vis)), vis[u] = 1; 
    queue<int> q; q.push(u);
    int res = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next)
            if (!vis[e[i].to]) {
                vis[e[i].to] = vis[u] + 1, q.push(e[i].to);
                if (vis[e[i].to] > res) res = vis[e[i].to];
            }
    }
    return res - 1;
}

int fa[N], ans[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int col[N];

void dfs(int u, int c) {
    col[u] = c;
    for (int i = head[u]; i; i = e[i].next)
        if (!col[e[i].to]) dfs(e[i].to, 3 - c);
        else if (col[e[i].to] == col[u]) puts("-1"), exit(0);
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b), adde(a, b), fa[find(a)] = find(b);
    }
    for (int i = 1; i <= n; i++) if (!col[i]) dfs(i, 1);
    for (int i = 1; i <= n; i++) {
        int rt = find(i);
        ans[rt] = max(ans[rt], BFS(i));
    }
    int res = 0;
    for (int i = 1; i <= n; i++) res += ans[i];
    printf("%d\n", res);
}