#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int dp[N][N];

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

struct BearCircleGame {
    int winProbability(int n, int k) {
        dp[1][0] = 1;
        for (int i = 2; i <= n; i++) {
            int g = gcd(i, k);
            static int v[2][N]; memset(v, 0, sizeof(v)); 
            for (int j = 0; j < g; j++) {
                v[0][j] = 1;
                int cur = j;
                while (233) {
                    int ls = cur; cur = (cur - k % i + i) % i;
                    int a[2] = { 0, 0 }; 
                    for (int t = 0; t <= 1; t++) 
                        a[t] = (LL)inv2 * v[t][ls] % mod;
                    if (ls != 1) a[1] = (a[1] + (LL)inv2 * dp[i - 1][max(ls - 1, 0)]) % mod;
                    if (cur == j) {
                        dp[i][j] = (LL)a[1] * Pow(1 - a[0], mod - 2) % mod;
                        if (dp[i][j] < 0) dp[i][j] += mod;
                        break;
                    }
                    v[0][cur] = a[0], v[1][cur] = a[1];
                }
                while (233) {
                    cur = (cur - k % i + i) % i;
                    if (cur == j) break;
                    dp[i][cur] = ((LL)v[0][cur] * dp[i][j] + v[1][cur]) % mod;  
                }
            }
        }
        return dp[n][0];
    }
};

// int main() {
//     BearCircleGame solver;
//     cout << solver.winProbability(1987, 987654321);
// }