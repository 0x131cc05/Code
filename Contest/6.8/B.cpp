#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int frac[N], inv[N];

inline int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int dp[N][N];

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt, sz[N];

inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

void dfs(int u, int f) {
    dp[u][1] = sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u);
//            cout << "after: " << u << ' ' << e[i].to << endl;
            for (int j = sz[u]; j >= 1; j--)
                for (int k = 1; k <= sz[e[i].to]; k++) {
                    dp[u][j + k] = (dp[u][j + k] + (LL)dp[u][j] * dp[e[i].to][k]) % mod;
//                    cout << u << ' ' << i << ' ' << j << ' ' << dp[u][i + j] << endl;
                }
                    
            sz[u] += sz[e[i].to];
        }
}

int main() {
    int n; LL s; scanf("%d%lld", &n, &s), frac[0] = inv[0] = 1, s %= mod;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 1, a, b; i < n; i++)
        scanf("%d%d", &a, &b), adde(a, b);
    dfs(1, 0); int res = 0;
    for (int i = 1, tmp = 1; i <= n; tmp = (LL)tmp * (s + i) % mod, i++) 
        res = (res + (LL)dp[1][i] * tmp % mod * inv[i - 1]) % mod;
    printf("%d\n", res);
}
