#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a, b; cin >> n >> a >> b;
    for (int a1 = 0; a1 < n; a1++)
        for (int b1 = 0; b1 < n; b1++) {
            bool flag = true;
            for (int x = 0; x < n && flag; x++)
                for (int y = 0; y < n; y++) if ((a * x + b * y) % n == 0) {
                    if ((a1 * x + b1 * y) % n) {
                        flag = false; break;
                    }
                }
            if (flag) printf("%d %d\n", a1, b1);
        }
}