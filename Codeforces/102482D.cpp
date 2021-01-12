#include <bits/stdc++.h>
using namespace std;

const int N = 510;

double f[N][N], g[N][N], C[N * 2][N * 2];

int main() {
    int n, d, r; cin >> n >> d >> r;
    f[0][n] = 1;
    for (int i = 0; i <= (N - 10) * 2; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    for (int i = 0; i < d; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= j && k + i <= d; k++) {
                f[i + k][k] += C[j][k] * f[i][j];
                g[i + k][k] += C[j][k] * (g[i][j] + min(k, r) * f[i][j]);
            }
    double res = 0;
    for (int i = 1; i <= n; i++) res += g[d][i];
    printf("%.6lf\n", res / C[n + d - 1][d] + r);
}