#include <bits/stdc++.h>
using namespace std;

inline double Rand() {
    int t = rand() % 1000;
    return 0.1 + (double)t / 1000 * 0.9;
}

int main() {
    srand((long long)new char);
    freopen("task10.in", "w", stdout);
    int T = 1; printf("%d\n", T);
    for (int i = 1; i <= T; i++) {
        int n = rand() % 2 + 3, m = rand() % 2 + 3;
        printf("%d %d %.4lf\n", n, m, Rand());
    }
}
