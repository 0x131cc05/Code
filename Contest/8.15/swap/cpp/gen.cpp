#include <bits/stdc++.h>
using namespace std;

void push(int u, int v, int w) {
    printf("%d %d %d\n", u - 1, v - 1, w);
}

int main() {
    srand((long long)new char + time(0));
    int n = 10, m = 15, q = 10;
    printf("%d %d\n", n, m);
    for (int i = 2; i <= n; i++) push(rand() % (i - 1) + 1, i, rand() % 5 + 1);
    for (int i = n; i <= m; i++) {
        int u = rand() % n + 1, v = rand() % n + 1;
        while (u == v) v = rand() % n + 1;
        push(u, v, rand() % 5 + 1);
    }
    printf("%d\n", q);
    for (int i = 1; i <= q; i++) {
        int u = rand() % n + 1, v = rand() % n + 1;
        while (u == v) v = rand() % n + 1;
        printf("%d %d\n", u - 1, v - 1);
    }
}
