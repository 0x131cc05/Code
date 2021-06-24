#include <bits/stdc++.h>
using namespace std;

const int N = 45;
const int M = 2010;
const int mod = 1e9 + 9;
const int inv2 = (mod + 1) / 2;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int frac[M], inv[M];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int calc(int a, int b) {
    return C(a + b + 1, a + 1);
}

int calc(int a, int b, int c) {
    int res = (LL)calc(a + b, c) * C(a + b, a) % mod;
    int A = a & 1, B = b & 1;
    if (A && B) return (LL)res * inv2 % mod;
    int w = C((a + b) / 2, a / 2);
    res = (res + (LL)calc((a + b) / 2, c / 2) * w) % mod;
    if (c && (!A && !B)) res = (res + (LL)calc((a + b) / 2, (c - 1) / 2) * w) % mod;
    return (LL)res * inv2 % mod;
}

int ct[3][N][N], id[127];

int get(int id, int x1, int y1, int x2, int y2) {
    if (x1 > x2 || y1 > y2) return 0;
    return ct[id][x2][y2] - ct[id][x1 - 1][y2] - ct[id][x2][y1 - 1] + ct[id][x1 - 1][y1 - 1];
}

int mxB[M][M], ok[M][M];

struct ColorfulJewelry {
    int getChains(vector<string> G, int K) {
        id['R'] = 0, id['G'] = 1, id['B'] = 2;
        int n = G.size(), m = G[0].size(), lim = n * m;
        frac[0] = inv[0] = 1;
        for (int i = 1; i <= lim + 1; i++) frac[i] = (LL)frac[i - 1] * i % mod;
        inv[lim + 1] = Pow(frac[lim + 1], mod - 2);
        for (int i = lim; i >= 1; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % mod;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                for (int k = 0; k < 3; k++) 
                    ct[k][i][j] = ct[k][i - 1][j] + ct[k][i][j - 1] - ct[k][i - 1][j - 1];
                ct[id[(int)G[i - 1][j - 1]]][i][j]++;
            }
        auto count = [&](int id, int i, int j) {
            int ti = min(n, i + K - 1), tj = min(m, j + K - 1);
            return get(id, i, j, ti, tj);
        };
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                for (int k = i; k <= n; k++)
                    for (int l = 1; l <= m; l++) {
                        int tmp[3] = { 0, 0, 0 };
                        for (int t = 0; t < 3; t++) 
                            tmp[t] = count(t, i, j) + count(t, k, l) - get(t, k, max(j, l), min(n, i + K - 1), min(m, min(j, l) + K - 1));
                        mxB[tmp[0]][tmp[1]] = max(mxB[tmp[0]][tmp[1]], tmp[2]), ok[tmp[0]][tmp[1]] = 1;
                    }
        int res = 0;
        for (int i = lim; i >= 0; i--)
            for (int j = lim - i; j >= 0; j--) {
                mxB[i][j] = max(mxB[i][j], mxB[i + 1][j]);
                mxB[i][j] = max(mxB[i][j], mxB[i][j + 1]);
                ok[i][j] |= ok[i + 1][j] | ok[i][j + 1];
                if (ok[i][j]) res = (res + calc(i, j, mxB[i][j])) % mod;
            }
        return (res + mod - 1) % mod;
    }
};

// int main() {
//     ColorfulJewelry solver;
//     cout << solver.getChains(	{"BBGRRGR", "GRGGBBB", "BRRGBGB", "GGGGBBG", "RGRGGGG", "GRGGRGG", "BBGRRGR"}, 4);
// }