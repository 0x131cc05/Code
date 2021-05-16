#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int N = 1010;

typedef long long LL;

struct Matrix {
    int G[65][65];
    Matrix() { memset(G, 0, sizeof(G)); }
    int* operator [] (int x) { return G[x]; }
    Matrix operator * (Matrix b) {
        Matrix res;
        for (int i = 1; i <= 64; i++)   
            for (int j = 1; j <= 64; j++)
                for (int k = 1; k <= 64; k++)
                    res[i][j] = (res[i][j] + (LL)G[i][k] * b[k][j]) % mod;
        return res;
    }
} E, pw[31];

Matrix Pow(Matrix x, int y) {
    Matrix res = E;
    for (; y; y >>= 1, x = x * x) if (y & 1) res = res * x;
    return res;
}

int id(int a, int b, int c) {
    return c + b * 4 + a * 16 + 1;
}

int f[4][4], a[N], trans[65][4], v[N][4], dp[N][4]; map<int, int> s[N];

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    int m; scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c), s[a][b] = c;
    }
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++) scanf("%d", &f[i][j]);
    for (int a = 0; a <= 3; a++)
        for (int b = 0; b <= 3; b++)
            for (int c = 0; c <= 3; c++)
                for (int i = 1; i <= 3; i++) {
                    static int buk[4]; memset(buk, 0, sizeof(buk));
                    if (f[i][1]) buk[c] = 1;
                    if (f[i][2]) buk[b] = 1;
                    if (f[i][3]) buk[a] = 1;
                    for (int j = 0; j < 4; j++) if (!buk[j]) {
                        trans[id(a, b, c)][i] = id(b, c, j); break;
                    }
                }
    for (int i = 1; i <= 64; i++) E[i][i] = 1;
    Matrix base;
    for (int i = 1; i <= 64; i++)
        for (int j = 1; j <= 3; j++) base[i][trans[i][j]]++;
    pw[0] = base;
    for (int i = 1; i <= 30; i++) pw[i] = pw[i - 1] * pw[i - 1];
    for (int i = 1; i <= n; i++) {
        int cur = 0, nw = id(3, 3, 3); static int res[65]; memset(res, 0, sizeof(res)), res[nw] = 1;
        auto work = [&](int y) {
            for (int i = 30; i >= 0; i--) if (y & (1 << i)) {
                static int tmp[65]; memset(tmp, 0, sizeof(tmp));
                for (int j = 1; j <= 64; j++)
                    for (int k = 1; k <= 64; k++)
                        tmp[k] = (tmp[k] + (LL)res[j] * pw[i][j][k]) % mod;
                memcpy(res, tmp, sizeof(tmp));
            }
        };
        for (auto t : s[i]) {
            int at = t.first, c = t.second; work(at - cur - 1);
            cur = at; static int tmp[65]; memset(tmp, 0, sizeof(tmp));
            for (int j = 1; j <= 64; j++) 
                tmp[trans[j][c]] = (tmp[trans[j][c]] + res[j]) % mod;
            memcpy(res, tmp, sizeof(tmp));
        } 
        work(a[i] - cur);
        for (int a = 0; a <= 3; a++)
            for (int b = 0; b <= 3; b++)
                for (int c = 0; c <= 3; c++)
                    v[i][c] = (v[i][c] + res[id(a, b, c)]) % mod;
    }
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= 3; j++)
            for (int k = 0; k <= 3; k++)
                dp[i][k] = (dp[i][k] + (LL)dp[i - 1][j] * v[i][j ^ k]) % mod;
    printf("%d\n", dp[n][0]);
}