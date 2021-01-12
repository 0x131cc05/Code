#include <bits/stdc++.h>
using namespace std;

const int N = 60;
const int M = 210;
const int mod = 1e9 + 7;

typedef long long LL;

int dp[M][N][N], ed[M], st[M], L1[M], R1[M];

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int frac[N], inv[N];

class TaroCheckers {
public:
    int getNumber(vector<int> L, vector<int> R, int m) {
        int n = L.size();
        frac[0] = inv[0] = 1;
        for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= L[i - 1]; j++) L1[j]++;
            for (int j = m; j >= m - R[i - 1] + 1; j--) R1[j]++; 
            ed[L[i - 1]]++, st[m - R[i - 1] + 1]++;
        }
        dp[0][0][0] = 1;
        for (int i = 1; i <= m; i++) {
            static int g[N][N]; memset(g, 0, sizeof(g));
            for (int j = 0; j <= L1[i]; j++)
                for (int k = 0; k + j <= n; k++) if (dp[i - 1][j][k]) {
                    if (j < L1[i]) Inc(g[j + 1][k + st[i]], dp[i - 1][j][k]);
                    Inc(g[j][k + st[i]], dp[i - 1][j][k]);
                    if (k + st[i]) Inc(g[j][k + st[i] - 1], (LL)dp[i - 1][j][k] * (k + st[i]) % mod);
                    Inc(g[j][k + st[i]], (LL)dp[i - 1][j][k] * (n - L1[i] - R1[i]) % mod);
                }
            for (int j = ed[i]; j <= L1[i]; j++)
                for (int k = 0; k + j <= n; k++) if (g[j][k]) 
                    dp[i][j - ed[i]][k] = (LL)g[j][k] * frac[j] % mod * inv[j - ed[i]] % mod;
        }
        return dp[m][0][0];
    }
};

// int main() {
//     TaroCheckers solver;
//     cout << solver.getNumber({21, 99, 87, 12, 138, 16, 78, 36, 98, 40, 57, 10, 61, 100, 8, 110, 96, 9, 69, 110, 14, 71}
// ,{83, 8, 25, 169, 1, 89, 109, 89, 19, 112, 39, 112, 87, 66, 116, 16, 41, 97, 52, 70, 111, 23}
// ,190) << endl;
// }