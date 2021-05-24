#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0) + (long long)new char);

int main() {
    for (int T = 1; T <= 10; T++) {
        int n = 100000, m = rnd() % 1000 + 20, k = rnd() % 20 + 5;
        printf("%d %d %d\n", n, m, k);
        for (int i = 1; i <= n; i++) printf("%d ", rnd() % 50 - 10);
        puts("");
    }
    
}
