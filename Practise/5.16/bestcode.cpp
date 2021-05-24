#include <bits/stdc++.h>
using namespace std;

const int N = 310;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int dp1[N][N]; // a 个 1, b 个 2 匹配，边无序
int buf[1100000000 / 6], *dp2[N][N], *cur; // 下一段长度为 i，这一段有 a 个 1，b 个 2
int dp[N][N];

int frac[N], inv[N], n;

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

void init() {
    frac[0] = inv[0] = 1, cur = buf;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    dp1[0][0] = 1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j + i <= n; j++) if (i | j) {
            if (i) {
                if (i >= 2) dp1[i][j] = (dp1[i][j] + (LL)dp1[i - 2][j] * (i - 1)) % mod;
                if (j) dp1[i][j] = (dp1[i][j] + (LL)dp1[i][j - 1] * j) % mod;
            } else {
                for (int k = 3; k <= j; k++) 
                    dp1[0][j] = (dp1[0][j] + (LL)dp1[0][j - k] * C(j - 1, k - 1) % mod * frac[k - 1] % mod * inv2) % mod;
            }
        }
    for (int l = 0; l <= n; l++)
        for (int a = 0; a <= n - l; a++) 
            dp2[l][a] = cur, cur += n - l - a + 1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; i + j <= n; j++) dp2[0][i][j] = dp1[i][j];
    for (int l = 1; l <= n; l++)
        for (int s = 0; s <= n - l; s++)
            for (int b = 0; b <= s; b++) {
                int a = s - b;
                if (a) dp2[l][a][b] = (dp2[l][a][b] + (LL)dp2[l - 1][a - 1][b] * a) % mod;
                if (b) dp2[l][a][b] = (dp2[l][a][b] + (LL)dp2[l - 1][a + 1][b - 1] * b) % mod;
            }
}

int d[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &d[i]);
    init(), dp[d[1] + 1][d[1]] = 1;
    for (int i = d[1] + 2; i <= n; i++)
        for (int j = 1; j <= i - (d[1] + 1); j++) {
            int c1 = 0, c2 = 0, lst = i - j;
            for (int k = lst; k >= 1; k--) {
                d[k] == 2 ? c1++ : c2++;
                dp[i][j] = (dp[i][j] + (LL)dp[lst][lst - k + 1] * dp2[j][c1][c2]) % mod;
            }
        }
    int res = 0, c1 = 0, c2 = 0;
    for (int i = 1; i <= n; i++) {
        d[n - i + 1] == 2 ? c1++ : c2++;
        res = (res + (LL)dp[n][i] * dp1[c1][c2]) % mod;
    }
    printf("%d\n", res);
}