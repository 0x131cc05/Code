#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int num[21];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    int res = 0;
    for (int s = 0; s < 1 << n; s++) {
        LL tmp = 0; int mn = 1e9;
        for (int i = 1; i <= n; i++) {
            if (s & (1 << i - 1)) tmp += num[i];
            else mn = min(mn, num[i]);
        }
        if (tmp < m && tmp + mn >= m) res++;
    }
    printf("%d\n", res);
}