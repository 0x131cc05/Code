#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int fuck = 0;

int calc(int n, int m) {
    if (n > m) swap(n, m);
    int all = 1, lim = n * m; fuck += lim;
    for (int i = 1; i <= n + m - 1; i++) {
        int cnt = min(min(i, n + m - i), n);
        all = (LL)all * Pow(n + m - i, mod - 1 - cnt) % mod;
    } 
    return all;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n, m; scanf("%d%d", &n, &m);
        if (n * m % 3) { puts("0"); continue; }
        fuck = 0;
        int res = (LL)calc(n / 3, m / 3) * calc((n + 1) / 3, (m + 1) / 3) % mod * calc((n + 2) / 3, (m + 2) / 3) % mod;
        for (int i = 1; i <= fuck; i++) res = (LL)res * i % mod;
        printf("%d\n", res);
    }
}