#include <bits/stdc++.h>
using namespace std;

const int N = 17;
const int mod = 998244353;

typedef long long LL;

int g[1 << N], f[1 << N], ct[1 << N], ban[1 << N], wkr[1 << N];

LL a[N], C;

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int sum[N][N + 1][1 << N];

int main() {
    // freopen("counting.in", "r", stdin), freopen("counting.out", "w", stdout);
    int n, m; scanf("%d%d%lld", &n, &m, &C);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    for (int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b), a--, b--;
        for (int s = 0; s < 1 << n; s++) 
            if ((s & (1 << a)) && (s & (1 << b))) 
                ct[s]++;
    }
    for (int s = 1; s < 1 << n; s++) {
        g[s] = ct[s] ? 0 : 1;
        int low = s & -s;
        for (int s1 = (s - 1) & s; s1; s1 = (s1 - 1) & s) if (s1 & low) {
            int other = s ^ s1;
            if (!ct[other]) 
                Inc(g[s], mod - g[s1]);
        } 
    }
    int all = (1 << n) - 1;
    for (int s = 1; s < 1 << n; s++) if (g[s]) {
        LL mn = 1e18; int pos = 0;
        for (int i = 0; i < n; i++) if (s & (1 << i)) {
            if (a[i] <= mn) mn = a[i], pos = i; 
        }
        int s1 = all ^ s, t = __builtin_popcount(s);
        int hh = (a[pos] + 1) % mod;
        if (!(t & 1)) Inc(ban[s], (LL)g[s] * hh % mod);
        else for (int ss = s1; ; ss = (ss - 1) & s1) {
            Inc(sum[pos][t - 1][ss | s], g[s]);
            if (!ss) break;
        } 
    }
    wkr[0] = 1;
    for (int s = 1; s < 1 << n; s++) {
        int low = s & -s;
        for (int s1 = s; s1; s1 = (s1 - 1) & s) if (s1 & low)
            wkr[s] = (wkr[s] + (LL)wkr[s ^ s1] * ban[s1]) % mod;
    }
    for (int s = 1; s < 1 << n; s++) {
        static int dp[N + 1][1 << N];
        int r = __builtin_popcount(s);
        for (int s1 = s; ; s1 = (s1 - 1) & s) {
            int t = n - __builtin_popcount(s1);
            for (int i = 0; i <= t; i += 2)
                dp[i][s1] = 0;
            if (!s1) break;
        }
        for (int s1 = s; ; s1 = (s1 - 1) & s) {
            Inc(dp[__builtin_popcount(s1)][0], wkr[s1]);
            if (!s1) break;
        }
        vector<int> fuck;
        for (int s1 = s; s1; s1 = (s1 - 1) & s) 
            fuck.push_back(s1);
        reverse(fuck.begin(), fuck.end());
        for (auto s1 : fuck) {
            int low = s1 & -s1, s2 = s1 ^ low, pos = __builtin_ctz(low);
            int t = __builtin_popcount(s1);
            for (int i = 0; i <= n - t; i += 2) if (dp[i][s2]) {
                int w = dp[i][s2];
                for (int j = 0; i + j <= n - t; j += 2) {
                    dp[i + j][s1] = (dp[i + j][s1] + (LL)w * sum[pos][j][s]) % mod;
                } 
            }
        }
        for (auto s1 : fuck) {
            int w = dp[n - __builtin_popcount(s1)][s1];
            if ((n - r) & 1) w = mod - w;
            Inc(f[s1], w);
        }
    }
    int res = 0;
    for (int s = 1; s < 1 << n; s++) {
        int w = f[s], v = 0;
        if (!w) continue;
        bool flag = true;
        for (int i = 62; i >= 0; i--) {
            int all = 0; static int dp[2][2][2]; memset(dp, 0, sizeof(dp));
            dp[0][0][0] = 1; int cur = 0;
            int A = (1ll << i) % mod;
            for (int j = 0; j < n; j++) if (s & (1 << j)) {
                cur ^= 1, memset(dp[cur], 0, sizeof(dp[cur]));
                int c = (a[j] >> i) & 1;
                all ^= c;
                int B = ((a[j] & ((1ll << i) - 1)) + 1) % mod;
                for (int a = 0; a <= 1; a++)
                    for (int b = 0; b <= 1; b++) if (dp[cur ^ 1][a][b]) {
                        int t = dp[cur ^ 1][a][b];
                        for (int nw = 0; nw <= c; nw++) {
                            int w = 1;
                            if (nw == c || (nw != c && a))
                                w = nw == c ? B : A;
                            dp[cur][a | (nw != c)][b ^ nw] = (dp[cur][a | (nw != c)][b ^ nw] + (LL)t * w) % mod;   
                        }
                    }
            }
            int c = (C >> i) & 1;
            Inc(v, dp[cur][1][c]);
            if (all != c) {
                flag = false; break;
            }
        }
        if (flag) v++;
        res = (res + (LL)v * w) % mod;
    }
    if (!C) res = (res + wkr[all]) % mod;
    printf("%d\n", res);
}

