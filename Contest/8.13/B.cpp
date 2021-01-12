#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int M = 31;
const int mod = 1e9 + 7;

typedef long long LL;

int f[M][N][N], g[M][N][N], num[N];

int solveOr(int bit, int l, int r) { // 认为最低位是第一位而非第零位
    if (l > r || !bit) return 1;
    if (f[bit][l][r]) return f[bit][l][r];
    f[bit][l][r] = solveOr(bit - 1, l, r);
    for (int i = r; i >= l; i--) {
        if (num[i] >> (bit - 1) & 1) break;
        f[bit][l][r] = (f[bit][l][r] + (LL)solveOr(bit - 1, l, i - 1) * solveOr(bit - 1, i, r)) % mod;
    }
    return f[bit][l][r];
}

int solveAnd(int bit, int l, int r) {
    if (l > r || !bit) return 1;
    if (g[bit][l][r]) return g[bit][l][r];
    g[bit][l][r] = solveAnd(bit - 1, l, r);
    for (int i = r; i >= l; i--) {
        if (!(num[i] >> (bit - 1) & 1)) break;
        g[bit][l][r] = (g[bit][l][r] + (LL)solveAnd(bit - 1, l, i - 1) * solveAnd(bit - 1, i, r)) % mod;
    }
    return g[bit][l][r];
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    printf("%d\n", (LL)solveOr(m, 1, n) * solveAnd(m, 1, n) % mod);
}