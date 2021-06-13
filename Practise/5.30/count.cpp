#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

typedef long long LL;

struct Matrix {
    int a[3][3], n;
    Matrix() { memset(a, 0, sizeof(a)); }
    int* operator[] (int x) { return a[x]; }
    Matrix operator* (Matrix b) {
        Matrix res; res.n = n;
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) 
                    res[i][j] = (res[i][j] + (LL)a[i][k] * b[k][j]) % mod;
        return res;
    }
};

Matrix Pow(Matrix x, int y) {
    Matrix res; res.n = x.n;
    for (int i = 0; i < res.n; i++) res[i][i] = 1;
    for (; y; y >>= 1, x = x * x) if (y & 1) res = res * x;
    return res;
}

int F(int n) {
    if (n == 0) return 1;
    Matrix base; base.n = 2;
    base[0][0] = 3, base[0][1] = mod - 1, base[1][0] = 1;
    base = Pow(base, n - 1);
    return base[0][0];
}

Matrix A;

int pre(int n) {
    if (n == 0) return 1;
    if (n == 1) return 2;
    return ((LL)4 * A[0][0] + A[0][1]) % mod + 1;
}

int G(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return ((LL)5 * A[0][0] + A[0][1]) % mod;
}

int main() {
    freopen("count.in", "r", stdin), freopen("count.out", "w", stdout);
    int T; scanf("%d", &T);
    Matrix base; base.n = 3;
    base[0][0] = 4, base[0][1] = mod - 4, base[0][2] = 1;
    base[1][0] = base[2][1] = 1;
    while (T--) {
        int n, m; scanf("%d%d", &n, &m);
        if (n - m >= 2) A = Pow(base, n - m - 2);
        int G0 = G(n - m), pre0 = pre(n - m);
        if (m - 1 >= 2) A = Pow(base, m - 3);
        int G1 = G(m - 1), pre1 = pre(m - 1);
        if (n >= 2) A = Pow(base, n - 2);
        int res = G(n);
        if (m != n) res = (res + (LL)m * (G0 + F(n - m) - (n - m) - (LL)(n - m) * (n - m) % mod)) % mod;
        if (m != 1) res = (res + (LL)(n - m) * (G1 + F(m - 1) - (m - 1) - (LL)(m - 1) * (m - 1) % mod)) % mod;
        res = (res + (LL)n * m % mod * (n - m)) % mod;
        int tmp = F(n);
        tmp = (tmp - F(n - m + 1) - (LL)(m - 1) * pre0) % mod;
        tmp = (tmp - F(m) - (LL)(n - m) * pre1) % mod;
        tmp = (tmp + n) % mod;
        res = (res + mod) % mod, tmp = (tmp + mod) % mod;
        printf("%lld\n", (res + (LL)2 * tmp) % mod);
    }
    
}