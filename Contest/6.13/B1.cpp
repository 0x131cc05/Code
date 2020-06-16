#include <bits/stdc++.h>
using namespace std;

int pos[1 << 19], ct[1 << 20], mx[21], val[1 << 20], fuck[1 << 19]; 

int main() {
    freopen("ex_arcahv3.in", "r", stdin), freopen("out.out", "w", stdout);
    int n, k, type; scanf("%d%d%d", &n, &k, &type);
    for (int i = 0, a; i < n; i++) scanf("%d", &a), pos[a - 1] = i;
    for (int i = 0; i < n; i++) {
        int p = pos[i];
        for (int j = 1; j <= k; j++) {
            int tp = p >> j | (1 << k - j + 1);
            if (++ct[tp] > mx[j] && (ct[tp] < (1 << j))) 
                mx[j] = ct[tp], val[mx[j] + (1 << j)] = i;
            if (ct[tp] == (1 << j)) fuck[i] |= 1 << j - 1;
        }
    } 
    int q; scanf("%d", &q);
    int lastans = 0;
    for (int t = 1; t <= q; t++) {
        int x, y; scanf("%d%d", &x, &y), x ^= type * lastans, y ^= type * lastans, x--;
        int ans = 0;
        for (int i = 1; i <= k; i++) {
            if ((!y) && (!(fuck[x] & (1 << i - 1)))) break;
            if (!((x + 1) >> i)) break;
            int tmp = max(0, (1 << i) - y);
            if (val[(1 << i) + tmp] <= x) ans = i;
        }
        printf("%d\n", lastans = ans);
    }
}
