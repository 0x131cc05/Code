#include <bits/stdc++.h>
using namespace std;

int id[1 << 19];

int rnd() {
    return rand() | rand() << 16;
}

int main() {
    freopen("a.in", "w", stdout);
    srand((long long)new char + time(0));
    int n = 1 << 19;
    printf("%d %d\n", n, 0);
    for (int i = 0; i < n; i++) id[i] = i;
    for (int i = 1; i < n; i++) {
        swap(id[i], id[rnd() % i]);
    }
    for (int i = 0; i < n; i++) printf("%d ", id[i]);
}