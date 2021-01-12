#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("in.in", "w", stdout);
    int n = 599999, m = n - 1;
    printf("%d %d\n", n, m);
    for (int i = n / 2 + 1; i <= n; i++) printf("%d %d\n", n / 2 - 1, i - 1);
    for (int i = 1; i < n / 2; i++) printf("%d %d\n", i - 1, i);
}