#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int f0[N], f1[N], f2[N], g[N];

inline int calc(int len, int tot) {
    if (len < 0 || len & 1) return 0;
    return (LL)tot * tot % mod * g[len] % mod;
}

inline vector<int> BM(vector<int> y) {
    vector<int> coef, diff; static int delta[N]; int fail = -1; 
    for (int i = 0, n = y.size(); i < n; i++) {
        delta[i] = y[i];
        for (int j = 0; j < coef.size(); j++) 
            delta[i] = (delta[i] - (LL)coef[j] * y[i - j - 1] % mod + mod) % mod;
        if (!delta[i]) continue;
        if (fail == -1) {
            fail = i, coef.resize(i + 1);
            continue;
        }
        int scale = (LL)delta[i] * Pow(delta[fail], mod - 2) % mod;
        vector<int> tmp = coef; coef.clear(), coef.resize(i - fail - 1), coef.push_back(scale);
        for (auto t : diff) coef.push_back((LL)t * (mod - scale) % mod);
        fail = i, diff = tmp;
        if (coef.size() < tmp.size()) coef.resize(tmp.size());
        for (int i = 0; i < tmp.size(); i++) coef[i] = (coef[i] + tmp[i]) % mod;
    }
    return coef;
}

inline void pre(int n) {
    g[0] = g[2] = 1;
    for (int i = 4; i <= n; i += 2) 
        g[i] = (g[i - 2] + g[i - 4]) % mod;
    for (int i = 2; i <= n; i++) {
        f0[i] = calc(i - 1, i - 1), f1[i] = calc(i - 2, i - 1), f2[i] = calc(i - 3, i - 1);
        for (int j = 2; j < i; j++) {
            f0[i] = (f0[i] + (LL)calc(j - 1, j - 1) * f0[i - j] + (LL)calc(j - 2, j - 1) * f1[i - j]) % mod;
            f1[i] = (f1[i] + (LL)calc(j - 2, j - 1) * f0[i - j] + (LL)calc(j - 3, j - 1) * f1[i - j]) % mod;
            f2[i] = (f2[i] + (LL)calc(j - 2, j - 1) * f1[i - j] + (LL)calc(j - 3, j - 1) * f2[i - j]) % mod;
        }
    }
}

inline int solve(int n) {
    int res = (LL)n * (calc(n - 1, n - 1) + calc(n - 3, n - 1)) % mod;
    for (int i = 2; i <= n; i++) {
        res = (res + (LL)calc(i - 1, i - 1) * f0[n - i] % mod * i) % mod;
        res = (res + (LL)calc(i - 2, i - 1) * f1[n - i] % mod * i * 2) % mod;
        res = (res + (LL)calc(i - 3, i - 1) * f2[n - i] % mod * i) % mod;
    }
    return res;
}

int dp[2000010];

int main() {
    pre(1000); vector<int> tmp;
    for (int i = 3; i <= 1000; i++) 
        tmp.push_back(dp[i] = solve(i));
    auto now = BM(tmp); int n; scanf("%d", &n);
    for (int i = 1001; i <= n; i++) 
        for (int j = 0; j < now.size(); j++)
            dp[i] = (dp[i] + (LL)now[j] * dp[i - j - 1]) % mod;
    printf("%d\n", dp[n]);
}
