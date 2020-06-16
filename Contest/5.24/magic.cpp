#include <bits/stdc++.h>
using namespace std;

const int N = 110;

typedef long long LL;

int n;

struct Matrix {

bitset<N> G[N];

Matrix operator * (const Matrix &b) {
    Matrix res;
    for (int i = 1; i <= n; i++)
        for (int k = 1; k <= n; k++) if (G[i][k])
            res.G[i] ^= b.G[k];
    return res;
}

};

inline Matrix Pow(Matrix x, LL y) {
    Matrix res;
    for (int i = 1; i <= n; i++) res.G[i][i] = 1;
    for (; y; y >>= 1, x = x * x) if (y & 1) res = res * x;
    return res;
}

unsigned int f[N];

int main() {
//    freopen("magic.in", "r", stdin), freopen("magic.out", "w", stdout);
    int m, q; scanf("%d%d%d", &n, &m, &q); Matrix base;
    for (int i = 1; i <= n; i++) scanf("%u", &f[i]);
    for (int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b), base.G[a][b] = base.G[b][a] = 1;
    }
    while (q--) {
        unsigned int y, res = 0; scanf("%u", &y); Matrix tmp = Pow(base, y);
        for (int i = 0; i < 31; i++) {
            int t = 0;
            for (int j = 1; j <= n; j++) {
                int c = f[j] >> i & 1; t ^= c & tmp.G[j][1];
            }
            if (t) res ^= 1 << i;
        }
        printf("%u\n", res);
    }
}
