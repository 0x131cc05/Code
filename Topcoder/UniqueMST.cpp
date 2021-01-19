#include <bits/stdc++.h>
using namespace std;

const int N = 55;

typedef long long LL;

int mod;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int f[N * N][N], frac[N], inv[N];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

vector<int> DP(int n, int c) {
    frac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    f[0][1] = 1;
    for (int i = 1; i <= n * n; i++) {
        static int inv[N * N]; inv[0] = 1;
        int t = Pow(c - i, mod - 2);
        for (int j = 1; j <= n * n; j++) inv[j] = (LL)inv[j - 1] * t % mod;
        for (int lst = 1; lst <= n; lst++) {
            static int g[N], fuck[N]; memset(g, 0, sizeof(g));
            for (int j = 1; j <= lst; j++) fuck[j] = (LL)f[i - 1][j] * inv[j * (j - 1) / 2 + 1] % mod * lst % mod * j % mod;
            for (int j = 1; j <= lst; j++) {
                g[j] = fuck[j];
                for (int k = 1; k < j; k++) 
                    g[j] = (g[j] + (LL)fuck[k] * C(j - 1, k - 1) % mod * g[j - k]) % mod;
            }
            f[i][lst] = (LL)g[lst] * Pow(c - i, lst * (lst - 1) / 2 + 1) % mod * Pow(lst, mod - 3) % mod;
        }
    }
    // cout << f[2][3] << endl;
    vector<int> res;
    for (int i = 0; i <= n * n; i++) res.push_back(f[i][n]);
    return res;
}


int lerp(vector<int> y, int x) {
    int n = y.size(), res = 0;
    for (int i = 1; i < n; i++) {
        int A = 1, B = 1;
        for (int j = 1; j < n; j++) if (j != i) 
            A = (LL)A * (x - j) % mod, B = (LL)B * (i - j) % mod;
        A = (LL)A * Pow(B, mod - 2) % mod;
        res = (res + (LL)y[i] * A) % mod;
    }
    res = (res + mod) % mod;
    return res;
}

struct UniqueMST {
    int count(int n, int k, int m) {
        if (n == 2) return k % m;
        mod = m; auto res = DP(n, k);
        return lerp(res, k - 1);
    }
};

// int main() {
//     UniqueMST solver;
//     cout << solver.count(3, 3, 998244353) << endl;
// }