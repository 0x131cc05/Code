#include <bits/stdc++.h>
using namespace std;
#define maxn 75
#define ll long long
#define db double
#define vi vector<int>
#define pb push_back
#define mod 998244353
#define fi first
#define pi pair<int, int>
#define se second
#define mp make_pair
ll ksm(ll a, ll b) {
   if (!b) return 1;
   ll ns = ksm(a, b >> 1);
   ns = ns * ns % mod;
   if (b & 1) ns = ns * a % mod;
   return ns;
}
// head
ll dp[maxn][maxn][maxn]; // ???,????
ll p[maxn][maxn];
int k;
ll calc(int n, int l, int r) {
	// ?k : l ~ r ??
	// ????? 
	if (n <= k) return 1;
	int len = r - l + 1;
	ll ans = 1;
	ans = ksm(p[len][len], n / k - 1);
	n %= k;
	if (n >= l) {
		r = min(r, n);
		ans = ans * p[len][r - l + 1] % mod;
	} 
	return ans;
}
int main() {
	for (int i = 0; i < maxn; i++) {
		p[i][0] = 1;
		for (int j = 1; j <= i; j++)
			p[i][j] = p[i][j - 1] * (i + 1 - j) % mod; 
	}
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n >> k;
		if (n <= k) {
			ll ans = 0;
			for (int i = 1; i <= n; i++) {
				ll na = p[k][i];
				if (i != n) {
					na = na * i % mod;
					na = na * p[k - 1][n - i - 1] % mod;
				}	
				ans = (ans + na) % mod;
			}
			cout << ans << endl;
		}
		else {
			memset(dp, 0, sizeof(dp));
			for (int i = k + 1; i >= 1; i--)
				for (int j = 0; j <= i - 1; j++)
					for (int t = j; t <= i - 1; t++) {
						if (i == k + 1) {
							if (j == 0) {
								dp[i][j][t] = 0;
								continue;
							}
							dp[i][j][t] = calc(n - (j - 1), t - j + 1, k);
							dp[i][j][t] = dp[i][j][t] * p[k][j - 1] % mod;
							int nr = min(n, j + k - 1);
							// t ~ nr
							int len = nr - t + 1; // ???????
							dp[i][j][t] = dp[i][j][t] * p[k - (t - j)][len] % mod; 
						}
						else {
							dp[i][j][t] = dp[i + 1][j][t]; // i ??
							ll na = 0;
							int ej = j;
							if (j == 0) ej = i;
							na = dp[i + 1][ej][i];
							if (j) {
								na = na * p[k - (t - 1)][i - t] % mod;
								na = na * calc(n - (j - 1), t - j + 1, i - j) % mod;
							}
							dp[i][j][t] = (dp[i][j][t] - na) % mod;
						}
					}
			ll ans = -dp[1][0][0];
			ans %= mod;
			if (ans < 0) ans += mod;
			cout << ans << endl;
		}
	}
	return 0;
}
