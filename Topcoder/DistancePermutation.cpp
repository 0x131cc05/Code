#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int N = 55;

typedef long long LL;
typedef pair<int, int> P;

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
    // cout << "adde: " << from << ' ' << to << endl;
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int dfn[N], sz[N], dist[N][N], dfsn;

int rt;

void getDis(int u, int f, int d) {
    dist[rt][u] = d;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) getDis(e[i].to, u, d + 1);
}

void dfs(int u, int f) {
    dfn[u] = ++dfsn, sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u), sz[u] += sz[e[i].to];
}

vector<int> wkr[N];

bool check(int u) {
    if (u == rt) return false;
    for (auto t : wkr[u]) 
        if (dfn[t] < dfn[u] || dfn[t] > dfn[u] + sz[u] - 1) return false;
    return true;
}

int n;

int ans[N], frac[N], inv[N];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

void DP(vector<P> item, bool flag) { 
    int m = item.size(); static int dp[2][2][N]; 
    memset(dp, 0, sizeof(dp)), dp[0][0][0] = 1;
    int cur = 0, ct = 0;
    for (int i = 0; i < m; i++) {
        cur ^= 1, memset(dp[cur], 0, sizeof(dp[cur])), ct += item[i].first;
        for (int a = 0; a <= 1; a++) {
            for (int j = 0; j <= item[i].second; j++) {
                int nxt = a | (item[i].first && j == 0);
                for (int k = j; k <= n; k++) 
                    dp[cur][nxt][k] = (dp[cur][nxt][k] + (LL)dp[cur ^ 1][a][k - j] * C(item[i].second, j)) % mod;
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        int tmp = dp[cur][flag][i];
        if (!tmp) continue;
        for (int j = 0; j < m; j++) if (i <= item[j].second) {
            if (flag && ct == 1 && item[j].first) continue;
            tmp = (tmp - C(item[j].second, i) + mod) % mod;
        }
        ans[i] = (ans[i] + tmp) % mod;
    }
}

void solve(int u, int f) {
    wkr[u].clear();
    for (int i = 1; i <= n; i++) if (dist[u][i] == dist[u][rt] && i != rt) 
        wkr[u].push_back(i);
    if (wkr[u].size() && u != rt) ans[1]++;
    vector<P> tmp = { P(0, 1) };
    if (check(u)) {
        for (int i = head[u]; i; i = e[i].next)
            if (e[i].to != f) {
                bool flag = false;
                for (auto v : wkr[u]) 
                    if (dfn[e[i].to] <= dfn[v] && dfn[v] <= dfn[e[i].to] + sz[e[i].to] - 1) 
                        { flag = true; break; }
                tmp.push_back(P(flag, sz[e[i].to]));
            }
        DP(tmp, true);
    } else if (u != rt) {
        for (int i = head[u]; i; i = e[i].next)
            if (e[i].to != f) tmp.push_back(P(0, sz[e[i].to]));
        DP(tmp, false);
    }
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) solve(e[i].to, u);
}

struct DistancePermutation {
    int solve(vector<int> p) {
        if (!p.size()) return 0;
        n = p.size() + 1;
        for (int i = 1; i < n; i++) 
            adde(p[i - 1] + 1, i + 1);
        frac[0] = inv[0] = 1;
        for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
        for (int i = 1; i <= n; i++) rt = i, getDis(i, 0, 0);
        int res = 0;
        for (int i = 1; i <= n; i++) {
            rt = i, dfsn = 0, dfs(i, 0), ::solve(i, 0);
            res = (res + frac[n]) % mod;
            for (int j = 1; j <= n; j++) 
                res = (res + (LL)ans[j] * frac[j] % mod * frac[n - j]) % mod;
            memset(ans, 0, sizeof(ans));
        }
        return res;
    }
};
