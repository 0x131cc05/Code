#include <bits/stdc++.h>
using namespace std;
const int N = 1010; int mod;
typedef long long LL;
int f[N][N], frac[N * 2], inv[N * 2];
inline void work(int n) {
	f[0][0] = 1;
	for (int j = 1; j <= n; j++) {
		f[j][0] = 1;
		for (int k = 0; k < n; k++) if (f[j - 1][k])
			for (int i = k + 1; i <= n; i++) 
				f[j][i] = (f[j][i] + (LL)f[j - 1][k] * f[j - 1][i - k - 1]) % mod;
	}	
}
inline int Pow(int x, int y) {
	int res = 1;
	for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
	return res;
}
inline int C(int n, int r) {
	return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}
inline int Catalan(int n) {
	return (LL)C(2 * n, n) * Pow(n + 1, mod - 2) % mod;
} 
int main() {
	freopen("silver.in", "r", stdin), freopen("silver.out", "w", stdout);
	int n, res = 0; scanf("%d%d", &n, &mod), work(n); frac[0] = inv[0] = 1;
	for (int i = 1; i <= 2 * n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
	for (int i = 1; i <= n; i++) res = (res + f[i][n]) % mod;
	int t = Catalan(n); res = (res - t + mod) % mod;
	printf("%d\n", (LL)res * Pow(t, mod - 2) % mod);
}
