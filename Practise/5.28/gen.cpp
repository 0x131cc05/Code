#include <bits/stdc++.h>
using namespace std;

mt19937 rnd((long long)new char + time(0));

int main() {
    // freopen("in.in", "w", stdout);
    int n = 10, q = 10;
    printf("%d %d\n", n, q);
    for (int i = 1; i <= n; i++) printf("%d ", rnd() % 100000 + 1);
    puts("");
    for (int i = 1; i <= q; i++) 
        printf("%d %d\n", rnd() % n, rnd() % n);
}