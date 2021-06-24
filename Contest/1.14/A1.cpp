#include <bits/stdc++.h>
using namespace std;

const int N = 30010;
const int M = 1000010;

typedef pair<int, int> P;

struct edge {
    int to, next, w;
} e[M];

int head[N], ecnt = 1;

void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], 0 }, head[to] = ecnt;
}

int dep[N], cur[N];

bool BFS(int s, int t) {
    memset(dep, -1, sizeof(dep)), dep[s] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next)
            if (e[i].w && dep[e[i].to] == -1) {
                dep[e[i].to] = dep[u] + 1;
                if (e[i].to == t) return true;
                q.push(e[i].to);
            }
    }
    return false;
}

int DFS(int u, int f, int t) {
    if (u == t || !f) return f;
    int res = 0, tmp;
    for (int &i = cur[u]; i; i = e[i].next)
        if (e[i].w && dep[e[i].to] == dep[u] + 1 && (tmp = DFS(e[i].to, min(f, e[i].w), t))) {
            res += tmp, f -= tmp, e[i].w -= tmp, e[i ^ 1].w += tmp;
            if (!f) break;
        }
    return res;
}

int dinic(int s, int t) {
    int res = 0;
    while (BFS(s, t)) memcpy(cur, head, sizeof(head)), res += DFS(s, 1e9, t);
    return res;
}

int n;

void dfs(int u, int id, int t, vector<int> &v) {
    if (u <= n) v.push_back(u);
    if (u == t) return;
    for (int i = head[u]; i; i = e[i].next)
        if (i % 2 == 0 && !e[i].w) { 
            dfs(e[i].to, id, t, v); break; 
        }
}

vector<int> p[4], q[3];
set<P> E;

vector<int> G[N], ans;

int vis[N], A, B, C;

void dfs(int u, int f) {
    if (vis[B] && !vis[C]) return;
    vis[u] = 1, ans.push_back(u);
    for (auto v : G[u]) if (v != f) {
        if (v == A) {
            if (vis[B] && vis[C]) {
                printf("%d\n", ans.size());
                copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
                printf("%d\n", A), exit(0);
            }
            continue;
        }
        if (!vis[v]) dfs(v, u);
    }
    vis[u] = 0, ans.pop_back();
}

int main() {
    int m; scanf("%d%d", &n, &m);
    int a, b, c; scanf("%d%d%d", &a, &b, &c);
    adde(a, a + n, 3);
    for (int i = 1; i <= n; i++) if (i != a) adde(i, i + n, 1);
    for (int i = 1, a, b; i <= m; i++) 
        scanf("%d%d", &a, &b), adde(a + n, b, 1), adde(b + n, a, 1);
    int zzh = dinic(a, b);
    for (int i = head[a + n], ct = 0; i; i = e[i].next)
        if (i % 2 == 0 && !e[i].w) ct++, dfs(e[i].to, ct, b, p[ct]);
    for (int i = 1; i <= n * 2; i++)
        for (int j = head[i]; j; j = e[j].next) {
            if (j % 2 == 0) e[j].w = 1;
            else e[j].w = 0;
            if (i == c && e[j].to == c + n) e[j].w = 2;
        }
    int t = n * 2 + 1;
    adde(a + n, t, 1), adde(b + n, t, 1);
    int res = dinic(c, t);
    if (res != 2) return puts("-1"), 0;
    for (int i = head[c + n], ct = 0; i; i = e[i].next) 
        if (i % 2 == 0 && !e[i].w) ct++, dfs(e[i].to, ct, t, q[ct]);
    auto insert = [&](int u, int v) {
        if (!E.count(P(u, v))) G[u].push_back(v), G[v].push_back(u), E.insert(P(u, v)), E.insert(P(v, u));
    };
    for (int i = 1; i <= 3; i++)
        for (int j = 0; j < p[i].size(); j++) {
            int u = j ? p[i][j - 1] : a, v = p[i][j];
            insert(u, v);
        }
    for (int i = 1; i <= 2; i++)
        for (int j = 0; j < q[i].size(); j++) {
            int u = j ? q[i][j - 1] : c, v = q[i][j];
            insert(u, v);
        }
    A = a, B = b, C = c, dfs(A, 0);
    puts("-1");
}