#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, r, lab[N];
inline void calc(int *c, int *d) {
	int st = -1;
	for (int i = 0; i < n; i++) if (c[i]) {
		st = i;
		break;
	}
	if (st == -1) {
		for (int i = 0; i < n; i++) d[i] = 0;
		return;
	}
	int tr = r;
	if (st) {
		while (st--) {
			tr--;
			for (int i = 1; i < n; i++) {
				if (c[i]) c[i - 1]++, c[i]--;
			}
		}
	}
	c[0]--;
	for (int t = 0; t < n; t++) {
		tr--;
		int tc = 0;
		if (c[0]) tc = 1;
		for (int i = 1; i < n; i++) {
			if (c[i]) c[i - 1]++, c[i]--;
		}
		if (tc) c[n - 1]++, c[0]--;
	}
	int flag = 1;
	for (int i = 0; i < n; i++) if (!c[i]) { flag = 0; break; }
	if (!flag) {
		rotate(c, c + tr % n, c + n);
	}
	for (int i = 0; i < n; i++) {
		d[i] = c[i] + (!i);
	}
}
int a[N * 2], c1[N], c2[N], d1[N], d2[N];
int main() {
	freopen("archery.in", "r", stdin);
	freopen("archery.out", "w", stdout);
	scanf("%d%d", &n, &r);
	int ta;
	scanf("%d", &ta);
	for (int i = 0; i < 2 * n - 1; i++) scanf("%d", &a[i]);
	int mn = N, fr = -1;
	for (int s = 0; s < n; s++) {
		for (int i = 0; i < n; i++) {
			int x, y;
			if (i < s) {
				x = a[i * 2], y = a[i * 2 + 1];
			} else if (i == s) {
				x = a[i * 2], y = ta;
			} else {
				x = a[i * 2 - 1], y = a[i * 2];
			}
			c1[i] = (x <= ta) + (y <= ta);
			c2[i] = (x < ta) + (y < ta);
		}
		calc(c1, d1);
		calc(c2, d2);
		int fnd = -1;
		for (int i = 0; i < n; i++) if (d1[i] != d2[i]) {
			fnd = i;
			break;
		}
		if (mn >= fnd) {
			mn = fnd;
			fr = s;
		}
	}
	printf("%d\n", fr + 1);
	return 0;
}
