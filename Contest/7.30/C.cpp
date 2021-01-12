#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 998244353; 

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int num[N], frac[N], inv[N];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int main() {
    int n; scanf("%d", &n), frac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    sort(num + 1, num + n + 1);
    int half = (n + 1) / 2, res = 0;
    for (int i = half; i <= n; i++) {
        int w = (LL)C(i - 1, half - 1) * frac[half] % mod * frac[n - half] % mod;
        res = (res + (LL)w * num[i]) % mod;
    }
    res = (LL)res * half % mod;
    printf("%d\n", res);
}