#include <bits/stdc++.h>
using namespace std;

const int N = 140;
const int mod = 1e9 + 7;

typedef long long LL;

int n;

struct Matrix {
    int G[N][N];
    Matrix() { memset(G, 0, sizeof(G)); }
    int* operator[] (int i) { return G[i]; }
    Matrix operator* (Matrix b) {
        Matrix res;
       for (int i = 1; i <= n; i++)
           for (int k = 1; k <= n; k++)
               for (int j = 1; j <= n; j++)
                   res[i][j] = (res[i][j] + (LL)G[i][k] * b[k][j]) % mod;
        return res;
    }
    Matrix operator+ (Matrix b) {
        Matrix res;
       for (int i = 1; i <= n; i++)
           for (int j = 1; j <= n; j++)
               res[i][j] = (G[i][j] + b[i][j]) % mod;
        return res;
    }
} E;

Matrix Pow(Matrix x, int y) {
    Matrix res = E;
    for (; y; y >>= 1, x = x * x) if (y & 1) res = res * x;
    return res;
}

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

struct ZZH { Matrix x, y; };

ZZH solve(Matrix &A, Matrix &B, int n) {
    if (n == 1) return { B, A };
    auto tmp = solve(A, B, n / 2);
    if (n % 2 == 0) return { tmp.x * tmp.y + tmp.y * tmp.x, tmp.y * tmp.y };
    else {
        auto hh = tmp.y * tmp.y;
        return { (tmp.x * tmp.y + tmp.y * tmp.x) * A + hh * B, hh * A };
    }
}

int main() {
    int n, k, a, b; scanf("%d%d%d%d", &n, &k, &a, &b), ::n = k;
    for (int i = 1; i <= k; i++) E[i][i] = 1;
    Matrix A, B;
    for (int i = 1; i <= k; i++) {
        A[i][i - 1] = A[i][i] = A[i][i + 1] = 1;
        if (a < i && i < b) B[i][i] = 1;
    }
    Matrix res = A * solve(A, B, n - 2).x * A;
    printf("%lld\n", (LL)res[k / 2][k / 2] * Pow(n - 2, mod - 2) % mod);
    return 0;
}