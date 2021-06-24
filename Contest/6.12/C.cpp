#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

int x[N], y[N];

int main() {
    int k, n, m, q; scanf("%d%d%d%d", &k, &n, &m, &q);
    if (q == 0) return 0;
    for (int i = 1; i <= k; i++) scanf("%*d%*d");
    for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
    for (int i = 1; i <= m; i++) {
        int t; scanf("%d", &t), t *= 2;
        while (t--) scanf("%*d");
    }
    while (q--) {
        int a, b; scanf("%d%d", &a, &b);
        int A = x[a] - x[b], B = y[a] - y[b];
        printf("%.10lf\n", sqrt((double)A * A + (double)B * B));
    }
}
