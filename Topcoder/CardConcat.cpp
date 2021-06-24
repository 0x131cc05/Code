#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int N = 110;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int f[N][N], g[N][N], pw[11], len[N], frac[N], w[N], inv[N];

int get(int x) {
    return x >= 10 ? get(x / 10) + 1 : 1;
}

struct CardConcat {
    int sum(vector<int> cards) {
        int n = cards.size();
        for (int i = 1; i <= n; i++) len[i] = get(cards[i - 1]);
        pw[0] = frac[0] = inv[0] = 1;
        for (int i = 1; i <= 10; i++) pw[i] = (LL)pw[i - 1] * 10 % mod;
        for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
        f[0][0] = g[n + 1][0] = 1;
        for (int i = 1; i <= n; i++) 
            for (int j = 0; j <= i; j++) {
                f[i][j] = f[i - 1][j];
                if (j) f[i][j] = (f[i][j] + (LL)f[i - 1][j - 1] * pw[len[i]]) % mod;
            }
        for (int i = n; i >= 1; i--)
            for (int j = 0; j <= n - i + 1; j++) {
                g[i][j] = g[i + 1][j];
                if (j) g[i][j] = (g[i][j] + (LL)g[i + 1][j - 1] * pw[len[i]]) % mod;
            }
        for (int i = 0, tmp = 0; i <= n; i++) {
            tmp = (tmp + inv[i]) % mod;
            w[i] = (LL)tmp * frac[i] % mod;
        }        
        int res = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < n; j++) {
                int t = 0;
                for (int l = 0; l < i && l <= j; l++) 
                    t = (t + (LL)f[i - 1][l] * g[i + 1][j - l]) % mod;
                res = (res + (LL)t * w[n - 1 - j] % mod * frac[j] % mod * cards[i - 1]) % mod;
            }
        }
        return res;
    }
};

// int main() {
//     CardConcat solver;
//     cout << solver.sum({1, 1, 2, 3, 5, 8, 13}) << endl;
// }
 