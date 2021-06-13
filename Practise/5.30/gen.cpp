#include <bits/stdc++.h>
using namespace std;

mt19937 rnd((long long)new char + time(0));

int main() {
    int T = 1000;
    printf("%d\n", T);
    while (T--) {
        int n = rnd() % 400 + 100, m = rnd() % n + 1;
        printf("%d %d\n", n, m);
    }
}