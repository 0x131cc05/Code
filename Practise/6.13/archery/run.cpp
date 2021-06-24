#include <bits/stdc++.h>
using namespace std;

char s[1010];

int main() {
    for (int i = 1; i <= 20; i++) {
        sprintf(s, "archery < archery%d.in > archery%d.ans", i, i);
        system(s);
    }
}
