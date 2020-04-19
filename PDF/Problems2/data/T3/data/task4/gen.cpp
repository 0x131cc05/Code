#include <bits/stdc++.h>
using namespace std;

inline double Rand() {
    int t = rand() % 1000;
    return 0.1 + (double)t / 1000 * 0.9;
}

inline double small() {
    int t = rand() % 1000;
    return 0.1 + (double)t / 1000 * 0.05;
}

typedef long long LL;

inline LL Big() {
    return rand() | (LL)rand() << 16 | (LL)rand() << 32 | (LL)rand() << 48;
}

int main() {
    srand((long long)new char);
    freopen("task20.in", "w", stdout);
    int T = 50; printf("%d\n", T);
    for (int i = 1; i <= T; i++) {
        if (rand() % 10 == 1) {
            int n = rand() % 4 + 5; LL m = Big();
            printf("%d %d %.4lf\n", n, m, small());
        } else {
            int n = rand() % 4 + 5; LL m = rand() | rand() << 8;
            printf("%d %d %.4lf\n", n, m, 0.1);
        }
        
    }
}
