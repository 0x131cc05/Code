#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

bool chk(int x) {
    for (int i = 2; i * i <= x; i++) 
        if (x % i == 0) return false;
    return true;
}

set<int> s;

int rnd() {
    return rand() | (rand() << 16);
}

int main() {
    srand((LL)new char + time(0));
    int q = rand() % 100 + 3, up = 1;
    while (!chk(q)) q = rand() % 100 + 3;
    int tp = q;
    while ((LL)tp * q <= 1e8) up++, tp *= q;
    up = rand() % up; int p = q;
    for (int i = 1; i <= up || p <= 5000; i++) p *= q; 
    printf("5000 %d\n", p);
    for (int i = 1; i <= 5000; i++) {
        int x = rnd() % (p - 1) + 1;
        while (s.count(x)) x = rnd() % (p - 1) + 1;
        printf("%d ", x), s.insert(x); 
    }
}