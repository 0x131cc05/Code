#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int calc(int a, int l) { // a + a^2 + ... + a^l
    if (a == 1) return l;
    int t = Pow(a, l + 1) - 1;
    return (LL)t * Pow(a - 1, mod - 2) % mod - 1;
}

int calc1(int a, int l) { // 1 * a + 2 * a^2 + 3 * a^3
    if (a == 1) return l;
    int tmp = calc(a, l), t1 = (LL)l * Pow(a, l + 1) % mod;
    return (LL)(t1 - tmp + mod) * Pow(a - 1, mod - 2) % mod;
}

int c[1010], n, m, st[1010];

int one() {
    int res = 0;
    for (int i = 1; i <= m; i++) res = (res + st[i] + c[i] - 1) % mod;
    for (int i = 1; i <= m; i++) if (c[i] > 1) {
        int ed = st[i] + c[i] - 1;
        int w = ((LL)ed * (1 + calc(2, c[i] - 2)) - (LL)calc1(2, c[i] - 1) * (mod + 1) / 2) % mod;
        w = (w + mod) % mod, res = (res + w) % mod;
    }
    return res;
}

int other() {
    int res = 0;
    for (int i = 2; i <= m; i++) {
        int base = 1;
        for (int j = i + 1; j >= 3; j--) {
            if (c[j - 2] <= 1) break;
            int a = i - j + 3, t = (LL)(a + 1) * Pow(a, mod - 2) % mod;
            int ed = st[j - 2] + c[j - 2] - 1;
            int w = ((LL)ed * (1 + calc(t, c[j - 2] - 2)) - (LL)calc1(t, c[j - 2] - 1) * Pow(t, mod - 2)) % mod;
            w = (w + mod) % mod, w = (LL)w * Pow(a, c[j - 1] - 2) % mod;
            res = (res + (LL)w * base) % mod;
            base = (LL)base * Pow(i - j + 3, c[j - 1] - c[j - 2]) % mod;
        }
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m), st[0] = 1;
    for (int i = 1; i <= m; i++) scanf("%d", &c[i]), st[i] = st[i - 1] + c[i - 1];
    printf("%d\n", (one() + other()) % mod);
}