#include <bits/stdc++.h>
using namespace std;

int main() {
    int res = 0;
    for (int a = 0; a < 4; a++)
        for (int b = 0; b < 4; b++)
            for (int c = 0; c < 4; c++) {
                if ((a ^ b) >= 1 && (a ^ c) >= 1) res++;
//                res += min(a ^ b, a ^ c);
            }
    cout << res << endl;
}
