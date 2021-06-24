#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

int sz[N], bl[N], dep[N];

void dfs(int u, int f, int t) {
    bl[u] = t, sz[u] = 1, dep[u] = dep[f] + 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u, t), sz[u] += sz[e[i].to];
}

int frac[N], inv[N], ans[N], pw[N];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int main() {
    // freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m), pw[0] = 1;
    for (int i = 1; i <= n; i++) pw[i] = (LL)pw[i - 1] * (m + 1) % mod;
    bool flag = true;
    for (int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b), adde(a, b);
        if (a != b - 1) flag = false;
    }
    frac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 1; i <= n; i++) {
        dep[i] = 0;
        for (int j = head[i]; j; j = e[j].next)
            dfs(e[j].to, i, e[j].to);
        for (int j = 1; j <= i; j++) {
            int w = (LL)(C(sz[j] + n - sz[bl[j]], sz[j]) - 1) * pw[n - 1 - dep[j]] % mod;
            if (dep[j] == 1) cout << sz[j] << ' ' << n - sz[bl[j]] << endl;
            Inc(ans[dep[j]], w);
        }
    }
    ans[0] = (LL)601 * pw[n - 1] % mod;
    // ans[0] = (LL)n * (Pow(2, n) - 1) % mod * pw[n - 1] % mod;
    cout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << endl;
    int res = 0;
    for (int i = 1; i < n; i++) {
        int w = 1;
        if (i > 1) w = (w - 2 * (m + 1)) % mod;
        if (i > 2) w = (w + (LL)(m + 1) * (m + 1)) % mod;
        res = (res + (LL)w * ans[i]) % mod;
    }
    printf("%d\n", (res + mod) % mod);
}