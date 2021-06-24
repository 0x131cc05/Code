#include <bits/stdc++.h>
using namespace std;

mt19937 rnd((long long)new char + time(0));

int nxt() {
    return rnd() % 1000000000;
}

int main() {
    freopen("in.in", "w", stdout);
    int n = 100000, m = 100000, k = 10;
    printf("%d %d %d\n", n, m, k);
    for (int i = 1; i <= n + m; i++) {
        printf("%d %d\n", 1, 1);
    }
}