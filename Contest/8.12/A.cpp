#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
    LL c; cin >> c;
    if (c <= 100) {
        cout << 2 << ' ' << c << endl;
        for (int i = 1; i <= c; i++) cout << 2 << ' ' << 1 << endl;
    } else {
        int k = 0;
        while (c) c >>= 1, k++;
        cout << k << ' ' << 2 * (k - 1) << endl;
        for (int i = 1; i < k; i++)
            for (int t = 0; t <= 1; t++) 
                cout << i + 1 << ' ' << i << endl;
    }
}
