#include <bits/stdc++.h>
using namespace std;

int main() {
    srand((long long)new char + time(0));
    for (int i = 1; i <= 5; i++) putchar('a' + rand() % 3);
    cout << endl;
    cout << 10 << endl;
    for (int i = 1; i <= 10; i++) {
        printf("%d %d\n", rand() % 100 + 1, rand() % 10 + 1);
    }
}
