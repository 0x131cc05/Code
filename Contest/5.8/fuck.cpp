#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL x, y;

LL exgcd(LL a, LL b) {
    if (!b) return x = 1, y = 0, a;
    LL res = exgcd(b, a % b), t = x;
    return x = y, y = t - a / b * y, res;
}

inline int phi(int x) {
    int res = x;
    for (int i = 2; i * i <= x; i++) if (x % i == 0) {
        res = res / i * (i - 1);
        while (x % i == 0) x /= i;
    }
    if (x != 1) res = res / x * (x - 1);
    return res;
}

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

inline int Pow(int x, LL y, int mod) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline LL excrt(LL A[], LL P[], int n) {
    LL lcm = P[1], a = A[1];
    for (int i = 2; i <= n; i++) {
        LL t = exgcd(lcm, P[i]), delta = A[i] - a, fuck = P[i] / t;
        if (delta % t) return -1; 
        x = x * (delta / t), x = (x % fuck + fuck) % fuck;
        a = x * lcm + a, lcm *= fuck;
    }
    return a;
}

LL A[3], P[3];

inline LL solve(int a, int m) {
    a %= m;
    if (m == 1) return 1;
    int t = phi(m), g = gcd(t, m);
    LL res = solve(a, g); 
    A[1] = res, P[1] = t;
    A[2] = Pow(a, res, m), P[2] = m;
    LL fuck = excrt(A, P, 2);
    if (fuck < t) return fuck + (LL)t / g * m;
    return fuck;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int a, m; scanf("%d%d", &a, &m);
        LL t = solve(a, m);
        printf("%lld\n", t);
    }
}
