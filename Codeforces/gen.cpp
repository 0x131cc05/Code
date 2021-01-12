#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 30010;

int id[N];

LL rnd() {
    return rand() | rand() << 16 | (LL)rand() << 32;
}

int main() {
    srand((long long)new char + time(0));
    freopen("in.in", "w", stdout);
    puts("1");
    int n = 20;
    printf("%d 4 100000\n", n);
    for (int i = 1; i <= n; i++) id[i] = i; 
    random_shuffle(id + 1, id + n + 1);
    for (int i = 1; i <= n; i++) printf("%d ", id[i]);
    puts("");
    for (int i = 1; i <= 100000; i++)
        printf("%d %lld\n", rand() % n + 1, rnd() % 100000 + 1);
}
