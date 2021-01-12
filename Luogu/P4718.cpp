#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

inline LL mul(LL a, LL b, LL mod) {
    return (a * b - (LL)((long double)a / mod * b + 0.5) * mod + mod) % mod;
}

inline LL Pow(LL x, LL y, LL mod) {
    LL res = 1;
    for (; y; y >>= 1, x = mul(x, x, mod)) if (y & 1) res = mul(res, x, mod);
    return res;
}

LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

const int P[] = { 2, 3, 5, 7, 11, 13, 131 };

inline bool Miller_Rabin(LL n) {
    if (n == 1) return false;
    LL tmp = n - 1; int ct = 0;
    while (tmp % 2 == 0) tmp /= 2, ct++;
    for (int i = 0; i < 7; i++) {
        if (n == P[i]) return true;
        LL tp = Pow(P[i], tmp, n), nxt;
        for (int j = 1; j <= ct; j++) {
            nxt = mul(tp, tp, n);
            if (nxt == 1 && tp != 1 && tp != n - 1) return false;
            tp = nxt;
        }
        if (tp != 1) return false;
    }
    return true;
}

inline LL rnd(LL x, LL c, LL mod) {
    return (mul(x, x, mod) + c) % mod;
}

inline LL rnd() {
    return rand() | (LL)rand() << 16 | (LL)rand() << 32 | (LL)rand() << 48;
}

inline LL Pollard_Rho(LL n) {
    if (Miller_Rabin(n)) return n;
    LL s = 0, t = 0, c = rnd() % (n - 1) + 1, val = 1;
    for (int cir = 1; ; cir <<= 1, s = t, val = 1) {
        for (int i = 1; i <= cir; i++) {
            t = rnd(t, c, n), val = mul(val, abs(t - s), n);
            if ((i & 127) == 0) {
                LL g = gcd(val, n);
                if (g != 1) return g;
            }
        }
        LL g = gcd(val, n);
        if (g != 1) return g;
    }
}

vector<LL> wkr;

void Factor(LL n) {
    if (n == 1) return;
    if (Miller_Rabin(n)) return wkr.push_back(n), void();
    LL t = Pollard_Rho(n);
    while (t == n) t = Pollard_Rho(n);
    while (n % t == 0) n /= t;
    Factor(t), Factor(n);
}

int main() {
    srand((LL)new char); int T; scanf("%d", &T);
    while (T--) {
        LL n; scanf("%lld", &n);
        if (Miller_Rabin(n)) { puts("Prime"); continue; }
        wkr.clear(), Factor(n);
        printf("%lld\n", *max_element(wkr.begin(), wkr.end()));
    }
}