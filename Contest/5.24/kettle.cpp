#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

int num[N];

int main() {
    freopen("kettle.in", "r", stdin), freopen("kettle.out", "w", stdout);
    int n, k; scanf("%d%d", &n, &k); int res = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &num[i]), num[i] += num[i - 1];
        res = max(res, num[i] - num[max(0, i - k - 1)]);
    }
    printf("%d\n", res);
}
