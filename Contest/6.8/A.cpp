#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const int mod = 1e9 + 7;

typedef long long LL;

int f[N], C[N][N], g[N][N], tmp[N][N];

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int main() {
//    freopen("biao.out", "w", stdout);
    for (int i = 0; i <= 200; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    f[0] = 1;
    for (int i = 1; i <= 200; i++) {
        f[i] = Pow(2, C[i][2]);
        for (int j = 1; j < i; j++) 
            f[i] = (f[i] - (LL)f[j] * C[i - 1][j - 1] % mod * Pow(2, C[i - j][2]) % mod + mod) % mod;
    }
    for (int i = 1; i <= 200; i++) {
        tmp[i][0] = f[i], tmp[0][i] = 1;
        for (int j = 1; j <= 200; j++) {
            tmp[i][j] = (LL)f[i] * Pow((Pow(2, i) - 1), j) % mod * Pow(2, C[j][2]) % mod;
        }
    }
    g[0][0] = 1;
    for (int j = 0; j <= 200; j++) g[0][j] = Pow(2, C[j][2]);
    for (int i = 1; i <= 200; i++) {
        for (int j = 0; j <= 200 - i; j++) {
            for (int k = 1; k <= i; k++)
                for (int l = 0; l <= j; l++) {
                    int w = tmp[l][k];
                    g[i][j] = (g[i][j] + (LL)C[j][l] * C[i - 1][k - 1] % mod * g[i - k][j - l] % mod * w) % mod;
                }
        }
    }
    int T; scanf("%d", &T);
    while (T--) {
        int n, m; scanf("%d%d", &n, &m);
        printf("%d\n", g[n - m][m]);
    }
}
