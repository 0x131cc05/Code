#include <bits/stdc++.h>
using namespace std;

char s[1010];

int main() {
    for (int i = 1; i <= 8; i++) {
        sprintf(s, "sequence < sequence%d.in > sequence%d.ans", i, i);
        system(s);
        cerr << "OK " << i << endl;
    }
}
