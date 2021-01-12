#include <bits/stdc++.h>
using namespace std;

int id[5010]; char s[5010];

int main() {
    freopen("match.in", "w", stdout);
    srand((long long)new char);
    int n = 5000; cout << n << endl;
    for (int i = 1; i <= n; i++) 
        id[i] = i, s[i] = '0';
    random_shuffle(id + 1, id + n + 1);
    for (int i = 1; i <= n / 2; i++) s[i] = '1';
    for (int i = 1; i <= n; i++) cout << s[i];
    cout << endl;
    for (int i = 2; i <= n; i++) cout << rand() % (i - 1) + 1 << ' ' << i << endl;
}
