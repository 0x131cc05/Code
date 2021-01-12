#include <bits/stdc++.h>
using namespace std;

const int N = 34;
const int mod = 998244353;

typedef long long LL;

int f[N][1 << 10][1 << 10], tmp[N][3], one[N][1 << 10][1 << 10], fucked;

int l[N], r[N], up, n, wkr[N];

void pre() {
    tmp[0][0] = 1;
    for (int i = 1; i <= n; i++) 
        for (int j = 0; j < 3; j++) if (tmp[i - 1][j])
            for (int k = 0; k <= 1; k++) tmp[i][(j + k) % 3] = (tmp[i][(j + k) % 3] + tmp[i - 1][j]) % mod;
    for (int i = 1; i <= n; i++) if (!l[i]) fucked |= 1 << i - 1;
    for (int s1 = 0; s1 < 1 << n; s1++) {
        if (s1 & fucked) continue;
        for (int s2 = 0; s2 < 1 << n; s2++) {
            if (s1 & s2) continue;
            for (int i = 1; i <= n; i++) {
                int A = s1 & (1 << i - 1), B = s2 & (1 << i - 1);
                if (A || B) {
                    for (int j = 0; j <= up; j++) {
                        if (A && ((l[i] - 1) >> j & 1)) one[j][s1][s2] |= 1 << i - 1;
                        if (B && (r[i] >> j & 1)) one[j][s1][s2] |= 1 << i - 1;
                    }
                }
            }
        }
    }
}

int solve() {
    int all = (1 << n) - 1;
    for (int s1 = 0; s1 < 1 << n; s1++) {
        if (s1 & fucked) continue;
        f[up + 1][s1][all ^ s1] = __builtin_popcount(s1) & 1 ? -1 : 1;
    }
    for (int i = up; i >= 0; i--) {
        for (int s1 = 0; s1 < 1 << n; s1++) {
            if (s1 & fucked) continue;
            for (int s2 = 0; s2 < 1 << n; s2++) if (f[i + 1][s1][s2]) {
                if (s1 & s2) continue;
                int full = (s1 | s2) & one[i][s1][s2], w = f[i + 1][s1][s2], t = n - __builtin_popcount(s1 | s2);
                for (int s = full; ; s = (s - 1) & full) {
                    int A = s1 ^ (s1 & s), B = s2 ^ (s2 & s);
                    int other = __builtin_popcount(one[i][A][B]) % 3;
                    f[i][A][B] = (f[i][A][B] + (LL)w * tmp[t][other ? 3 - other : 0]) % mod;
                    if (!s) break;
                }
            }
        }
    }
    int res = 0;
    for (int s1 = 0; s1 < 1 << n; s1++)
        for (int s2 = 0; s2 < 1 << n; s2++) res = (res + f[0][s1][s2]) % mod;
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &l[i], &r[i]), up = max(up, 31 - __builtin_clz(r[i]));
    pre(), printf("%d\n", solve());
}