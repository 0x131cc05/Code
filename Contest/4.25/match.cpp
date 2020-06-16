#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
const int mod = 998244353;

typedef long long LL;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){to, head[from]}, head[from] = ecnt;
    e[++ecnt] = (edge){from, head[to]}, head[to] = ecnt;
}

int dp[N][N], frac[N], a[N], b[N], sz[N], C[N / 2][N / 2], m;

char s[N];

void dfs(int u, int f) {
    dp[u][0] = 1, sz[u] = 0;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u); static int tmp[N];
            for (int j = 0; j <= sz[u] + sz[e[i].to] && j <= m; j++) tmp[j] = 0;
            for (int j = 0; j <= sz[u] && j <= m; j++) if (dp[u][j])
                for (int k = 0; k <= sz[e[i].to] && j + k <= m; k++) if (dp[e[i].to][k]) 
                    tmp[j + k] = (tmp[j + k] + (LL)dp[u][j] * dp[e[i].to][k]) % mod;
            for (int j = 0; j <= sz[u] + sz[e[i].to] && j <= m; j++) dp[u][j] = tmp[j];
            sz[u] += sz[e[i].to], a[u] += a[e[i].to], b[u] += b[e[i].to];
        }
    sz[u]++;
    int remain = s[u] == '1' ? b[u] : a[u];
    for (int i = remain - 1; i >= 0; i--) 
        dp[u][i + 1] = (dp[u][i + 1] + (LL)dp[u][i] * (remain - i)) % mod;
}

int ans[N];

int main() {
    freopen("match.in", "r", stdin), freopen("match.out", "w", stdout);
    int n; scanf("%d%s", &n, s + 1), frac[0] = C[0][0] = 1;
    for (int i = 1; i <= n; i++) 
        if (s[i] == '1') a[i]++; else b[i]++;
    for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), adde(a, b);
    m = n / 2, dfs(1, 0);
    for (int i = 1; i <= m; i++) {
        frac[i] = (LL)frac[i - 1] * i % mod, C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    for (int i = 0; i <= m; i++) ans[i] = (LL)dp[1][i] * frac[m - i] % mod;
    for (int i = m; i >= 0; i--) 
        for (int j = i + 1; j <= m; j++)
            ans[i] = (ans[i] - (LL)ans[j] * C[j][i] % mod + mod) % mod;
    for (int i = 0; i <= m; i++) printf("%d ", ans[i]);
}
