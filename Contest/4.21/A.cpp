#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 998244353;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

vector<int> son[N]; int dep[N], mx;

void dfs(int u, int f) {
    dep[u] = dep[f] + 1, mx = max(mx, dep[u]);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u);
            for (auto v : son[e[i].to]) son[u].push_back(v);
            son[u].push_back(e[i].to);
        } 
}

typedef long long LL;

int w[N], frac[N], inv[N];

inline int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int num[N], tmp[N];

int main() {
    int n; scanf("%d", &n), frac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 1, a, b; i < n; i++)
        scanf("%d%d", &a, &b), adde(a, b);
    dfs(1, 0);
    for (int i = 1; i <= mx; i++) 
        for (int j = 1; j <= i; j++) 
            w[i] = (w[i] + (LL)C(i - 1, j - 1) * frac[i] % mod * inv[j]) % mod;
    int ans = 0;
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    for (int i = 0; i <= n; i++) tmp[i] = C(n, i);
    for (int i = 1; i <= n; i++) {
        int res = frac[n] * 2; 
        for (auto v : son[i]) {
            int t = dep[v] - dep[i];
            res = (res + (LL)w[t + 1] * tmp[t + 1] % mod * frac[n - t - 1]) % mod;
        }
        ans = (ans + (LL)res * num[i]) % mod;
    }
    printf("%d\n", ans);
    return 0;
}