#include <bits/stdc++.h>
using namespace std;

const int N = 51;

typedef long long LL;

int f[9][N][N][256], g[9][N], C[N][N], mod;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int F(int x, int y, int m, int mx) { // < 2 ^ m, ^ >= mx
    if (mx == 0 || (!x || !y)) return Pow(1 << m, x + y);
    if (x > y) swap(x, y);
    if (~f[m][x][y][mx]) return f[m][x][y][mx];
    int &res = f[m][x][y][mx]; res = 0;
    if (mx & (1 << m - 1)) return res = 2 * F(x, y, m - 1, mx ^ (1 << m - 1)) % mod;
    for (int a = 0; a <= x; a++)
        for (int b = 0; b <= y; b++) {
            int w = (LL)C[x][a] * C[y][b] % mod;
            res = (res + (LL)F(a, b, m - 1, mx) * F(x - a, y - b, m - 1, mx) % mod * w) % mod;
        }
    return res;
}

int G(int n, int m) {
    if (n <= 1 || m == 0) return 0;
    if (~g[m][n]) return g[m][n];
    int &res = g[m][n]; res = G(n, m - 1) * 2 % mod;
    for (int a = 1; a < n; a++) {
        int tmp = 0;
        for (int t = 1; t < 1 << m - 1; t++) 
            tmp = (tmp + F(a, n - a, m - 1, t)) % mod;
//        cout << n << ' ' << m << ' ' << a << ' ' << tmp << endl;
        int l = Pow(1 << m - 1, a), r = Pow(1 << m - 1, n - a);
        tmp = (tmp + (LL)G(a, m - 1) * r + (LL)G(n - a, m - 1) * l) % mod;
        tmp = (tmp + (LL)l * r % mod * (1 << m - 1)) % mod;
        res = (res + (LL)tmp * C[n][a]) % mod;
    }
    return res;
}

int main() {
    memset(f, -1, sizeof(f)), memset(g, -1, sizeof(g));
    int n, m; scanf("%d%d%d", &n, &m, &mod);
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    printf("%d\n", G(n, m));
} 
