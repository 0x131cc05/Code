#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int mod = 1e9 + 7;

inline void Inc(int &x, int y = 0) {x += y, x -= x >= mod ? mod : 0;}
inline void Dec(int &x, int y = 0) {x -= y, x += x < 0 ? mod : 0;}
inline int Add(int x, int y) {x += y; return x >= mod ? x - mod : x;}
inline int Sub(int x, int y) {x -= y; return x < 0 ? x + mod : x;}

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

template<class T> inline void read(T &x) {
    x = 0; char c = getchar(); int flg = 0;
    while (!isdigit(c)) flg |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (flg) x = -x;
}

template<class T> inline void print(T x) {
    x < 10 ? putchar('0' + x) : (print(x / 10), putchar('0' + x % 10));
}

const int N = 1510;
const int M = 100010;

int frac[M], inv[M];

inline int C(int n, int r) {
    if (n < r) return 0;
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int P[M], P1[M], dp[N][N], sum[N], sum1[N];

int main() {
    int n, m, a, b, t; read(n), read(m), read(a), read(b), read(t);
    frac[0] = inv[0] = 1;
    for (int i = 1; i <= t; i++) frac[i] = (LL)frac[i - 1] * i % mod;
    inv[t] = Pow(frac[t], mod - 2);
    for (int i = t - 1; i >= 1; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % mod;
    int p = (LL)a * Pow(b, mod - 2) % mod, p1 = mod + 1 - p;
    for (int i = 0; i <= t; i++) 
        P[i] = (LL)C(t, i) * Pow(p, i) % mod * Pow(p1, t - i) % mod;
    P1[0] = P[0];
    for (int i = 1; i <= m; i++) P1[i] = Add(P1[i - 1], P[i]);
    dp[0][m] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) sum[j] = Add(sum[j - 1], dp[i - 1][j]);
        for (int j = 1; j <= m; j++) sum1[j] = Add(sum1[j - 1], (LL)sum[j] * P[j] % mod);
        for (int j = 1; j <= m; j++) {
            dp[i][j] = Sub((LL)P1[j - 1] * Sub(sum[m], sum[m - j]) % mod, sum1[j - 1]);
            dp[i][j] = (LL)dp[i][j] * P[m - j] % mod;
        }
    }
    int res = 0;
    for (int i = 1; i <= m; i++) Inc(res, dp[n][i]);
    printf("%d\n", res);
}