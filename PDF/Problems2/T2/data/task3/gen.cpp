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
    open("data15");
    srand((LL)new char);
    int n = 500000, q = 500000;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) num[i] = i;
    Random_shuffle(n);
    for (int i = 1; i <= n; i++) pos[num[i]] = i;
    for (int i = 1; i <= n; i++) printf("%d ", num[i]);
    puts("");
    for (int i = 2; i <= n; i++) printf("%d %d\n", i - 1, i);
//    for (int i = 2; i <= n; i++) printf("%d %d\n", Rand() % (i - 1) + 1, i);
    printf("%d\n", q);
    for (int i = 1; i <= 10; i++) printf("%d %d\n", pos[i], i), pos[num[i]] = pos[i];
    int tp = 1;
    for (int i = 11; i <= q; i++) {
//        printf("%d %d\n", i, n - i + 1);
//        if (i % 200 == 0) {printf("%d %d\n", 1, n); continue; }
//        if (i % 200 == 1 && i != 1) {printf("%d %d\n", 1, n); continue; }
//        printf("%d %d\n", pos[i], i), pos[num[i]] = pos[i];
        int u = Rand() % 10 + 1, v = Rand() % 10 + 1;
        while (u == v) v = Rand() % 10 + 1;
        printf("%d %d\n", u, v);
//        for (int j = 1; j < n; j++) if (num[j] == tp) {
//            if (num[j] < num[j + 1]) {
//                printf("%d %d\n", j, j + 1), swap(num[j], num[j + 1]);
//                if (j + tp == n) tp++;
//                break;
//            }
//        }
        
    }
}
