#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL res[] = {
    0,
199990,
28263827,
371599992,
499999993,
5555555554,
6666666665,
7777777776,
8888888887};

const LL fuck = 1999920117463824;

int a[11];

int main() {
    freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
    for (int i = 0; i < 10; i++) scanf("%d", &a[i]);
    if (!a[0]) return puts("10"), 0;
    for (int i = 1; i <= 9; i++) if (a[i] == 0) {
        printf("%d\n", i); return 0;
    }
    for (int i = 1; i < 9; i++) if (a[i] == 1) {
        printf("%lld\n", res[i]);
        return 0;
    }
    printf("%lld\n", fuck);
}