#include <bits/stdc++.h>
using namespace std;

const int N = 41;
const int mod = 1e9 + 7;

typedef long long LL;

int f[5][N][N * N * 4], g[N][N * N * 4];

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int p[6], pw[6][N * N], C[N][N];

int main() {
    int n, m; scanf("%d%d", &n, &m); int inv = Pow(100, mod - 2);
    for (int i = 0; i <= m; i++) scanf("%d", &p[i]), p[i] = (LL)p[i] * inv % mod;
    p[m + 1] = p[0];
    for (int i = m; i >= 1; i--) p[i] = (p[i] + p[i + 1]) % mod;
    for (int i = 1; i <= m + 1; i++) {
        pw[i][0] = 1, pw[i][1] = p[i];
        for (int j = 2; j <= n * n; j++) pw[i][j] = (LL)pw[i][j - 1] * p[i] % mod;
    }
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    f[0][1][0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++)
            for (int k = j - 1; k <= (j - 1) * i; k++) {
                g[j][k] = f[i - 1][j][k];
                for (int l = 1; l < j; l++) 
                    for (int t = l - 1; t <= (l - 1) * (i - 1) && t + i <= k; t++) 
                        g[j][k] = (g[j][k] + (LL)f[i - 1][l][t] * C[j - 1][l - 1] % mod 
                                * g[j - l][k - t - i] % mod * pw[i][l * (j - l)]) % mod;
            }
        memcpy(f[i], g, sizeof(g));
        for (int j = 1; j <= n; j++)
            for (int k = j - 1; k <= (j - 1) * i; k++) {
                for (int l = 1; l < j; l++) 
                    for (int t = l - 1; t <= (l - 1) * i && t + i <= k; t++) {
                        f[i][j][k] = (f[i][j][k] - (LL)f[i][l][t] * g[j - l][k - t - i] % mod 
                            * C[j - 1][l - 1] % mod * pw[i + 1][l * (j - l)]) % mod;
                        f[i][j][k] = (f[i][j][k] + mod) % mod;
                    }
            }
                
    }
        
    for (int i = n - 1; i <= m * (n - 1); i++) 
        printf("%d ", f[m][n][i]);
} 
