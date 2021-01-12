#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const int mod = 1e9 + 7;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int n, m, pw[N], inv[N];

inline int DP(LL s) { // 以 s 集合作为 border
    static int dp[N]; memset(dp, 0, sizeof(dp)); // dp[i]: i - n + 1 ~ i 为 T 串第一次出现位置
    int res = 0;
    for (int i = m, tmp = 0; i <= n; i++) {
        // for (int j = i - m; j >= 0; j--) 
        //     dp[i] = (dp[i] - (LL)dp[j] * pw[i - j - m] % mod + mod) % mod;
        dp[i] = (pw[i - m] - (LL)tmp * pw[i - m] % mod + mod) % mod;
        for (int j = 1; j < m; j++) if (s & (1ll << j - 1)) 
            dp[i] = (dp[i] - dp[i - m + j] + mod) % mod; 
        tmp = (tmp + (LL)dp[i - m + 1] * inv[i - m + 1]) % mod;
        res = (res + (LL)dp[i] * pw[n - i]) % mod;
    }
    return res;
}

int res;

vector<int> dfs(LL s, int w) {
    vector<int> wkr(m + 1, 0); // wkr[i]: 以当前 border 集合作为该串 border 集合的前缀，长度为 i 的 T 串的数量
    int up = s ? 64 - __builtin_clzll(s) : 0;
    wkr[up] = w;
    if (up == m) {
        res = (res + (LL)w * DP(s)) % mod;
        return wkr;
    }
    for (int i = up + 1; i <= m; i++) {
        bool flag = true;
        for (int j = up; j * 2 > i && flag; j--) // 如果 j 是 border, 那么 j * 2 - i 也应是 border
            if ((s & (1ll << j - 1)) && (!(s & (1ll << (j * 2 - i) - 1)))) 
                flag = false;
        if (!flag) continue;
        int nw = (LL)w * pw[max(0, i - up * 2)] % mod;
        nw = (nw - wkr[i] + mod) % mod; // 保证了 up, i 一定是 border, 但没有保证 (up, i) 中没有 border，因此需要减去 (up, i) 中存在其它 border 的情况
        if (!nw) continue;
        vector<int> tmp = dfs(s | (1ll << i - 1), nw);
        for (int j = i; j <= m; j++) wkr[j] = (wkr[j] + tmp[j]) % mod;
    }
    return wkr;
}

int main() {
    int a; scanf("%d%d%d", &n, &m, &a), pw[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = (LL)pw[i - 1] * a % mod;
        inv[i] = Pow(pw[i], mod - 2);
    }
    dfs(0, 1), printf("%d\n", res);
    return 0;
}