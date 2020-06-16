#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

// f, g 是否有对子，以上一种花色开头的有 i 个顺子，以这一种花色开头的有 j 个顺子，能构成的顺子个数的最大值
// db 能组成的不同对子的总数 
// db >= 7 or g[*][*] >= 4

struct WEN { 

int f[3][3], g[3][3]; int db;

WEN() { memset(f, -1, sizeof(f)), memset(g, -1, sizeof(g)), db = 0; } 

bool operator < (const WEN &b) const {
    if (db != b.db) return db < b.db;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) 
            if (f[i][j] != b.f[i][j])
                return f[i][j] < b.f[i][j];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) 
            if (g[i][j] != b.g[i][j])
                return g[i][j] < b.g[i][j];
    return 0;
}

};

map<WEN, int> mp; vector<WEN> st; int trans[4010][5], tot;

inline int nxt(WEN nw, int num) {
    WEN tar; tar.db = nw.db;
    if (num >= 2) tar.db++;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) 
            for (int k = 0; i + j + k <= num; k++) {
                int remain = num - i - j - k, ok = nw.f[i][j] + i, ok1 = nw.g[i][j] + i;
                if (remain < 2) {
                    if (~nw.g[i][j]) tar.g[j][k] = max(tar.g[j][k], ok1);
                    if (~nw.f[i][j]) tar.f[j][k] = max(tar.f[j][k], ok);
                } else {
                    if (~nw.f[i][j]) tar.g[j][k] = max(tar.g[j][k], ok);
                    if (~nw.g[i][j]) tar.g[j][k] = max(tar.g[j][k], ok1);
                }
                if (remain >= 3) {
                    if (~nw.g[i][j]) tar.g[j][k] = max(tar.g[j][k], ok1 + 1);
                    if (~nw.f[i][j]) tar.f[j][k] = max(tar.f[j][k], ok + 1);
                }
            }    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tar.f[i][j] = min(tar.f[i][j], 4);
    if (tar.db >= 7) return -1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tar.g[i][j] >= 4) return -1;
    if (mp.count(tar)) {
        trans[mp[nw]][num] = mp[tar];
        return -1;
    } 
    mp[tar] = ++tot, st.push_back(tar), trans[mp[nw]][num] = tot;
    return tot;
}
 
void dfs(WEN nw) {
    for (int i = 0; i <= 4; i++) {
        int hh = nxt(nw, i);
        if (~hh) dfs(st[hh - 1]);
    }
}

int dp[N][N * 4][4010], frac[N * 4], inv[N * 4];

inline int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int ct[N];

int main() {
    WEN base; base.f[0][0] = 0, tot = 1; st.push_back(base), mp[base] = 1;
    dfs(base), dp[0][0][1] = frac[0] = inv[0] = 1;
    int n; scanf("%d", &n);
    for (int i = 1; i <= n * 4; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 1, a; i <= 13; i++) 
        scanf("%d%*d", &a), ct[a]++;
    for (int i = 1; i <= n; i++) 
        for (int l = 0; l <= (i - 1) * 4; l++)
            for (int k = 1; k <= tot; k++) if (dp[i - 1][l][k])
                for (int j = ct[i]; j <= 4; j++) if (trans[k][j]) 
                    dp[i][l + j - ct[i]][trans[k][j]] = (dp[i][l + j - ct[i]][trans[k][j]] + (LL)dp[i - 1][l][k] * 
                        C(l + j - ct[i], j - ct[i]) % mod * C(4 - ct[i], j - ct[i]) % mod * frac[j - ct[i]]) % mod;
    int res = 0;
    for (int i = 0; i <= 4 * n - 13; i++)
        for (int j = 1; j <= tot; j++) if (dp[n][i][j])
            res = (res + (LL)dp[n][i][j] * Pow((LL)C(4 * n - 13, i) * frac[i] % mod, mod - 2)) % mod;
    printf("%d\n", res);
}


