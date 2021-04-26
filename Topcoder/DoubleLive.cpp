#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
const int mod = 1e9 + 7;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int f[N][N * 2], g[N][N * 2], inv[N * 2];

struct DoubleLive {
    int findEV(int B, int H, int T) {
        f[B][H] = H, g[B][H] = H * H;
        for (int i = 1; i <= B + H; i++) inv[i] = Pow(i, mod - 2);
        int res = 0;
        for (int i = B; i >= 0; i--)
            for (int j = B + H; j >= 0; j--) if (f[i][j]) {
                int cur = B * 2 + H - i * 2 - j;
                if (cur > T) continue;
                if (j) {
                    f[i][j - 1] = (f[i][j - 1] + (LL)f[i][j] * (j - 1) % mod * inv[i + j]) % mod;
                    g[i][j - 1] = (g[i][j - 1] + ((LL)g[i][j] * (j - 2) + f[i][j]) % mod * inv[i + j]) % mod;
                }
                if (i) {
                    f[i - 1][j + 1] = (f[i - 1][j + 1] + (LL)f[i][j] * i % mod * inv[i + j]) % mod;
                    g[i - 1][j + 1] = (g[i - 1][j + 1] + (LL)g[i][j] * i % mod * inv[i + j]) % mod;
                }
                if (cur == T) 
                    res = (res + (LL)(i + j) * (i + j) % mod * f[i][j] + (LL)(mod - i - j) * g[i][j]) % mod;
            }
        return res;
    }
};

// int main() {
//     DoubleLive solver;
//     cout << solver.findEV(5, 2, 5);
// }