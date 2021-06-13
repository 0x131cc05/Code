#include <bits/stdc++.h>
using namespace std;

struct status {
    bool dp[2][3][3][5];
    void reset() { memset(dp, 0, sizeof(dp)); }
} q[10010];

const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

map<status, int> mp;

int tot;

int trans[10010][20];

int append(status s, int ct) {
    int id = mp[s];
    if (trans[id][ct] != -1) return trans[id][ct];
    status nxt; nxt.reset();
    for (int t = 0; t <= 1; t++)
        for (int a = 0; a <= 2; a++)
            for (int b = 0; b <= 2; b++) 
                for (int all = 0; all < 5; all++) if (s.dp[t][a][b][all]) {
                    for (int c = 0; c <= 1 - t; c++) {
                        int h = ct - c * 2;
                        if (h < 0) continue;
                        for (int r = 0; r <= 3 && r <= h; r++) {
                            int mn = min(min(a, b), r);
                            int w = mn + (h - r) / 3 + all, p = t | c;
                            if (w >= 5) return trans[id][ct] = 0;
                            if (w == 4 && p) return trans[id][ct] = 0;
                            nxt.dp[p][r - mn][a - mn][t] = 1;
                        } 
                    }
                }
    if (mp.count(nxt)) return trans[id][ct] = mp[nxt];
    q[++tot] = nxt, mp[nxt] = tot;
    return trans[id][ct] = tot;
}

const int N = 1010;

int frac[N], inv[N];

int ct[4][N];

int dp[1010][1010];

int solve(int ban, int n) {
    status base; base.reset(); base.dp[0][0][0][0] = 1;
    mp[base] = tot = 1;
    for (int i = 1; i <= n; i++) {
        int t = 
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    frac[0] = inv[0] = 1;
    for (int i = 1; i <= N - 10; i++) 
        frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        ct[a][b]++;
    }
}