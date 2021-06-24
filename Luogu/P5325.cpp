#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 400010;
const int mod = 1e9 + 7;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline int F(int p, int k) {
    int t = Pow(p, k);
    return t;
}

inline int G(LL n) {
    n %= mod; 
    return (LL)n * (n + 1) / 2 % mod - 1;
}

LL n, a[N]; 

int prime[N], ncnt, flag[N], sum[N], id1[N], id2[N], m;

int g[N];

inline int ID(LL x) {
    if (x <= n / x) return id1[x];
    return id2[n / x];
}

inline void sieve() {
    int up = ceil(sqrt(n));
    for (int i = 2; i <= up; i++) {
        if (!flag[i]) prime[++ncnt] = i, sum[ncnt] = (sum[ncnt - 1] + F(i, 1)) % mod;
        for (int j = 1; j <= ncnt && (LL)i * prime[j] <= up; j++) {
            flag[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
        
    }
}

inline void pre() {
    sieve();
    for (LL l = 1, r; l <= n; l = r + 1) {
        LL tmp = n / l; r = n / tmp, a[++m] = tmp;
        if (a[m] <= r) id1[a[m]] = m; else id2[r] = m;
        g[m] = G(tmp); // g(m, 0)
    }
    for (int i = 1; i <= ncnt; i++) 
        for (int j = 1; j <= m && (LL)prime[i] * prime[i] <= a[j]; j++) 
            g[j] = (g[j] - (LL)F(prime[i], 1) * (g[ID(a[j] / prime[i])] - sum[i - 1] + mod) % mod + mod) % mod;
}

inline int S(LL n, int m) {
    if (n < prime[m] || m > ncnt) return 0;
    int res = (g[ID(n)] - sum[m - 1] + mod) % mod; 
    for (int i = m; i <= ncnt && (LL)prime[i] * prime[i] <= n; i++) 
        for (LL p = prime[i], ct = 1; p * prime[i] <= n; p *= prime[i], ct++) 
            res = (res + (LL)S(n / p, i + 1) * F(prime[i], ct) + F(prime[i], ct + 1)) % mod;
    return res;
}

inline int solve(LL _n) {
    return n = _n, pre(), S(n, 1) + F(1, 1); 
}

int main() {
    LL n; scanf("%lld", &n);
    printf("%d\n", solve(n));
    return 0;
}

