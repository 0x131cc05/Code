#include <bits/stdc++.h>
using namespace std;

int id[10010], n = 10;

int main() {
    freopen("in1.in", "w", stdout);
    cout << n << endl, srand((long long)new char);
//    for (int i = 2; i <= n; i++) cout << rand() % (i - 1) + 1 << ' ' << i << endl;
    cout << "2 3\n1 2\n7 8\n5 3\n6 2\n9 7\n9 4\n9 2\n10 4\n";
    cout << 40000 << endl;
    for (int i = 1; i <= n; i++) id[i] = i;
    for (int i = 1; i <= 40000; i++) {
        random_shuffle(id + 1, id + n + 1);
        int k = rand() % 10 + 1; cout << k << ' ' << 5 << endl;
        for (int j = 1; j <= k; j++) cout << id[j] << ' ' << rand() % 3 + 1 << endl;
        random_shuffle(id + 1, id + n + 1);
        for (int j = 1; j <= 5; j++) cout << id[j] << ' ';
        puts("");
    }
}
