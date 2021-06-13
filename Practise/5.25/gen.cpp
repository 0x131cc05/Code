#include <bits/stdc++.h>
using namespace std;

mt19937 rnd((long long)new char + time(0));

int main() {
    int n = 1000, q = 1000;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) printf("%d ", rnd() % 3);
    printf("\n%d\n", q);
    for (int i = 1; i <= q; i++) {
        int op = rnd() % 2 + 1, a = rnd() % n + 1;
        if (op == 1) {
            int b = rnd() % 3;
            printf("%d %d %d\n", op, a, b);
        } else {
            int b = rnd() % n + 1;
            if (a > b) swap(a, b);
            printf("%d %d %d\n", op, a, b);
        }
    }
}
