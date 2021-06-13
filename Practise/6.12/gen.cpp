#include <bits/stdc++.h>
using namespace std;

mt19937 rnd((long long)new char + time(0));

int main() {
    int n = 1000, q = 1000;
    printf("%d %d\n", n, q);
    for (int i = 1; i <= n; i++) printf("%d ", rnd() % 20000 - 10000);
    puts("");
    while (q--) {
        int l = rnd() % n + 1, r = rnd() % n + 1;
        if (l > r) swap(l, r);
        printf("%d %d %d\n", l, r, rnd() % (r - l + 1) + 1);
    }
}
