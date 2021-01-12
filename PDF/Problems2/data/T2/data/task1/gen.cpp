#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

#define open(x) freopen(x".in", "w", stdout)

const int N = 500010;

int num[N];

inline int Rand() {
    return rand() | rand() << 16;
}

inline void Random_shuffle(int n) {
    for (int i = 2; i <= n; i++) 
        swap(num[Rand() % (i - 1) + 1], num[i]);
}

int main() {
    open("data5");
    srand((LL)new char);
    int n = 100, q = 100;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) num[i] = i;
    for (int i = 1; i <= n; i += 2) swap(num[i], num[i + 1]);
//    Random_shuffle(n);
    for (int i = 1; i <= n; i++) printf("%d ", num[i]);
    puts("");
    for (int i = 2; i <= n; i++) printf("%d %d\n", i - 1, i);
    printf("%d\n", q);
    while (q--) {
        int u = Rand() % n + 1;
        if (u % 2 == 0) u--;
        printf("%d %d\n", u, u + 1);
    }
}
