#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const long double eps = 1e-4;

long double G[N][N];

int gauss(int n) {
    int ct = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) if (fabs(G[j][i]) > eps) {
            swap(G[i], G[j]); break;
        } 
        if (fabs(G[i][i]) < eps) continue;
        ct++;
        for (int j = i + 1; j <= n; j++) if (fabs(G[j][i]) > eps) {
            long double d = G[j][i] / G[i][i];
            for (int k = 1; k <= n; k++) G[j][k] -= d * G[i][k];
        }
    }
    return ct;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int a; scanf("%d", &a), G[i][j] = a;
        }
    printf("%d\n", gauss(max(n, m)));
}