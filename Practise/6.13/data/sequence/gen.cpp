#include <bits/stdc++.h>
using namespace std;

mt19937 rnd((long long)new char + time(0));

int main() {
    for (int i = 7; i <= 8; i++) {
        static char in[1010];
        sprintf(in, "sequence%d.in", i);
        freopen(in, "w", stdout);
        int n = 8192, q = 10000;
        printf("%d %d\n", n, q);
        for (int i = 1; i <= n; i++) {
            int v;
            if (rnd() % 4 == 1) v = rnd() % 3000;
            else v = -(rnd() % 2000);
            printf("%d ", v);
        }
        puts("");
        while (q--) {
            int len = 1 << (rnd() % 8 + 6), all = n / len, cur = rnd() % all;
            int r = (cur + 1) * len, l = r - len + 1;
            printf("%d %d %d\n", l, r, rnd() % (r - l + 1) + 1);
        }
        fclose(stdout);
    }
    
}
