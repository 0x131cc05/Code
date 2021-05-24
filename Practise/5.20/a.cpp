#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 22;

typedef long long LL;

int mod;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

void FWT(int a[], int len) {
    for (int mid = 2; mid <= len; mid <<= 1)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++) {
                int A = a[j], B = a[j + (mid >> 1)];
                a[j] = A + B, a[j + (mid >> 1)] = A - B;
            }
}

int flag[N], pw[N / 5];

void sieve(int n) {
    flag[1] = 1;
    for (int i = 2; i <= n; i++) 
        if (!flag[i]) for (int j = i + i; j <= n; j += i)
            flag[j] = 1;
}

int main() {
    freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
    int n, m; scanf("%d%d%d", &n, &m, &mod);
    sieve(m);
    for (int i = 1; i <= m; i++) flag[i] ^= 1;
    int len = 1;
    while (len <= m) len <<= 1;
    FWT(flag, len);
    int diff = flag[0], mx = 0;
    for (int i = 0; i < len; i++) {
        if (flag[i] >= 0) pw[flag[i]]++, mx = max(mx, flag[i]);
        else pw[-flag[i] + diff]++, mx = max(mx, diff - flag[i]);
    }
    int res = 0;
    for (int i = 1; i <= mx; i++) {
        int t = i <= diff ? i : -(i - diff);
        res = (res + (LL)Pow(t, n) * pw[i]) % mod;
    }
    res = (res + mod) % mod;
    int phi = mod, nw = mod;
    for (int i = 2; i * i <= nw; i++) if (nw % i == 0) {
        while (nw % i == 0) nw /= i;
        phi = phi / i * (i - 1);
    }
    if (nw != 1) phi = phi / nw * (nw - 1);
    res = (LL)res * Pow(len, phi - 1) % mod;
    printf("%d\n", res);
}