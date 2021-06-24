#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int mod = 998244353;

int dp[N][N], pos[N];

int DP(int l, int r) {
    if (r <= pos[l]) return r - l + 1;
    if (dp[l][r]) return dp[l][r];
    return dp[l][r] = (DP(l, r - 1) + DP(l + 1, r) + 1) % mod;
}

char s[N];

int main() {
    scanf("%s", s + 1); int n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        pos[i] = max(pos[i - 1], i);
        while (pos[i] < n && s[pos[i] + 1] == s[i]) pos[i]++;
    }
    printf("%d\n", DP(1, n));
}