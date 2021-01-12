#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 1010;
const int mod = 998244353;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

char s[N]; int dp[N], nxt[N];

int main() {
    int a, b, p; scanf("%d%d%s", &a, &b, s + 1), p = (LL)a * Pow(b, mod - 2) % mod; 
    int n = strlen(s + 1);
    for (int i = 2; i <= n; i++) {
        int t = nxt[i - 1];
        while (t && s[t + 1] != s[i]) t = nxt[t];
        nxt[i] = s[t + 1] == s[i] ? t + 1 : t;
    }
    for (int i = 1; i <= n; i++) {
        int t = s[i] == 'H' ? p : mod + 1 - p, ls = i - 1;
        while (ls && s[ls + 1] == s[i]) ls = nxt[ls];
        if (s[ls + 1] != s[i]) ls++;
        int a = dp[i - 1], b = dp[ls], tmp = (1 + a - (LL)(mod + 1 - t) * b) % mod;
        dp[i] = (LL)(tmp + mod) * Pow(t, mod - 2) % mod;
    }
    printf("%d\n", dp[n]);
} 
