#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res; 
}

int p[8][8]; map<__int128_t, int> mp[8];

int dp[8][40010], tot[8]; __int128_t st[8][40010];

int main() {
    int n; scanf("%d", &n); int inv = Pow(100, mod - 2); 
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &p[i][j]), p[i][j] = (LL)p[i][j] * inv % mod;
    mp[0][1] = dp[0][1] = tot[0] = st[0][1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int s = 1; s < 1 << n; s++) {
            int w = 1;
            for (int j = 1; j <= n; j++) if (s & (1 << j - 1))
                w = (LL)w * p[i][j] % mod;
            else w = (LL)w * (mod + 1 - p[i][j]) % mod;
            for (int t = 1; t <= tot[i - 1]; t++) {
                __int128_t tmp = st[i - 1][t], nw = 0;
                for (int ss = 0; ss < 1 << n; ss++) if (tmp & ((__int128_t)1 << ss)) 
                    for (int j = 1; j <= n; j++) if (s & (1 << j - 1)) 
                        if (!(ss & (1 << j - 1))) nw |= (__int128_t)1 << (ss | (1 << j - 1));
                if (!mp[i].count(nw)) mp[i][nw] = ++tot[i], st[i][tot[i]] = nw;
                int to = mp[i][nw];
                dp[i][to] = (dp[i][to] + (LL)dp[i - 1][t] * w) % mod;
            }
        }
    }
    int res = 0, all = (1 << n) - 1;
    for (int i = 1; i <= tot[n]; i++)
        if (st[n][i] & ((__int128_t)1 << all)) res = (res + dp[n][i]) % mod;
    printf("%d\n", res);
}