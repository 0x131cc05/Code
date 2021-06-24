#include <bits/stdc++.h>
using namespace std;

int tmp[1 << 19], num[1 << 20], mx[19], wkr[1 << 20]; vector<int> fuck[19];

int main() {
    freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
    int n, q, k; scanf("%d%d", &n, &q), k = __builtin_ctz(n) + 1;
    for (int i = 0; i < n; i++) scanf("%d", &num[i]), tmp[num[i]] = i;
    memset(num, 0, sizeof(num));
    int tot = 0;
    for (int i = 0; i < n; i++) {
        int pos = tmp[i];
        for (int t = 1; t < k; t++) {
            int cur = pos >> t | (1 << (k - t));
            wkr[cur] = max(wkr[cur], i);
            num[cur]++;
            if (num[cur] > mx[t]) {
                mx[t] = num[cur], fuck[t].push_back(i), tot++;
            }
        }
    }
    int lastans = 0;
    while (q--) {
        int x, y; scanf("%d%d", &x, &y);
        x = (x + lastans) % n, y = (y + lastans) % n; int res = 0;
        int most = x ? 31 - __builtin_clz(x + 1) : 0;
        for (int t = most; t >= 1; t--) {
            int keep = upper_bound(fuck[t].begin(), fuck[t].end(), x) - fuck[t].begin();
            int need = (1 << t) - keep;
            if (!need) {
                int pos = tmp[x];
                if (wkr[pos >> t | (1 << (k - t))] != x) need++;
            }
            if (need <= y) {
                res = t; break;
            }
        }
        printf("%d\n", lastans = res);
    }
}