#include <bits/stdc++.h>
using namespace std;

inline double Rand() {
    int t = rand() % 1000;
    return 0.1 + (double)t / 1000 * 0.9;
}

int main() {
    srand((long long)new char);
    freopen("task15.in", "w", stdout);
    int T = 50; printf("%d\n", T);
    for (int i = 1; i <= T; i++) {
        int n = rand() % 4 + 5, m = rand() % 11 + 40;
        printf("%d %d %.4lf\n", n, m, Rand());
    }
}
