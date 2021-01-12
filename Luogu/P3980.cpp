#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;

double s[10010][1010], c[1010]; int n, m;

inline void pivot(int x, int y) {
    double tmp = s[y][x]; s[y][x] = -1;
    for (int i = 1; i <= n + 1; i++) s[y][i] /= -tmp;
    for (int i = 1; i <= m; i++) if (i != y) {
        tmp = s[i][x], s[i][x] = 0;
        if (-eps <= tmp && tmp <= eps) continue;
        for (int j = 1; j <= n + 1; j++) s[i][j] += s[y][j] * tmp;
    }
    tmp = c[x], c[x] = 0;
    for (int j = 1; j <= n + 1; j++) c[j] += s[y][j] * tmp;
}

inline double LP() {
    for (int pos = 0, cur = 0; ; pivot(pos, cur), pos = cur = 0) { // 第 cur 个方程，第 pos 个变量
        for (int i = 1; i <= n; i++) if (c[i] > eps) pos = i;
        if (!pos) return c[n + 1];
        double mn = 1e100;
        for (int i = 1; i <= m; i++) if (s[i][pos] < -eps) {
            double t = s[i][n + 1] / -s[i][pos];
            if (t < mn) mn = t, cur = i;
        }
        if (!cur) return 1e100;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lf", &c[i]);
    for (int i = 1; i <= m; i++) {
        int l, r, a; scanf("%d%d%d", &l, &r, &a), s[i][n + 1] = a;
        for (int j = l; j <= r; j++) s[i][j] = -1;
    }
    printf("%d\n", (int)(LP() + 0.5));
}