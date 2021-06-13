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

int frac[N], inv[N], ans[N];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int main() {
    // freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    bool flag = true;
    for (int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b), adde(a, b);
        if (a != b - 1) flag = false;
    }
    if (flag) {
        int cur = 1;
        for (int i = n - 1; i >= 0; i--) ans[i] = cur, cur = cur * 2 % mod;
    } else {
        frac[0] = inv[0] = 1;
        for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
        for (int i = 1; i <= n; i++) {
            dep[i] = 0;
            for (int j = head[i]; j; j = e[j].next)
                dfs(e[j].to, i, e[j].to);
            for (int j = 1; j < i; j++) 
                Inc(ans[dep[j]], C(sz[j] + n - sz[bl[j]], sz[j]) - 1);
        }
        int A = 0, B = 0;
        for (int i = n - 1; i >= 1; i--) {
            ans[i] = (ans[i] - A + (LL)(i - 1) * B) % mod;
            if (ans[i] < 0) ans[i] += mod;
            A = (A + (LL)i * ans[i]) % mod;
            B = (B + ans[i]) % mod;
        }
        int tot = Pow(2, n) - 1;
        for (int i = 1; i < n; i++) {
            tot -= ans[i];
            if (tot < 0) tot += mod;
        }
        ans[0] = tot;
        cout << tot << endl;
    }
    int res = 0;
    // for (int i = 0; i < n; i++) printf("%d ", ans[i]);
    // puts("");
    for (int i = 0; i < n; i++) {
        res = (res + (LL)ans[i] * Pow(m + 1, n - 1 - i)) % mod;
    }
    printf("%d\n", res + 1);
}