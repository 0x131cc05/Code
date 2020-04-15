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
    open("data10");
    srand((LL)new char);
    int n = 500, q = 2000;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) num[i] = i;
    Random_shuffle(n);
    for (int i = 1; i <= n; i++) pos[num[i]] = i;
    for (int i = 1; i <= n; i++) printf("%d ", num[i]);
    puts("");
    for (int i = 2; i <= n; i++) printf("%d %d\n", i - 1, i);
//    for (int i = 2; i <= n; i++) printf("%d %d\n", Rand() % (i - 1) + 1, i);
    printf("\n%d\n", q);
    int tp = 1;
    for (int i = 1; i <= q; i++) {
        if (i % 200 == 0) {printf("%d %d\n", 1, n); continue; }
        if (i % 200 == 1 && i != 1) {printf("%d %d\n", 1, n); continue; }
//        printf("%d %d\n", pos[i % n + 1], i % n + 1), pos[num[i % n + 1]] = pos[i % n + 1];
//        int u = Rand() % n + 1, v = Rand() % n + 1;
//        while (u == v) v = Rand() % n + 1;
//        printf("%d %d\n", u, v);
        for (int j = 1; j < n; j++) if (num[j] == tp) {
            if (num[j] < num[j + 1]) {
                printf("%d %d\n", j, j + 1), swap(num[j], num[j + 1]);
                if (j + tp == n) tp++;
                break;
            }
        }
        
    }
}
