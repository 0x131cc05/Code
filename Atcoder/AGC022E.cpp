#include <bits/stdc++.h>
using namespace std;

const int N = 300010;
const int mod = 1e9 + 7;

int dp[N][3][3]; char s[N];

int main() {
    scanf("%s", s + 1), dp[0][0][0] = 1; int n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        for (int a = 0; a <= 2; a++)
            for (int b = 0; b <= 2; b++) {
                if (s[i] != '1') {
                    if (b == 2) dp[i][a][b - 1] = (dp[i][a][b - 1] + dp[i - 1][a][b]) % mod;
                    else dp[i][a][b + 1] = (dp[i][a][b + 1] + dp[i - 1][a][b]) % mod;
                } 
                if (s[i] != '0') {
                    if (b) dp[i][a][b - 1] = (dp[i][a][b - 1] + dp[i - 1][a][b]) % mod;
                    else dp[i][min(2, a + 1)][b] = (dp[i][min(2, a + 1)][b] + dp[i - 1][a][b]) % mod;
                }
            }
    }
    int res = 0;
    for (int a = 0; a <= 2; a++)
        for (int b = 0; b <= a; b++) res = (res + dp[n][a][b]) % mod;
    printf("%d\n", res);
}