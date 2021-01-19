#include <bits/stdc++.h>
using namespace std;

int main() {
    srand((long long)new char + time(0));
    double res = 0;
    for (int i = 1; i <= 1000000; i++) {
        double A = rand() / 32767., B = rand() / 32767., C = rand() / 32767., E = (A + B + C) / 3;
        res += (A - E) * (A - E) + (B - E) * (B - E) + (C - E) * (C - E);
    }
    cout << res / 1000000 << endl;
    cout << 2. / 12 << endl;
}
