#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 998244353;

typedef long long LL;
typedef vector<int> vec;

int Pow(int x, int y) {
	int res = 1;
	for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
	return res;
}

int r[N << 2];

int GetR(int n) {
	int len = 1, l = 0;
	while (len <= n) len <<= 1, l++;
	for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
	return len;
}

void NTT(vec &a, int len, int type) {
	a.resize(len);
	for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
	for (int mid = 2; mid <= len; mid <<= 1) {
		int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
		for (int i = 0; i < len; i += mid)
			for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod)
				t = (LL)a[j + (mid >> 1)] * w % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
	}
	if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
		a[i] = (LL)a[i] * inv % mod;
}

vec Mul(vec a, vec b) {
	int n = a.size() - 1 + b.size() - 1, len = GetR(n);
	NTT(a, len, 1), NTT(b, len, 1);
	for (int i = 0; i < len; i++) a[i] = (LL)a[i] * b[i] % mod;
	NTT(a, len, 0);
	return a.resize(n + 1), a;
}

int frac[N], inv[N];

int main() {
	int n, m; scanf("%d%d", &n, &m), frac[0] = inv[0] = 1; if (n < m) swap(n, m);
	for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
	vec A(n + 2, 0), B(n + 2, 0), C(n + 2, 0);
	for (int i = 0; i <= n; i++) {
		A[i] = inv[i], B[i] = (LL)Pow(i, n) * inv[i] % mod, C[i] = (LL)Pow(i, m) * inv[i] % mod;
		if (i & 1) A[i] = mod - A[i];
	}
	B = Mul(A, B), C = Mul(A, C);
	for (int i = 0; i <= n; i++) B[i] = (LL)B[i] * frac[i] % mod, C[i] = (LL)C[i] * frac[i] % mod;
	B[n + 1] = C[m + 1] = 0;
	int res = 0;
	for (int i = 1; i <= m; i++)
		res = (res + (LL)2 * B[i] * C[i] % mod + (LL)B[i + 1] * C[i] + (LL)B[i] * C[i + 1]) % mod;
	printf("%d\n", res);
}
