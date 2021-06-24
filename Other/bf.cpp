#include <bits/stdc++.h>
using namespace std;

int m;

int F(int x) {
    if (x == 1) return 0;
    return x % m ? F(x + 1) + 1 : F(x / m) + 1;
}

int main() {
    int n; cin >> m >> n;
    for (int i = 1; i <= 1000; i++) if (F(i) == n) {
        cout << i << endl;
    }
}