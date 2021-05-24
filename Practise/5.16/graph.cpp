#include <bits/stdc++.h>
using namespace std;

const int N = 310;
const int mod = 1e9 + 7;

typedef long long LL;

int dp[N * 2][N], g[N][N][N * 2], C[N * 2][N * 2], frac[N], num[N], ct2[N], ct3[N];

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int main() {
    // freopen("graph.in", "r", stdin), freopen("graph.out", "w", stdout);
    int n; scanf("%d", &n), frac[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &num[i]), ct2[i] = ct2[i - 1], ct3[i] = ct3[i - 1];
        if (num[i] == 2) ct2[i]++;
        else ct3[i]++;
    } 
    int st = clock();
    for (int i = 0; i <= n * 2; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) 
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }   
    dp[num[1]][1] = 1;
    g[0][0][0] = 1;
    for (int s = 1; s <= n; s++)
        for (int i = 0; i <= s; i++) {
            int j = s - i;
            for (int k = max(2 * s + i - n, 0); k <= i + j * 2 && s + k <= n; k++) {
                if (i) g[i][j][k] = g[i - 1][j][k];
                else if (j) g[i][j][k] = g[i][j - 1][k];
                if (i && k) {
                    if (i >= 2) Inc(g[i][j][k], (LL)g[i - 2][j][k - 1] * (i - 1) % mod);
                    if (j) Inc(g[i][j][k], (LL)g[i][j - 1][k - 1] * j * 2 % mod); 
                } else {
                    if (j >= 2 && k) Inc(g[i][j][k], (LL)g[i + 1][j - 2][k - 1] * (j - 1) * 4 % mod);
                    if (j >= 3 && k >= 2) Inc(g[i][j][k], (LL)g[i + 2][j - 3][k - 2] * (j - 1) % mod * (j - 2) % mod * 4 % mod);
                }
            }
        }
    // cout << "end" << endl;
    for (int i = 1; i < n; i++)
        for (int j = 0; j <= i * 2 && i + j <= n; j++) if (dp[j][i]) {
            int tmp = 1;
            for (int k = i + 1; k <= n && k - i <= j; k++) {
                tmp = (LL)tmp * num[k] % mod;
                int r = j - (k - i), a = ct2[k] - ct2[i], b = ct3[k] - ct3[i], t = b * 2 + a;
                if (r) continue;
                int w = (LL)dp[j][i] * frac[k - i] % mod * tmp % mod;
                for (int l = 0; l * 2 <= t; l++) {
                    Inc(dp[t - l * 2][k], (LL)w * g[a][b][l] % mod);
                }
                break;
            }
        }
    int res = dp[0][n], inv2 = (mod + 1) / 2, inv3 = (mod + 1) / 6;
    for (int i = 1; i <= n; i++) {
        if (num[i] == 2) res = (LL)res * inv2 % mod;
        else if (num[i] == 3) res = (LL)res * inv3 % mod;
    }
    printf("%d\n", res);
    // cout << clock() - st << endl;
}