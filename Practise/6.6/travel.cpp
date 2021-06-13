#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
const int mod = 998244353;

typedef long long LL;

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int sum[N][N];

int cir;

void add(int lx, int rx, int ly, int ry, int v) {
    if (lx < 0) lx += cir; if (rx < 0) rx += cir;
    if (ly < 0) ly += cir; if (ry < 0) ry += cir;
    if (lx > rx) { add(lx, cir - 1, ly, ry, v), add(0, rx, ly, ry, v); return; }
    if (ly > ry) { add(lx, rx, ly, cir - 1, v), add(lx, rx, 0, ry, v); return; }
    Inc(sum[lx][ly], v), Inc(sum[lx][ry + 1], mod - v), Inc(sum[rx + 1][ly], mod - v), Inc(sum[rx + 1][ry + 1], v); 
}

int dp[N][N], n, k, bl[N];

void trans1(vector<int> loop) { // a -> b
    cir = loop.size(); int id = bl[loop[0]];
    if (cir == 1) {
        if (k == 1) dp[loop[0]][loop[0]] = 0;
        return;
    }
    for (int j = 1; j <= n; j++) if (bl[j] > id) {
        static int tmp[N]; int sum = 0;
        for (int i = 0; i < cir; i++) {
            tmp[i] = dp[j][loop[i]];
            Inc(sum, dp[j][loop[i]]);
        }
        sum = (LL)sum * (k - 1) % mod;
        for (int i = 0; i < cir; i++) 
            dp[j][loop[i]] = (sum + tmp[(i + 1) % cir]) % mod;
    }
}

void trans2(vector<int> loop) { // (a, b) -> (c, d)
    cir = loop.size();
    if (cir == 1) {
        if (k == 1) dp[loop[0]][loop[0]] = 0;
        return;
    }
    for (int i = 0; i <= cir; i++)
        for (int j = 0; j <= cir; j++) sum[i][j] = 0;
    for (int i = 0; i < cir; i++)
        for (int j = 0; j < cir; j++) {
            int w = (LL)k * (k - 1) / 2 % mod, v = dp[loop[i]][loop[j]];
            if (k == 1) {
                if (i != j) add(j - 1, j - 1, i - 1, i - 1, v);
                continue;
            }
            add(0, cir - 1, 0, cir - 1, (LL)w * v % mod);
            add(i, i - 2, j, j - 2, mod - v);
            if (i != j) {
                add(i, j - 1, j, i - 1, (LL)k * v % mod);
                add(j - 1, i - 2, i - 1, j - 2, v);
            }
        }
    for (int i = 0; i < cir; i++)
        for (int j = 0; j < cir; j++) {
            if (i) Inc(sum[i][j], sum[i - 1][j]);
            if (j) Inc(sum[i][j], sum[i][j - 1]);
            if (i && j) Inc(sum[i][j], mod - sum[i - 1][j - 1]);
            dp[loop[i]][loop[j]] = sum[i][j];
        }
}

struct edge {
    int to, next;
} e[N * 4];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
}

vector<vector<int>> loop;

int dfn[N], dfsn, low[N], stk[N], top, vis[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++dfsn, vis[u] = 1, stk[++top] = u;
    for (int i = head[u]; i; i = e[i].next) 
        if (!dfn[e[i].to]) tarjan(e[i].to), low[u] = min(low[u], low[e[i].to]);
        else if (vis[e[i].to]) low[u] = min(low[u], dfn[e[i].to]);
    if (low[u] >= dfn[u]) {
        vector<int> p; int id = loop.size() + 1;
        while (233) {
            int v = stk[top--];
            p.push_back(v), vis[v] = 0, bl[v] = id;
            if (u == v) break; 
        }
        reverse(p.begin(), p.end());
        loop.push_back(p);
    }
}

int main() {
    freopen("travel.in", "r", stdin);
    int m; scanf("%d%d%d", &n, &m, &k);
    if (k == 0) return puts("0"), 0;
    for (int i = 1, a, b; i <= m; i++)
        scanf("%d%d", &a, &b), adde(a, b);
    for (int i = 1; i <= n; i++) adde(n + 1, i), adde(i, 0);
    n++, adde(n, 0), tarjan(n);
    reverse(loop.begin(), loop.end());
    dp[n][n] = 1;
    for (int i = 1; i < loop.size(); i++) {
        int cur = bl[loop[i][0]];
        for (auto u : loop[i - 1]) {
            for (int j = 1; j <= n; j++) if (dp[j][u]) {
                for (int t = head[u]; t; t = e[t].next)
                    if (bl[e[t].to] == cur) {
                        Inc(dp[j][e[t].to], dp[j][u]);
                    }
                if (bl[j] != bl[u]) for (int t = head[j]; t; t = e[t].next)
                    if (bl[e[t].to] == cur) 
                        Inc(dp[u][e[t].to], dp[j][u]);
            }
        }
        for (auto u : loop[i]) {
            for (int j = 1; j <= n; j++) if (dp[j][u] && bl[j] > bl[u]) {
                for (int t = head[j]; t; t = e[t].next)
                    if (bl[e[t].to] == cur) {
                        Inc(dp[e[t].to][u], dp[j][u]);
                    }
            }
        }
        if (loop[i][0] == 0) continue;
        trans1(loop[i]);
        trans2(loop[i]);
    }
    printf("%d\n", dp[0][0]);
}