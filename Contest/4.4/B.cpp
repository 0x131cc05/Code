#include <bits/stdc++.h>
using namespace std;

const int N = 510;
const int M = 110;
const int mod = 1e9 + 7;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int flag[N], prime[N], tot;

int G[N][N], G1[N][N], n;

inline void sieve() {
    for (int i = 2; i <= n; i++) {
        if (!flag[i]) prime[++tot] = i;
        for (int j = 1; j <= tot && i * prime[j] <= n; j++) {
            flag[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    for (int i = 1; i <= n; i++) {
        int tmp = i;
        for (int j = 1; j <= tot; j++) {
            int ct = 0;
            while (tmp % prime[j] == 0) tmp /= prime[j], ct++;
            G[j][ct]++, G1[i][prime[j]] = ct;
        }
    }
}

int dp[M][30], k, f[N][10010];

inline int if_n_is_ssssssssssssssmall() {
    if (n > 30) return 0;
    static int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    static int c[] = {5, 4, 3, 2,  2,  2,  2,  2,  2,  2};
    f[0][0] = 1;
    for (int i = 1; i <= k; i++) 
        for (int j = 0; j <= 10000; j++) if (f[i - 1][j]) {
            static int buk[20]; int tmp = j;
            for (int i = 9; i >= 0; i--) buk[i] = tmp % c[i], tmp /= c[i];
            for (int k = 1; k <= n; k++) {
                static int nw[20]; int code = 0;
                for (int l = 0; l <= 9; l++) nw[l] = max(G1[k][p[l]], buk[l]);
                for (int l = 0; l <= 9; l++) code = code * c[l] + nw[l];
                f[i][code] = (f[i][code] + f[i - 1][j]) % mod;
            }
        }
    int res = 0;
    for (int j = 0; j <= 10000; j++) if (f[k][j]) {
        static int buk[20]; int tmp = j, nw = 1;
        for (int i = 9; i >= 0; i--) buk[i] = tmp % c[i], tmp /= c[i];
        for (int i = 0; i <= 9; i++) nw = (LL)nw * Pow(p[i], buk[i]) % mod;
        res = (res + (LL)nw * f[k][j]) % mod;
    }
    return res;
}

int main() {
    int res = 1; scanf("%d%d", &n, &k), sieve();
    for (int i = 1; i <= tot; i++) {
        memset(dp, 0, sizeof(dp)), dp[0][0] = 1;
        int tp = 1;
        while (G[i][tp + 1]) tp++;
        for (int j = 1; j <= k; j++)
            for (int a = 0; a <= tp; a++)
                for (int b = 0; b <= tp; b++) 
                    dp[j][max(a, b)] = (dp[j][max(a, b)] + (LL)dp[j - 1][a] * G[i][b]) % (mod - 1);
        for (int j = 0, t = 1; j <= tp; j++, t = (LL)t * prime[i] % mod)
            res = (LL)res * Pow(t, dp[k][j]) % mod;
    }
    printf("%d %d\n", if_n_is_ssssssssssssssmall(), res);
    return 0;
}
