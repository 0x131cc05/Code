#include <bits/stdc++.h>
using namespace std;

inline double Rand() {
    int t = rand() % 1000;
    return 0.1 + (double)t / 1000 * 0.9;
}

int main() {
    srand((long long)new char);
    freopen("task5.in", "w", stdout);
    int T = 50; printf("%d\n", T);
    for (int i = 1; i <= T; i++) {
        printf("%d %lld %.4lf\n", 2, 2ll, Rand());
    }
}
