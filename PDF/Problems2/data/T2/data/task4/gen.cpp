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

int pos[N];

int main() {
    open("data20");
    srand((LL)new char);
    int n = 500000, q = 500000;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) num[i] = i;
//    Random_shuffle(n);
//    for (int i = 1; i <= n; i++) pos[num[i]] = i;
    for (int i = 1; i <= n; i++) printf("%d ", num[i]);
    puts("");
//    for (int i = 2; i <= n; i++) printf("%d %d\n", i - 1, i);
    printf("%d %d\n", 1, n);
    for (int i = 2; i < n; i++) printf("%d %d\n", max(1, i - 2), i);
//    for (int i = 2; i <= n; i++) printf("%d %d\n", Rand() % (i - 1) + 1, i);
    printf("%d\n", q);
//    for (int i = 1; i <= 10; i++) printf("%d %d\n", pos[i], i), pos[num[i]] = pos[i];
//    int tp = 1;
    for (int i = 1; i <= q; i++) {
        int t = Rand() % (n - 1) + 1;
        if (t & 1) t++; if (t > n) t -= 2;
        if (t + 2 > n || (rand() & 1)) printf("%d %d\n", t - 1, t);
        else printf("%d %d\n", t + 2, t);
    }
}
