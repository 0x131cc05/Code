#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

inline LL mul(LL a, LL b, LL mod) {
    return (a * b - (LL)((long double)a / mod * b) * mod + mod) % mod;
}

LL x, y;

LL exgcd(LL a, LL b) {
    if (!b) return x = 1, y = 0, a;
    LL d = exgcd(b, a % b);
    LL t = x; x = y, y = t - a / b * y; 
    return d;
}

LL a[N], m[N];

inline LL Just_DOIT(int n) {
    LL a1 = a[1], m1 = m[1];
    for (int i = 2; i <= n; i++) {
        LL g = exgcd(m1, m[i]), delta = a[i] - a1;
        if (delta % g) return -1;
        LL hh = m[i] / g;
        x = (mul(x, delta / g, hh) + hh) % hh;
        a1 = x * m1 + a1, m1 = m1 / g * m[i];
    }
    return a1;
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld%lld", &m[i], &a[i]);
    printf("%lld\n", Just_DOIT(n));
}