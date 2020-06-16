#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
    int n, d, m, op; scanf("%d%d%d%d", &n, &d, &m, &op);
    if (op == 0) {
        if (d >= 2) printf("%d\n", 1 % m);
        else if (n <= 2) printf("%d\n", 1 % m);
        else puts("0");
    } else {
        if (d == 1) return printf("%d\n", (n <= 2) % m), 0;
        int res = 1 % m;
        for (int i = 1; i <= n - 1; i++) res = res * 2 % m;
        printf("%d\n", (res + m - 1) % m);
    }
}
