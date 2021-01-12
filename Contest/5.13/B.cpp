#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast")

const int N = 100010;

int num[N], base[N];

int main() {
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) scanf("%d", &base[i]), num[i] = base[i];
    while (q--) {
        int t, l, r, x; scanf("%d%d%d%d", &t, &l, &r, &x);
        if (t == 0) {
            int i = l;
            for (i = l; i + 7 <= r; i += 8) {
                num[i] += x; num[i + 1] += x; num[i + 2] += x; num[i + 3] += x;
                num[i + 4] += x; num[i + 5] += x; num[i + 6] += x; num[i + 7] += x;
            }
            for (; i <= r; i++) num[i] += x;
        } else if (t == 1) {
            int i = l;
            for (i = l; i + 7 <= r; i += 8) {
                num[i] /= x; num[i + 1] /= x; num[i + 2] /= x; num[i + 3] /= x;
                num[i + 4] /= x; num[i + 5] /= x; num[i + 6] /= x; num[i + 7] /= x;
            }
            for (; i <= r; i++) num[i] /= x;
        } else if (t == 2) {
            int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
            int i = l, mx = 0;
            for (i = l; i + 7 <= r; i += 8) {
                if (num[i] > a) a = num[i];
                if (num[i + 1] > b) b = num[i + 1];
                if (num[i + 2] > c) c = num[i + 2];
                if (num[i + 3] > d) d = num[i + 3];
                if (num[i + 4] > e) e = num[i + 4];
                if (num[i + 5] > f) f = num[i + 5];
                if (num[i + 6] > g) g = num[i + 6];
                if (num[i + 7] > h) h = num[i + 7];
            }
            mx = max(a, max(b, max(c, max(d, max(e, max(f, max(g, h)))))));
            for (; i <= r; i++) mx = max(mx, num[i]);
            printf("%d\n", mx);
        } else {
            int i = l;
            for (i = l; i + 7 <= r; i += 8) {
                num[i] = base[i]; num[i + 1] = base[i + 1]; num[i + 2] = base[i + 2]; num[i + 3] = base[i + 3];
                num[i + 4] = base[i + 4]; num[i + 5] = base[i + 5]; num[i + 6] = base[i + 6]; num[i + 7] = base[i + 7];
            }
            for (; i <= r; i++) num[i] = base[i];
        }
    }
}
