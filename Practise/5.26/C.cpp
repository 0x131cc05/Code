#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

typedef long long LL;

int num[N]; LL f[2][N], g[2][N];

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    for (int i = n; i >= 1; i--) num[i] -= num[i - 1];
    memset(f, 0x3f, sizeof(f));
    f[0][2] = max(num[2], 0), f[1][2] = max(-num[2], 0);
    g[0][2] = f[0][2];
    for (int i = 3; i <= n; i++) {
        for (int t = 0; t <= 1; t++) if (f[t][i - 1] <= 1e17) {
            LL tmp = num[i] + g[t][i - 1];
            if (!tmp) f[t][i] = min(f[t][i], f[t][i - 1]), f[t ^ 1][i] = min(f[t ^ 1][i], f[t][i - 1]);
            else {
                
            }
        }
    }
}