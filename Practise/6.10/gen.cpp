#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("in.in", "w", stdout);
    puts("100000");
    for (int i = 1; i <= 25000; i++) {
        printf("1 %d %d 1\n", i * 2 - 1, i * 2);
        printf("1 %d %d -1\n", i * 2 - 1, i * 2);
    }
    for (int i = 1; i <= 50000; i++) 
        puts("2 1 100000");
}