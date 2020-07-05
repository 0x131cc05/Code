#include <bits/stdc++.h>
using namespace std;

const int n = 80, m = 300;

typedef long long LL;

inline LL rnd() {
    return rand() | rand() << 16 | (LL)rand() << 32;
}

int main() {
    freopen("in.in", "w", stdout);
    srand((long long)new char + time(0));
    cout << n << endl;
    for (int i = 1; i <= n; i++)
        printf("%d %d %lld\n", rand() % 100 + 1, rand() % 100 + 1, rnd());
    cout << m << endl;
    for (int i = 1; i <= m; i++) {
        int t = rand() % 4;
        if (t == 0) printf("L ");
        else if (t == 1) printf("R ");
        else if (t == 2) printf("U ");
        else printf("D ");
        printf("%d %d\n", rand() % 100 + 1, rand() % n);
    }
}
