#include <bits/stdc++.h>
using namespace std;

int main() {
    srand((long long)new char + time(0));
    int n = 100000, q = 100000; cout << n << ' ' << q << endl;
    for (int i = 1; i <= n; i++) cout << rand() % 20 << ' ';
    cout << endl;
    while (q--) {
        int l = rand() % n + 1, r = rand() % n + 1;
        if (l > r) swap(l, r);
        cout << l << ' ' << r << ' ' << rand() % (r - l + 1) + 1 << endl;
    }
}