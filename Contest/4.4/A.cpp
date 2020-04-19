#include <bits/stdc++.h>
using namespace std;

const int N = 5010;

int mod;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

int frac[N], inv[N], C[N][N];

int res = 1, n;

void dfs(int u, int f, int fuck) {
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u, e[i].w);
    static int F[N]; memset(F, 0, sizeof(F)), F[u != 1] = 1;
    int t = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            int v = e[i].w / 2; static int G[N];
            for (int j = 0; j <= t + v; j++) G[j] = 0;
            for (int j = 0; j <= t; j++) 
                for (int k = 1; k <= v; k++) {
                    int tmp = (LL)F[j] * C[v - 1][k - 1] % mod * inv[k] % mod;
                    if ((v - k) & 1) G[j + k] = (G[j + k] + mod - tmp) % mod;
                    else G[j + k] = (G[j + k] + tmp) % mod;
                }
            for (int j = 0; j <= t + v; j++) F[j] = G[j];
            t += v;
        }
    int ans = 0;
    for (int i = fuck / 2; i <= t; i++) 
        ans = (ans + (LL)C[i - 1][fuck / 2 - 1] * frac[i] % mod * F[i]) % mod;
    res = (LL)res * ans % mod;
}

int main() {
    scanf("%d%d", &n, &mod), frac[0] = inv[0] = 1;
    for (int i = 1, a, b, c; i < n; i++) scanf("%d%d%d", &a, &b, &c), adde(a, b, c);
    for (int i = 1; i <= n + 1; i++) {
        frac[i] = (LL)frac[i - 1] * i % mod;
        inv[i] = Pow(frac[i], mod - 2);
    }
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            if (C[i][j] >= mod) C[i][j] -= mod;
        }
    }   
    dfs(1, 0, 2), printf("%lld\n", (LL)res * n % mod);
    return 0;
}
