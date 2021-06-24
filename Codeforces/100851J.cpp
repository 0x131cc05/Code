#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

int n, flip[N];

bool check(vector<int> &num) {
    for (auto t : num) cout << t;
    cout << endl;
    int t; cin >> t;
    if (t == n) exit(0);
    return t == n / 2;
}

int main() {
    cin >> n; vector<int> num(n);
    while (!check(num)) 
        for (auto &t : num) t = rand() & 1;
    for (int i = 2; i <= n; i++) 
        num[0] ^= 1, num[i - 1] ^= 1, flip[i] = check(num), num[0] ^= 1, num[i - 1] ^= 1;
    for (int i = 2; i <= n; i++) num[i - 1] ^= flip[i];
    check(num);
    for (int i = 1; i <= n; i++) num[i - 1] ^= 1;
    check(num); 
}
