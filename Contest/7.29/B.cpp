#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
const int M = 510;

typedef long long LL;

int Pow(int x, int y, int mod) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
} 

int flag[M], prime[M], tot;

void sieve() {
    for (int i = 2; i <= M - 10; i++) {
        if (!flag[i]) prime[++tot] = i;
        for (int j = 1; j <= tot && i * prime[j] <= M - 10; j++) {
            flag[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

char s[N]; int h[M][N], ok[M][M], pw[M][N];

int main() {
    // freopen("ex_decode2.in", "r", stdin);
    int n; scanf("%d%s", &n, s + 1), sieve();
    for (int i = 2; i <= tot; i++) {
        int mod = prime[i]; pw[i][0] = 1;
        for (int j = 1; j <= n; j++) h[i][j] = (h[i][j - 1] * 2 + (s[j] - '0')) % mod, pw[i][j] = pw[i][j - 1] * 2 % mod;
    }
    for (int i = 2; i <= tot; i++) {
        ok[i][0] = 1; int mod = prime[i];
        for (int j = 1; j < mod; j++) if (Pow(j, (mod - 1) / 2, mod) == 1) ok[i][j] = 1;
    }
    int res = 0;
    for (int i = 1; i <= n; i++) if (s[i] == '1') {
        for (int j = i + 1; j <= n; j++) {
            bool flag = true;
            for (int k = 2; k <= tot; k++) {
                int mod = prime[k];
                int t = (h[k][j] - h[k][i - 1] * pw[k][j - i + 1] % mod + mod) % mod;
                if (!ok[k][t]) {
                    flag = false; break;
                } 
            }
            if (flag) res = max(res, j - i + 1);
        }
    }
    printf("%d\n", res);
}