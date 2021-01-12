#include <bits/stdc++.h>
using namespace std;

int f[25], ans[1000010], sum[1 << 24];

int main() {
    f[1] = 1, f[2] = 2;
    for (int i = 3; i <= 24; i++) f[i] = f[i - 1] + f[i - 2];
    for (int i = 1; i < 1 << 24; i++) {
        sum[i] = sum[i ^ (i & -i)];
        sum[i] += f[__builtin_ctz(i) + 1];
        ans[sum[i]]++;
    }
    int n, t = 0; scanf("%d", &n);
    for (int i = 1, a; i <= n; i++) scanf("%d", &a), t += f[a], printf("%d\n", ans[t]);
}
