#include <bits/stdc++.h>
using namespace std;

mt19937 rnd((long long)new char + time(0));

int main() {
    // freopen("sa.in", "w", stdout);
    int n = 1000, m = rnd() % 1000;
    printf("%d %d\n", n, m);
    for (int i = 1; i <= m; i++) {
        int op = rnd() % 2, l = rnd() % n + 1, r = rnd() % n + 1;
        if (l > r) swap(l, r);
        printf("%d %d %d\n", op, l, r);
    }
}