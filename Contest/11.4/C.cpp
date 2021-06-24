#include <bits/stdc++.h>
using namespace std;

const int N = 4010;

typedef long long LL;

int pw[N], pw1[N], dp[N][N], sum[N];

int main() {
    int n, mod, inv2; pw[0] = pw1[0] = 1;
    cin >> n >> mod, inv2 = (mod + 1) / 2;
    for (int i = 1; i <= n + 1; i++) pw[i] = pw[i - 1] * 2 % mod, pw1[i] = (LL)pw1[i - 1] * inv2 % mod;
    dp[n][n] = 1, sum[n] = pw[n];
    for (int t = n * 2 - 1; t >= 0; t--) {
        for (int i = min(n, t); i >= max(0, t - n); i--) {
            int j = t - i; 
            dp[i][j] = (LL)sum[i] * (j + 1) % mod * pw1[j + 1] % mod;
        }
        for (int i = min(n, t); i >= max(0, t - n); i--) {
            int j = t - i;
            sum[j] = (sum[j] + (LL)dp[i][j] * pw[i]) % mod;
        }
    }
        
    printf("%d\n", dp[0][0] * 2 % mod);
}
