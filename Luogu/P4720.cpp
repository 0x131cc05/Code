#include <bits/stdc++.h>
using namespace std;

const int N = 30;

typedef long long LL;

int x, y;

int exgcd(int a, int b) {
    if (!b) return x = 1, y = 0, x;
    int d = exgcd(b, a % b);
    int t = x; x = y, y = t - a / b * y;
    return d;
}

int mod, p;

inline LL count(LL n) {
    LL res = 0;
    while (n) res += n / p, n /= p;
    return res;
}

inline int Pow(int x, LL y, int mod = ::mod) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline int calc(LL n) {
    int A = 1, B = 1; LL ct1 = 0, ct2 = 0;
    for (int i = 0; i < mod; i++) if (i % p) {
        LL t = n / mod + (i <= n % mod);
        if (ct1 == 0) ct1 = t, A = i;
        else {
            if (ct1 == t) A = (LL)A * i % mod;
            else ct2 = t, B = (LL)B * i % mod;
        }
    }
    return (LL)Pow(A, ct1) * Pow(B, ct2) % mod;
}

int F(LL n) {
    if (n <= 1) return 1;
    return (LL)F(n / p) * calc(n) % mod;
} 

inline int inv(int x) {
    LL d = exgcd(x, mod); assert(d == 1);
    return (::x % mod + mod) % mod;
}

inline int C(LL n, LL r, int p, int k) { // mod p^k
    ::p = p, ::mod = Pow(p, k, 1000001);
    int res = (LL)F(n) * inv(F(r)) % mod * inv(F(n - r)) % mod;
    LL tp = count(n) - count(r) - count(n - r);
    res = (LL)res * Pow(p, tp) % mod;
    return res;
}

int a[N], m[N];

inline int exCRT(int n) {
    int a1 = a[1], m1 = m[1];
    for (int i = 2; i <= n; i++) {
        int g = exgcd(m1, m[i]), t = a[i] - a1; 
        int tp = m[i] / g; x = ((LL)x * (t / g) % tp + tp) % tp;
        a1 = a1 + m1 * x, m1 = m1 * tp;
    }
    return a1;
}

inline int C(LL n, LL r, int mod) {
    int tot = 0;
    for (int i = 2; i * i <= mod; i++) if (mod % i == 0) {
        int ct = 0; tot++, m[tot] = 1;
        while (mod % i == 0) ct++, mod /= i, m[tot] *= i;
        a[tot] = C(n, r, i, ct);
    }
    if (mod != 1) tot++, m[tot] = mod, a[tot] = C(n, r, mod, 1);
    return exCRT(tot);
}

int main() {
    LL n, m; int p; scanf("%lld%lld%d", &n, &m, &p);
    printf("%d\n", C(n, m, p));
}