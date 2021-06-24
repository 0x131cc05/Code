#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
    LL cur = 1, k = 1; LL ct = 0;
    while (233) {
        LL tmp = cur;
        ct += k;
        while (tmp) {
            if (tmp % 10 == 0) ct--;
            tmp /= 10;
        }
        if (ct < 0) {
            cout << cur;
            return 0;
        }
        cur++;

    }
    cout << cur << endl;
}