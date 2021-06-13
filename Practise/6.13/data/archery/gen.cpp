#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

mt19937 rnd((LL)new char + time(0));

int id[400010];

int main() {
    for (int i = 7; i <= 14; i++) {
        static char s[110]; sprintf(s, "archery%d.in", i);
        freopen(s, "w", stdout);
        int n = rnd() % 1000 + 2000, r = n * 2; 
        r += rnd() % (1000000001 - r);
        for (int i = 1; i <= 2 * n; i++) id[i] = i;
        random_shuffle(id + 1, id + 2 * n + 1);
        int type = i % 2 == 1;
        int a;
        if (!type) a = rnd() % (n + 1) + 1;
        else a = 2 * n - rnd() % n;
        for (int i = 1; i <= 2 * n; i++) if (id[i] == a) {
            swap(id[1], id[i]); break;
        }
        printf("%d %d\n", n, r);
        for (int i = 1; i <= 2 * n; i++) printf("%d ", id[i]);
        fclose(stdout);
    }
}
