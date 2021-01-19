#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int mod = 998244353;

typedef long long LL;

int f[N], dp[N][N], frac[N], inv[N];

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int coef[N];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int main() {
    int n; scanf("%d", &n), dp[0][0] = 1;
    frac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 1; i <= n; i++) {
        if (i % 3 == 1) continue;
        coef[i] = i % 6 == 5 || i % 6 == 0 ? -1 : 1; 
    }
    for (int i = 1; i <= n; i++) cout << coef[i] << ' ';
    cout << endl;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i / 2; j++) 
            for (int k = 2; k <= i; k++) dp[i][j] = (dp[i][j] + (LL)dp[i - k][j - 1] * k * coef[k]) % mod;
    int res = 0;
    for (int i = 1; i <= n / 2; i++) {
        int w = dp[n][i];
        f[i] = (LL)w * Pow(n, (mod - 1 + i - 2) % (mod - 1)) % mod;
        res = (res + f[i]) % mod;
    }
//    cout << f[1] << ' ' << f[2] << endl;
//    int res = 0;
//    for (int i = 1; i <= n / 2; i++) {
//        int fuck = 0;
//        for (int j = 1; j <= i; j++) {
//            int w = (LL)f[j] * C(i - 1, i - j) % mod;
//            if ((i - j) & 1) fuck = (fuck - w + mod) % mod;
//            else fuck = (fuck + w) % mod;
//        }
////        cout << fuck << endl;
//        res = (res + fuck) % mod;
//    }
    printf("%d\n", res);
}
