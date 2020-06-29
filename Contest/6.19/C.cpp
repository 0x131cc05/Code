#include <bits/stdc++.h>
using namespace std;

const int N = 11;

int ans[N], id[N];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    if (n > 10) return puts("I don't know, fuck you."), 0;
    for (int i = 1; i <= n; i++) id[i] = i;
    do {
        int ct = 0;
        for (int i = 1; i <= n; i++) if (abs(id[i] - i) == m) ct++;
        ans[ct]++;
    } while (next_permutation(id + 1, id + n + 1));
    for (int i = 0; i <= n; i++) printf("%d\n", ans[i]);
}
