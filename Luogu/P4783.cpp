#include <bits/stdc++.h>
using namespace std;

const int N = 410;
const int mod = 1e9 + 7;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int n;

struct Matrix {

int a[N][N];

Matrix() { memset(a, 0, sizeof(a)); }

int* operator[] (int x) { return a[x]; }

void swap(int i, int j) { ::swap(a[i], a[j]); }

void update(int x, int y, int k) { // a[y] -= a[x] * k
    for (int i = 1; i <= n; i++) 
        a[y][i] = (a[y][i] - (LL)a[x][i] * k % mod + mod) % mod;
}

};

inline Matrix inv(Matrix G) {
    Matrix res;
    for (int i = 1; i <= n; i++) res[i][i] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) if (G[j][i]) {
            G.swap(i, j), res.swap(i, j); break;
        }
        if (!G[i][i]) puts("No Solution"), exit(0);
        int tmp = Pow(G[i][i], mod - 2);
        for (int j = i + 1; j <= n; j++) if (G[j][i]) {
            int w = (LL)G[j][i] * tmp % mod;
            G.update(i, j, w), res.update(i, j, w);
        }
    }
    for (int i = n; i >= 1; i--) {
        int tmp = Pow(G[i][i], mod - 2);
        for (int j = 1; j <= n; j++) res[i][j] = (LL)res[i][j] * tmp % mod;
        for (int j = i - 1; j >= 1; j--) if (G[j][i]) 
            res.update(i, j, G[j][i]);
    }
    return res;
}

int main() {
    scanf("%d", &n); Matrix G;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) scanf("%d", &G[i][j]);
    G = inv(G);
    for (int i = 1; i <= n; i++, puts(""))
        for (int j = 1; j <= n; j++) printf("%d ", G[i][j]);
}