// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
#define N 100010
#define LL long long
const int mod = 998244353;
inline int Pow(int x, int y) {
	int res = 1;
	for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
	return res;
}
struct Poly {
	static int r[N], len, l; int A[N];
	Poly() {memset(A, 0, sizeof(A));}
	inline static void Reset(int _n) {
		Poly::l = 0, Poly::len = 1;
		while (len <= _n) len <<= 1, l++;
		for (int i = 1; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
	}
	void operator *= (int type) {
		for (int i = 1; i < len; i++) if (i < r[i]) swap(A[i], A[r[i]]);
		for (int mid = 2; mid <= len; mid <<= 1)
			for (int i = 0; i < len; i += mid) {
				int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
				for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod)
					t = (LL)w * A[j + (mid >> 1)] % mod, A[j + (mid >> 1)] = (A[j] - t + mod) % mod, A[j] = (A[j] + t) % mod;
			}
	}
};
int Poly::r[N], Poly::len, Poly::l;
// b(x) = 2b'(x) - a(x)b'(x) ^ 2
inline void Inv(const Poly &a, Poly &b, int n) {
	if (n == 1) return void(b.A[0] = Pow(a.A[0], mod - 2));
	else Inv(a, b, (n + 1) >> 1); Poly c(a);
	Poly::Reset(n * 3); int l = Poly::len;
	for (int i = n; i < l; i++) c.A[i] = 0;
	c *= 1, b *= 1;
	for (int i = 0;i < l;i++)
		b.A[i] = (2 - (LL)c.A[i] * b.A[i] % mod + mod) % mod * b.A[i] % mod;
	b *= 0; int inv = Pow(l, mod - 2);
	for (int i = 0;i < l;i++) b.A[i] = (LL)b.A[i] * inv % mod;
	for (int i = n;i < l;i++) b.A[i] = 0;
}
int main() {
	Poly a, b; int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a.A[i]);
	Inv(a, b, n);
	for (int i = 0; i < n; i++) printf("%d ", b.A[i]);
}