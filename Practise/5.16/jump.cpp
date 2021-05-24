#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;
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

// 1. 全局 + 1
// 2. dp[u][j] = prod dp[v][j - 1]
int *cur, *dp[N], buf[N * 2], son[N], len[N], *g[N], bufG[N * 2], *curG;

void pushdown(int u, int L) {
    int sum = 1;
    for (int i = 1; i <= L; i++) 
        sum = (LL)g[u][i] * sum % mod, dp[u][i] = (LL)dp[u][i] * sum % mod, g[u][i] = 1;
    if (L < len[u]) g[u][L + 1] = (LL)g[u][L + 1] * sum % mod;
}

void dfs(int u, int f) {
    len[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u);
            if (len[e[i].to] >= len[son[u]]) son[u] = e[i].to, len[u] = len[e[i].to] + 1;
        }
}

int Add(int x, int y) {
   return x + y - (x + y >= mod ? mod : 0); 
}

void dfs1(int u, int f) {
    if (son[u]) dp[son[u]] = dp[u] + 1, g[son[u]] = g[u] + 1, dfs1(son[u], u);
    dp[u][1] = g[u][1] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && e[i].to != son[u]) {
            dp[e[i].to] = cur, cur += len[e[i].to] + 1, g[e[i].to] = curG, curG += len[e[i].to] + 1, dfs1(e[i].to, u);
            pushdown(u, len[e[i].to] + 1), pushdown(e[i].to, len[e[i].to]);
            static int tmp[N]; tmp[0] = 0;
            for (int j = 1; j <= len[e[i].to] + 1; j++) 
                tmp[j] = Add(tmp[j - 1], dp[u][j]) % mod;
            int sum = 1;
            for (int j = 1; j <= len[e[i].to] + 1; j++) {
                dp[u][j] = ((LL)tmp[j - 1] * dp[e[i].to][j - 1] + (LL)dp[u][j] * sum) % mod;
                sum = Add(sum, dp[e[i].to][j]) % mod;
            }
            if (len[e[i].to] + 1 < len[u]) g[u][len[e[i].to] + 2] = (LL)g[u][len[e[i].to] + 2] * sum % mod;
        }
    pushdown(u, len[u]);
}

int all[N];

template<class T> void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
    freopen("jump.in", "r", stdin), freopen("jump.out", "w", stdout);
    int n; read(n), cur = buf, curG = bufG;
    for (int i = 1, a, b; i < n; i++) 
        read(a), read(b), adde(a, b);
    dfs(1, 0);
    vector<int> son;
    for (int i = head[1]; i; i = e[i].next) {
        dp[e[i].to] = cur, cur += len[e[i].to] + 1, g[e[i].to] = curG, curG += len[e[i].to] + 1; 
        dfs1(e[i].to, 1), pushdown(e[i].to, len[e[i].to]);
        for (int j = 1; j <= len[e[i].to]; j++) dp[e[i].to][j] = (dp[e[i].to][j] + dp[e[i].to][j - 1]) % mod;
        son.push_back(e[i].to);
    }
    sort(son.begin(), son.end(), [&](int a, int b) {
        return len[a] < len[b];
    });
    for (int i = 0; i <= n; i++) all[i] = 1;
    int tmp = 1, lst = 0;
    for (auto v : son) {
        while (lst < len[v]) all[++lst] = tmp;
        for (int i = 1; i <= len[v]; i++) all[i] = (LL)all[i] * (dp[v][i] + 1) % mod;
        tmp = (LL)tmp * (dp[v][len[v]] + 1) % mod;
    }
    int res = 0;
    for (auto v : son) {
        for (int i = 1; i <= len[v]; i++) {
            int lst = i == 1 ? 0 : dp[v][i - 1];
            int w = (LL)all[i - 1] * Pow(lst + 1, mod - 2) % mod * (dp[v][i] - lst + mod) % mod;
            res = Add(res, w); 
        }
    }
    printf("%d\n", (tmp - res + mod) % mod);
} 
