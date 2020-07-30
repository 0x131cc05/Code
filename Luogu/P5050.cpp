#include <bits/stdc++.h>
using namespace std;

const int N = 64010;
const int mod = 998244353;

typedef long long LL;
typedef vector<int> vec;

void Print(vec& a) {
//	for (auto v : a) printf("%d ", v);
//	puts("");
}

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

int Wn[2][17][N << 2];

void Pre(int len) {
	for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) {
		int w1 = Pow(3, (mod - 1) / mid), w2 = Pow(w1, mod - 2);
		Wn[1][step][0] = Wn[0][step][0] = 1, Wn[1][step][1] = w1, Wn[0][step][1] = w2;
		for (int i = 2; i < (mid >> 1); i++) {
			Wn[1][step][i] = (LL)Wn[1][step][i - 1] * w1 % mod;
			Wn[0][step][i] = (LL)Wn[0][step][i - 1] * w2 % mod;
		}
	}
}

void NTT(vec &a, int len, int type) {
	a.resize(len);
	for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
	for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) 
		for (int i = 0; i < len; i += mid)
			for (int j = i, t; j < i + (mid >> 1); j++) 
				t = (LL)Wn[type][step][j - i] * a[j + (mid >> 1)] % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
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

vec MulT(vec a, vec b) {
	int n = b.size() - 1; reverse(b.begin(), b.end()), a = Mul(a, b);
	for (int i = 0; i + n < a.size(); i++) a[i] = a[i + n];
	Print(a);
	return a.resize(a.size() - n), a;
}

vec Inv(vec a, int n) {
	if (n == 1) return { Pow(a[0], mod - 2) };
	vec b = Inv(a, (n + 1) >> 1); a.resize(n);
	int len = GetR(n * 2);
	Print(b);
//	cout << "a: ", Print(a);
	NTT(a, len, 1), NTT(b, len, 1);
//	cout << "b: ", Print(b);
	for (int i = 0; i < len; i++) b[i] = (2 - (LL)a[i] * b[i] % mod + mod) * b[i] % mod;
	NTT(b, len, 0);
//	cout << "b: ", Print(b);
	return b.resize(n), b;
}

int x[N], y[N]; vec wkr[N << 2];

void Sol1(int rt, int l, int r) {
	if (l == r) return wkr[rt] = { 1, mod - x[l] }, void();
	int mid = (l + r) >> 1;
	Sol1(rt << 1, l, mid), Sol1(rt << 1 | 1, mid + 1, r), wkr[rt] = Mul(wkr[rt << 1], wkr[rt << 1 | 1]);
}

void Sol2(int rt, int l, int r, vec nw) {
	if (l == r) return y[l] = nw[0], void();
	int mid = (l + r) >> 1; nw.resize(r - l + 1);
	Sol2(rt << 1, l, mid, MulT(nw, wkr[rt << 1 | 1])), Sol2(rt << 1 | 1, mid + 1, r, MulT(nw, wkr[rt << 1]));
}

int main() {
	int n, m; scanf("%d%d", &n, &m), n++; vec base(n, 0);
	for (int i = 0; i < n; i++) scanf("%d", &base[i]);
	for (int i = 1; i <= m; i++) scanf("%d", &x[i]);
	int len = 1;
	while (len <= 2 * max(n, m)) len <<= 1;
	Pre(len);
//	Print(Mul({ 1, 2 }, { 1, 3 }));
	Sol1(1, 1, m);
	auto fuck = Inv(wkr[1], n);
	Print(fuck);
	base = MulT(base, fuck), Print(base), Sol2(1, 1, m, base);
	for (int i = 1; i <= m; i++) printf("%d\n", y[i]);
}
