#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
const int mod = 1e9 + 7;

int a[N], f[N];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = 2 * f[i - 1] + 1; int nw = i;
        while (233) {
            nw = nw - a[nw], f[i]++;
            if (!nw) break;
            f[i] = ((long long)f[i] - f[nw] + f[nw - 1] + 1) % mod;
            f[i] = (f[i] + mod) % mod;
        }
    }
    printf("%d\n", f[n]);
}
