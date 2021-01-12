#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

typedef long long LL;

inline int calc(LL l, LL r) {
    l %= mod, r %= mod;
    return (LL)(l + r) * (r - l + 1) / 2 % mod;
} 

const int N = 1000010;

int A[N], B[N]; LL n;

inline int get(LL t) {
    if (t <= n / t) return A[t];
    return B[n / t];
}

inline void store(LL t, int val) {
    if (t <= n / t) A[t] = val;
    else B[n / t] = val;
}

int flag[N], prime[N], tot, mu[N], F[N];

inline void sieve() {
    mu[1] = 1;
    for (int i = 2; i <= N - 10; i++) {
        if (!flag[i]) prime[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * prime[j] <= N - 10; j++) {
            flag[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= N - 10; i++)
        for (int j = i; j <= N - 10; j += i) 
            F[j] += i * mu[i];
    for (int i = 1; i <= N - 10; i++) 
        F[i] = (F[i - 1] + F[i]) % mod;
}

int solve(LL t) {
    if (t <= N - 10) return F[t];
    int tmp = get(t);
    if (tmp) return tmp;
    int res = t % mod;
    for (LL l = 2, r; l <= t; l = r + 1) {
        r = t / (t / l);
        res = (res - (LL)calc(l, r) * solve(t / l)) % mod;
    }
    res = (res + mod) % mod;
    return store(t, res), res;
}

int main() {
    scanf("%lld", &n), sieve(); int res = 0;
    for (LL l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l); LL h = n / l; 
        res = (res + (LL)h % mod * calc(1, h) % mod * (solve(r) - solve(l - 1))) % mod;
    }
    res = (res + mod) % mod;
    printf("%d\n", res);
}
