#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int main() {
    int n, m; scanf("%d%d", &n, &m), m -= n;
    int t = m; if ((t ^ n) & 1) t++;
    int A = (n - t) / 2, B = 1, base = (LL)m * (m + 1) % mod;
    for (int i = 2; i <= t; i++) B = (LL)B * i % mod;
    printf("%lld\n", (LL)Pow(base, A) * B % mod);
    return 0;
}