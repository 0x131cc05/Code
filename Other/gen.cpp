#include <bits/stdc++.h>
using namespace std;

const int n = 80, m = 300;

typedef long long LL;

inline LL rnd() {
    return rand() | rand() << 16 | (LL)rand() << 32;
}

int main() {
//    freopen("in.in", "w", stdout);
    srand((long long)new char + time(0));
    puts("1");
    int mod = 17;
    printf("%d %d %d %d %d %d %d 10000\n", rand() % mod, rand() % mod, rand() % mod, rand() % mod, rand() % mod, mod, rand() % mod);
    for (int i = 1; i <= 10000; i++) {
        LL l = rnd() + 1, r = rnd() + 1;
        if (l > r) swap(l, r);
        printf("%lld %lld\n", l, r);
    }
}
