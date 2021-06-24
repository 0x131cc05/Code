#include <bits/stdc++.h>
using namespace std;

mt19937 rnd((long long)new char + time(0));

int main() {
    int n = rnd() % 500 + 1, k = rnd() % n + 1;
    printf("%d %d\n", n, k);
    for (int i = 1; i <= n; i++) {
        printf("%d ", rnd() % 60000 - 30000);
    }
}