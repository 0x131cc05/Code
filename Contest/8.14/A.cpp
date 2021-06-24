#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int frac[N], inv[N];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

char s[N];

int main() {
    scanf("%s", s + 1); int n = strlen(s + 1);
    frac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    int res = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = l;
        while (r < n && s[r + 1] == s[l]) r++;
        res = (res + (LL)C(l - 1 + n - r, l - 1) * (r - l + 1)) % mod;
        for (int i = 1; i <= r - l; i++) {
            int tmp = 0;
            if (l != 1) tmp = (tmp + C(l - 2 + n - r + i, l - 2)) % mod;
            if (r != n) tmp = (tmp + C(l - 1 + n - r + i - 1, l - 1 + i)) % mod;
            res = (res + (LL)tmp * (r - l + 1 - i)) % mod;
        }
    }
    for (int i = 1, j = 1; i <= n; i++) {
        j = max(j, i);
        while (j <= n && s[j] == s[i]) j++;
        if (j <= n) {
            int r = i - 1 + n - j;
            res = (res + C(r + 1, i)) % mod;
        }
    }
    printf("%d\n", res);
}