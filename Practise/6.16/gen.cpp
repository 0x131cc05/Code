#include <bits/stdc++.h>
using namespace std;

mt19937 rnd((long long)new char + time(0));

int main() {
//    freopen("in.in", "w", stdout);
    int n = rnd() % 500 + 100, k = rnd() % 200 + 10;
    cout << n << ' ' << k << endl;
    for (int i = 1; i <= n; i++) printf("%d ", rnd() % 1000);
}
