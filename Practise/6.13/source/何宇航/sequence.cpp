#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int a[50010];
int n, q;

bool AllAGood() {
	for (int i = 1; i <= n; i++) if (a[i] < 0) return 0;
	return 1;
}

int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	if (n <= 50 && q <= 50) {
		while (q--) {
			int dp[60][2] = {};
			int l, r, k; scanf("%d%d%d", &l, &r, &k);
			for (int i = 0; i < 55; i++) for (int j = 0; j < 2; j++) dp[i][j] = -INF;
			dp[0][0] = 0;
			for (int i = l; i <= r; i++) {
				for (int j = 54; j >= 1; j--) dp[j][1] = max(dp[j - 1][0], dp[j][1]);
				for (int j = 0; j < 55; j++) dp[j][1] += a[i];
				for (int j = 0; j < 55; j++) dp[j][0] = max(dp[j][0], dp[j][1]);
			}
			printf("%d\n", dp[k][0]);
		}
	} else if (AllAGood()) {
		for (int i = 1; i <= n; i++) a[i] += a[i - 1];
		while (q--) {
			int l, r, k; scanf("%d%d%d", &l, &r, &k);
			printf("%d\n", a[r] - a[l - 1]);
		}
	} else if (q == 1) {
		
	}
	return 0;
}
/*
6 5
-1 3 -1 2 3 -1
1 4 2
2 5 1
3 4 2
1 3 2
1 1 1

10 10
-3 4 2 -5 1 2 4 -4 2 1
2 6 2
3 9 2
1 5 1
5 9 3
1 10 7
1 4 4
6 9 2
4 8 1
2 9 5
2 5 2


*/
