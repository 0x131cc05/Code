#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("number.in", "w", stdout);
    srand((long long)new char + time(0));
    int n = 30000;
    putchar('1');
    for (int i = 2; i <= n; i++) {
        putchar((rand() & 1) + '0');
    }
}