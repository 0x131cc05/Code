#include <bits/stdc++.h>
using namespace std;

const int N = 20;

int num[N], s[N], t[N], tag[N];

bool push(int l, int r, int c) {
    for (int i = l; i <= r; i++) 
        if (tag[i] == -1) tag[i] = c;
        else if (tag[i] != c) return false;
    return true;
}

int main() {
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]), num[i] += num[i - 1];
    for (int i = 1; i <= q; i++) {
        scanf("%d%d", &s[i], &t[i]);
    }
    int ans = 1e9;
    for (int s1 = 0; s1 < 1 << q; s1++) {
        memset(tag, -1, sizeof(tag));
        bool flag = true;
        int res = 0;
        for (int i = 1; i <= q; i++) {
            int c = s1 & (1 << i - 1);
            if (s[i] <= t[i]) {
                int d = num[t[i]] - num[s[i]];
                if (c) {
                    res += num[n] - d;
                    flag &= push(t[i] + 1, n, 1);
                    flag &= push(1, s[i], 1);
                } else {
                    res += d;
                    flag &= push(s[i] + 1, t[i], 0);
                }
            } else {
                int d = num[n] - (num[s[i]] - num[t[i]]);
                if (c) {
                    res += num[n] - d;
                    flag &= push(t[i] + 1, s[i], 1);
                } else {
                    res += d;
                    flag &= push(1, t[i], 0);
                    flag &= push(s[i] + 1, n, 0);
                }
            }
        }
        if (flag) ans = min(ans, res);
    }
    printf("%d\n", ans);
}