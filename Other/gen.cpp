#include <bits/stdc++.h>
using namespace std;

inline int Rand() {
    return rand() << 16 | rand();
}

int main() {
    freopen("in1.in", "w", stdout);
    int n = 250000; cout << n << ' ' << 998437288324723242 << endl;
    int tot = 0, mod = 998244353;
    for (int i = 0; i < n; i++) {
        int t = Rand() % mod; tot = (tot + t) % mod;
        cout << t << ' ';
    }
    cout << mod + 1 - tot << endl;
}
