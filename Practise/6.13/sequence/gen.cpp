#include <bits/stdc++.h>
using namespace std;

mt19937 rnd((long long)new char + time(0));

int main() {
    for (int i = 17; i <= 18; i++) {
        static char in[1010];
        sprintf(in, "sequence%d.in", i);
        freopen(in, "w", stdout);
        int n = 50000, q = 50000;
        printf("%d %d\n", n, q);
        for (int i = 1; i <= n; i++) {
            int v;
            if (rnd() % 3 == 1) v = rnd() % 10000;
            else v = -(rnd() % 2000);
            printf("%d ", v);
        }
        puts("");
        while (q--) {
            int l, r;
            if (rnd() % 2) {
                l = rnd() % n + 1, r = rnd() % n + 1;
            } else {
                l = rnd() % 1000 + 1, r = n - rnd() % 1000;
            }
            if (l > r) swap(l, r);
            printf("%d %d %d\n", l, r, rnd() % (r - l + 1) + 1);
        }
        fclose(stdout);
    }
    
}
