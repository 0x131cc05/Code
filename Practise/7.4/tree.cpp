#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int M = 210;

typedef long long LL;

int C[M][M], g[M][1 << 15], h[M][1 << 15], ct[1 << 15];

void Dec(int &x, int y) {
    x -= y, x += x < 0 ? mod : 0;
}

int ans[M];

int main() {
    freopen("tree.in", "r", stdin), freopen("tree.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i <= m; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    for (int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        for (int s = 0; s < 1 << n; s++) 
            if ((s & (1 << a)) && (s & (1 << b)))
                ct[s]++;
    }
    g[0][0] = h[0][0] = 1;
    for (int s = 2; s < 1 << n; s += 2) {
        for (int s1 = s; s1; s1 = (s1 - 1) & s) {
            for (int j = 0; j <= ct[s ^ s1]; j++) 
                Dec(g[j + ct[s1]][s], g[j][s ^ s1]);
        }
        for (int j = 0; j <= ct[s]; j++) if (g[j][s])
            for (int k = 0; k <= j; k++) 
                h[k][s] = (h[k][s] + (LL)C[j][k] * g[j][s]) % mod;
    }
    for (int s = 1; s < 1 << n; s += 2) {
        for (int i = 0; i <= ct[s]; i++) {
            int w = C[ct[s]][i], s1 = ((1 << n) - 1) ^ s;
            for (int j = max(n - 1 - i, 0); j <= ct[s1]; j++)
                ans[i + j] = (ans[i + j] + (LL)w * h[j][s1]) % mod;
        }
    }
    for (int i = n - 1; i <= m; i++) printf("%d ", ans[i]);
}

