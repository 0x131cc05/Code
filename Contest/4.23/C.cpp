#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

inline LL mul(LL a, LL b, LL mod) {
	return (a * b - (LL)((long double)a / mod * b + 0.5) * mod + mod) % mod;
}

inline LL Pow(LL x, LL y, LL mod) {
	LL res = 1;
	for (; y; y >>= 1, x = (LL)mul(x, x, mod)) if (y & 1) res = mul(res, x, mod);
	return res;
}

const int _A[] = {2, 3, 5, 7, 11, 13, 131};

inline bool Miller_Rabin(LL n) {
	if (n == 1) return false;
	LL tmp = n - 1; int ct = 0;
	while (!(tmp & 1)) tmp >>= 1, ct++;
	for (int i = 0; i < 7; i++) {
		if (n == _A[i]) return true;
		LL a = Pow(_A[i], tmp, n), nxt = a;
		for (int j = 1; j <= ct; j++) {
			nxt = mul(a, a, n);
			if (nxt == 1 && a != 1 && a != n - 1) return false;
			a = nxt;
		}
		if (a != 1) return false;
	}
	return true;
}

inline LL _rand(LL x, LL c, LL mod) {
	return (mul(x, x, mod) + c) % mod;
}

inline LL _rand() {
	return (LL)rand() << 48 | (LL)rand() << 32 | rand() << 16 | rand();
}

inline LL _abs(LL x) {
	return x >= 0 ? x : -x;
}

LL gcd(LL a, LL b) {
	return b ? gcd(b, a % b) : a;
}

inline LL Pollard_Rho(LL n) {
	LL s = 0, t = 0, c = _rand() % (n - 1) + 1, val = 1;
	for (int cir = 1; ; cir <<= 1, s = t, val = 1) {
		for (int i = 0; i < cir; i++) {
			t = _rand(t, c, n), val = mul(val, _abs(t - s), n);
			if (i % 127 == 0) {
				LL g = gcd(val, n);
				if (g != 1) return g;
			} 
		}
		LL g = gcd(val, n);
		if (g != 1) return g;
	}
}

vector<LL> divisors; 

inline void Factor(LL n) {
	if (n == 1) return;
	if (Miller_Rabin(n)) return divisors.push_back(n), void();
	LL d = n;
	while (d == n) d = Pollard_Rho(n);
	while (n % d == 0) n /= d;
	Factor(n), Factor(d);
}

map<LL, LL> fuck;

inline LL find(LL x) {
    if (!fuck.count(x)) return x;
    return fuck[x] = find(fuck[x]);
}

inline LL push(LL k, LL len) {
    LL t = find(k);
    fuck[t] = (t + 1) % len;
    if (t >= k) return t - k;
    return t + len - k;
}

LL num[210]; int n;

inline LL solve(LL len) {
    LL res = 0; fuck.clear();
    for (int i = 1; i <= n; i++) res += push(num[i] % len, len);
    return res;
}

inline LL Abs(LL x) { return x > 0 ? x : -x; }

int main() {
    scanf("%*d%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &num[i]);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) 
            Factor(Abs(num[j] - num[i]));
    LL res = 0; sort(divisors.begin(), divisors.end());
    divisors.resize(unique(divisors.begin(), divisors.end()) - divisors.begin());
    // cout << solve(6) << endl;
    for (int i = n; i <= n * n; i++) {
        res = max(res, solve(i));
        // cout << i << ' ' << res << endl;
    }
    for (auto t : divisors) if (t > n * n) res = max(res, solve(t));
    printf("%lld\n", res);
    return 0;
}