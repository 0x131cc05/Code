#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 310;

int mod, f[N], C[N][N];

int Pow(int x, int y) {
	int res = 1;
	for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
	return res;
}

int main() {
	int n; scanf("%d%d", &n, &mod), n++;
	for (int i = 0; i <= n; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	}
	for (int i = 1; i <= n - 1; i++) {
		f[i] = Pow(2, i * (i - 1) / 2);
		for (int j = 1; j < i; j++) 
			f[i] = (f[i] - (LL)f[j] * C[i - 1][j - 1] % mod * Pow(2, (i - j) * (i - j - 1) / 2) % mod + mod) % mod;
	}
	int res = Pow(2, n * (n - 1) / 2 - 1);
	for (int j = 2; j < n; j++)
		res = (res - (LL)f[j - 1] * Pow(2, j - 2) % mod * C[n - 2][j - 2] % mod * Pow(2, (n - j) * (n - j - 1) / 2) % mod + mod) % mod;
	res = res * 2 % mod;
	res -= f[n - 1];
	printf("%d\n", res);
}
