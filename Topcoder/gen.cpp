#include <bits/stdc++.h>
using namespace std;

int main() {
    srand((long long)new char + time(0));
    cout << 1 << endl;
    int n = 10, m = rand() % 10 + 1;
    cout << n << ' ' << m << endl;
    for (int i = 1, a, b, c; i <= m; i++) {
        a = rand() % n + 1, b = rand() % n + 1, c = rand() % n + 1;
        if (a > b) swap(a, b);
        cout << a << ' ' << b << ' ' << c << endl;
    }
}