#include <bits/stdc++.h>
using namespace std;

const int N = 800010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

vector<int> G[N];

void adde(int from, int to) {
    G[from].push_back(to), G[to].push_back(from);
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

int low[N], dfn[N], dfsn, stk[N];

void tarjan(int u, int f) {
    low[u] = dfn[u] = ++dfsn, stk[u] = 1;
    for (int i = head[u]; i; i = e[i].next) if (e[i].to != f) {
        if (!dfn[e[i].to]) tarjan(e[i].to, u), low[u] = min(low[u], low[e[i].to]);
        else if (stk[e[i].to]) low[u] = min(low[u], dfn[e[i].to]); 
    }
    stk[u] = 0;
}

vector<string> res;

void push(char s[]) {
    string tmp = ""; int t = strlen(s);
    for (int i = 0; i < t; i++) tmp += s[i];
    res.push_back(tmp);
}

char hh[15];

void R(int u, int a, int b) { sprintf(hh, "r %d %d %d", u, a, b), push(hh); } 
void C(int u, int a, int b) { sprintf(hh, "c %d %d %d", u, a, b), push(hh); }
void J(int u, int v) { sprintf(hh, "j %d %d", u, v), push(hh); }

int vis[N], col[N];

void dfs(int u) {
    R(u, 1, 4), vis[u] = 1;
    bool flag = false;
    sort(G[u].begin(), G[u].end(), [&](int a, int b) {
        return low[a] > low[b];
    });
    for (auto v : G[u]) if (!vis[v]) {
        dfs(v), J(u, v), C(u, 4, col[v]);
        if (low[v] < dfn[u]) flag = true;
        if (low[v] == dfn[u]) C(u, 4, 3), R(u, 3, 1);
        R(u, 2, 1);
    }
    if (low[u] == dfn[u] || flag) R(u, 4, 2), col[u] = 2;
    else R(u, 4, 3), col[u] = 3;
}

int main() {
    freopen("cactus.in", "r", stdin), freopen("cactus.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        vector<int> tmp; int k; scanf("%d", &k);
        for (int j = 0, t; j < k; j++)
            scanf("%d", &t), tmp.push_back(t);
        for (int j = 1; j < k; j++) adde(tmp[j], tmp[j - 1]); 
    }
    tarjan(1, 0), dfs(1);
    printf("%d\n", res.size());
    for (auto t : res) puts(t.c_str());
}

