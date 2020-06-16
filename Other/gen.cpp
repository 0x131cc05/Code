#include <bits/stdc++.h>
using namespace std;

const int n = 10;

char A[11], B[11];

int main() {
    freopen("in.in", "w", stdout);
    srand((long long)new char + time(0));
    cout << 1 << endl;
    cout << n << endl;
    for (int i = 2; i <= n; i++)
        printf("%d %d\n", rand() % (i - 1) + 1, i);
    for (int i = 2; i <= n; i++)
        printf("%d %d\n", rand() % (i - 1) + 1, i);
}
