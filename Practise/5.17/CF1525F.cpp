#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int M = N * N;

typedef long long LL;

int n, m, fuck[N];

struct edge {
    int to, next, w;
} e[M * 2];

int head[N], ecnt;

void adde(int from, int to, int w) {
    e[++ecnt] = { to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = { from, head[to], 0 }, head[to] = ecnt;
}

int dep[N];

bool BFS(int s, int t) {
    memset(dep, -1, sizeof(dep)), dep[s] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next)
            if (dep[e[i].to] == -1 && e[i].w) {
                dep[e[i].to] = dep[u] + 1, q.push(e[i].to);
                if (e[i].to == t) return true;
            }
    }
    return false;
}

int cur[N];

int DFS(int u, int f, int t) {
    if (u == t || !f) return f;
    int res = 0;
    for (int &i = cur[u], tmp; i; i = e[i].next)
        if (e[i].w && dep[e[i].to] == dep[u] + 1 && (tmp = DFS(e[i].to, min(f, e[i].w), t))) {
            res += tmp, f -= tmp, e[i].w -= tmp, e[i ^ 1].w += tmp;
            if (!f) break;
        }
    return res;
}

int dinic(int s, int t) {
    int res = 0;
    while (BFS(s, t)) memcpy(cur, head, sizeof(cur)), res += DFS(s, 1e9, t);
    return res;
}

int from[M], to[M];

int run() {
    memset(head, 0, sizeof(head)), ecnt = 1;
    int s = n * 2 + 1, t = s + 1;
    for (int i = 1; i <= n; i++) if (!fuck[i]) adde(s, i, 1);
    for (int i = n + 1; i <= 2 * n; i++) if (!fuck[i]) adde(i, t, 1);
    for (int i = 1; i <= m; i++) 
        adde(from[i], n + to[i], 1);
    return dinic(s, t);
}

LL dp[N][N]; int lst[N][N], ct[N];

int main() {
    int k; scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) 
        scanf("%d%d", &from[i], &to[i]);
    int match = run(); 
    memset(dp, -0x3f, sizeof(dp)), dp[0][match] = 0;
    for (int i = 1; i <= k; i++) {
        int x, y; scanf("%d%d", &x, &y);
        for (int j = 0; j <= match; j++)
            for (int k = 0; k <= j; k++) {
                int w = max(0ll, x - (LL)(j - k) * y);
                if (n - k <= i) w = 0;
                if (dp[i - 1][j] + w > dp[i][k]) 
                    dp[i][k] = dp[i - 1][j] + w, lst[i][k] = j;
            } 
    }
    int cur = 0;
    for (int i = 1; i <= match; i++) if (dp[k][i] > dp[k][cur]) cur = i;
    for (int i = k; i >= 1; i--) 
        ct[i] = lst[i][cur] - cur, cur = lst[i][cur];
    vector<int> res;
    for (int i = 1, nw = match; i <= k; i++) {
        for (int j = 1; j <= ct[i]; j++) {
            for (int k = 1; k <= n * 2; k++) if (!fuck[k]) {
                fuck[k] = 1;
                if (run() == nw - 1) { nw--, res.push_back(k <= n ? k : -(k - n)); break; }
                fuck[k] = 0;
            }
        }
        res.push_back(0);
    }
    printf("%d\n", res.size());
    for (auto t : res) printf("%d ", t);
}