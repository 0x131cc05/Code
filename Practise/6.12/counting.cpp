#include <bits/stdc++.h>
using namespace std;

const int N = 17;
const int mod = 998244353;

typedef long long LL;

int g[1 << N], f[1 << N], ct[1 << N], id[N];

LL a[N], C;

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int dp[N][1 << N], n;

int DP(int s, int pos) {
    int S = s & ((1 << pos) - 1), T = s >> pos; 
    if (!T) return f[S];
    if (dp[pos][s] != -1) return dp[pos][s];
    int &res = dp[pos][s]; res = 0;
    int low = T & -T, T1 = T ^ low, p = pos + __builtin_ctz(T);
    for (int nxt = T1; ; nxt = (nxt - 1) & T1) {
        int bass = low | nxt, ct = __builtin_popcount(bass);
        if (!g[bass << pos]) continue;
        if (ct & 1) res = (res + (LL)g[bass << pos] * DP(s ^ (nxt << pos), p + 1)) % mod;
        else res = (res + (LL)g[bass << pos] * (a[p] % mod + 1) % mod * DP(s ^ (bass << pos), p + 1)) % mod;
        if (!nxt) break;
    }
    return res;
}

int pos[N];

int main() {
    // freopen("counting.in", "r", stdin), freopen("counting.out", "w", stdout);
    int m; scanf("%d%d%lld", &n, &m, &C);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++) id[i] = i;
    sort(id, id + n, [&](int i, int j) {
        return a[i] < a[j];
    });
    for (int i = 0; i < n; i++) pos[id[i]] = i;
    sort(a, a + n);
    for (int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b), a--, b--;
        a = pos[a], b = pos[b];
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
    memset(dp, -1, sizeof(dp));
    for (int s = 0; s < 1 << n; s++) {
        int v = 0;
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
        f[s] = v;
    }
    printf("%d\n", DP((1 << n) - 1, 0));
}
