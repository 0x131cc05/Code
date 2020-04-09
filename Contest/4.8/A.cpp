#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int frac[510], inv[510];

inline int C(int n, int r) {
    if (r < 0 || r > n) return 0;
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

LL dis[N]; int dep[N], fa[N][17], res, sz[N];

int mark[N], n, m, k;

void dfs(int u, int f, int w) {
    dep[u] = dep[f] + 1, dis[u] = dis[f] + w, fa[u][0] = f;
    for (int i = 1; i < 17; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    sz[u] = mark[u];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) 
            dfs(e[i].to, u, e[i].w), sz[u] += sz[e[i].to];
    int t = C(m, k) - C(sz[u], k) - C(m - sz[u], k); t = (t % mod + mod) % mod;
    res = (res + (LL)t * w * 2) % mod;
}

inline int LCA(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 16; i >= 0; i--) if (dep[fa[a][i]] >= dep[b]) a = fa[a][i];
    if (a == b) return a;
    for (int i = 16; i >= 0; i--) if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
    return fa[a][0];
}

inline LL Dis(int a, int b) {
    return dis[a] + dis[b] - 2 * dis[LCA(a, b)];
}

LL G[510][510]; int pos[510]; 

int main() {
    scanf("%d%d%d", &n, &m, &k), frac[0] = inv[0] = 1;
    for (int i = 1; i <= m; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 1; i <= m; i++) scanf("%d", &pos[i]), mark[pos[i]] = 1;
    for (int i = 1, a, b, c; i < n; i++) 
        scanf("%d%d%d", &a, &b, &c), adde(a, b, c);
    dfs(1, 0, 0);
    for (int i = 1; i <= m; i++)
        for (int j = i + 1; j <= m; j++) 
            G[i][j] = G[j][i] = Dis(pos[i], pos[j]);
    for (int i = 1; i <= m; i++)
        for (int j = i + 1; j <= m; j++) {
            LL tmp = G[i][j]; int tot = 0;
            for (int k = 1; k <= m; k++) if (k != i && k != j) {
                LL a = G[k][i], b = G[k][j];
                if (a < tmp && b < tmp) { tot++; continue; } 
                if (a > tmp || b > tmp) continue;
                if (a == tmp && k < j) continue;
                if (b == tmp && k < i) continue;
                tot++;
            }
            res = (res - tmp % mod * C(tot, k - 2)) % mod;
        }
    res = (LL)(res + mod) * Pow(C(m, k), mod - 2) % mod;
    printf("%d\n", res);
    return 0;
}
