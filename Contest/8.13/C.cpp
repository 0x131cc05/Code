#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
const int mod = 1e9 + 7;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int F[N], G[N]; 

int main() {
    int n, k; scanf("%d%d", &n, &k);
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (i & 1) F[i] = (F[i] + (LL)Pow(k, (i + 1) / 2) * i % mod) % mod;
        else F[i] = (F[i] + (LL)Pow(k, i / 2 + 1) * i / 2 + (LL)Pow(k, i / 2) * i / 2) % mod;
        G[i] = (G[i] + Pow(k, (i + 1) / 2)) % mod;
        for (int j = i * 2, step = 2; j <= n; j += i, step++) {
            F[j] = (F[j] - (LL)F[i] * step) % mod;
            G[j] = (G[j] - G[i]) % mod;
        }
        res = (res + (LL)F[i] * (n / i)) % mod;
        res = (res - G[i]) % mod;
    }
    printf("%d\n", (res + mod) % mod);
}