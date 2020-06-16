#include <bits/stdc++.h>
using namespace std;

const int N = 5010;

typedef long long LL;

int h[N], nxt[N], buk[N], ans[N][N];

int main() {
    int n; scanf("%d", &n); int res = 0;
    for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
    for (int i = 1; i <= n; i++) {
        nxt[i - 1] = i, nxt[i] = i + 1;
        for (int j = 1; j <= i - 2; j++) {
            if ((LL)(h[i] - h[j]) * (nxt[j] - j) > (LL)(h[nxt[j]] - h[j]) * (i - j))
                nxt[j] = i;
        }
        for (int j = 1; j <= i; j++) {
            memset(buk, 0, sizeof(buk)); int hh = 0;
            for (int k = j; k <= i; k++) {
                if (!buk[k]) {
                    if (!buk[nxt[k]]) hh++;
                    buk[nxt[k]] = 1;
                }
            }
            cout << i << ' ' << j << ' ' << hh << endl;
            res ^= hh;
        }
    }
    printf("%d\n", res);
}

