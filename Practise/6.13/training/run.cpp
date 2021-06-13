#include <bits/stdc++.h>
using namespace std;

char s[1010];

int main() {
    for (int i = 1; i <= 20; i++) {
        sprintf(s, "training < training%d.in > training%d.ans", i, i);
        system(s);
    }
}
