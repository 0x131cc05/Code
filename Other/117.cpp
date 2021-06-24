#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int N = 10000010;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int f[110], g[N], wkr[N];

int main() {
    int n, k, x, sum = 0; cin >> n >> k >> x;
    for (int i = 0; i <= k; i++) cin >> f[i], sum += f[i];
    sum = Pow(sum, mod - 2);
    for (int i = 0; i <= k; i++) f[i] = (LL)f[i] * sum % mod;
    g[0] = Pow(f[0], n); int inv = Pow(f[0], mod - 2);
    wkr[1] = 1;
    for (int i = 2; i < x; i++) wkr[i] = (LL)(mod - mod / i) * wkr[mod % i] % mod;
    int res = 0; sum = 0;
    for (int i = 0; i + 1 < x; i++) {
        int tmp = 0;
        for (int j = 0; j < k && j <= i; j++) 
            tmp = (tmp + (LL)g[i - j] * f[j + 1] % mod * (j + 1)) % mod;
        tmp = (LL)tmp * n % mod;
        for (int j = 1; j <= k && j <= i; j++) 
            tmp = (tmp - (LL)f[j] * g[i - j + 1] % mod * (i - j + 1)) % mod;
        tmp = (tmp + mod) % mod;
        g[i + 1] = (LL)tmp * inv % mod * wkr[i + 1] % mod;
    }
    for (int i = 0; i < x; i++) {
        sum = (sum + g[i]) % mod;
        res = (res + (LL)g[i] * i) % mod;
    }
    printf("%lld\n", (res + (LL)(mod + 1 - sum) * x) % mod);
}