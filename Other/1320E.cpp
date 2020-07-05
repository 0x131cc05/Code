#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;

double s[410][110], c[110]; int n, m;

inline void pivot(int x, int y) {
    double tmp = s[y][x]; s[y][x] = -1;
    for (int i = 1; i <= n + 1; i++) s[y][i] /= -tmp;
    for (int i = 1; i <= m; i++) if (i != y) {
        tmp = s[i][x], s[i][x] = 0;
        if (-eps < tmp && tmp < eps) continue;
        for (int j = 1; j <= n + 1; j++) s[i][j] += s[y][j] * tmp;
    }
    tmp = c[x], c[x] = 0;
    for (int i = 1; i <= n + 1; i++) c[i] += s[y][i] * tmp;
}

inline double LP() {
    for (int cur = 0, pos = 0; ; pivot(cur, pos), pos = cur = 0) {
        for (int i = 1; i <= n; i++) if (c[i] > eps) cur = i;
        if (!cur) return c[n + 1];
        double mn = 1e100;
        for (int i = 1; i <= m; i++) if (s[i][cur] < -eps) {
            double tmp = s[i][n + 1] / -s[i][cur];
            if (tmp < mn) mn = tmp, pos = i;
        }
        if (!pos) return 1e100;
    }
}

int x[110], y[110];

int main() {
    int n, tp = 0; scanf("%d", &n);
    for (int i = 1; i <= n; i++) 
        scanf("%d%d%lf", &x[i], &y[i], &c[i]), s[++tp][i] = -1, s[tp][n + 1] = 1;
    int m; scanf("%d", &m);
    while (m--) {
        char st[5]; int a, b; scanf("%s%d%d", st + 1, &a, &b), tp++, s[tp][n + 1] = b;
        if (st[1] == 'L') {
            for (int i = 1; i <= n; i++) if (x[i] <= a) s[tp][i] = -1;
        } else if (st[1] == 'R') {
            for (int i = 1; i <= n; i++) if (x[i] >= a) s[tp][i] = -1;
        } else if (st[1] == 'D') {
            for (int i = 1; i <= n; i++) if (y[i] <= a) s[tp][i] = -1;
        } else for (int i = 1; i <= n; i++) if (y[i] >= a) s[tp][i] = -1;
    }
    ::m = tp, ::n = n, printf("%lld\n", (long long)(LP() + 0.5));
    for (int i = 1; i <= tp; i++) cout << s[i][n + 1] << ' ';
    cout << endl; 
}

