#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 5e4, inf = 0x3f3f3f3f;
bool flag = 1;
int n, m, a[nsz + 5], pre[nsz + 5];

inline void upd(int &a, int b) {
	if (a < b) a = b;
}

inline int solve(int l, int r, int k) {
	static int f[2][nsz + 5][2];
	if (flag) return pre[r] - pre[l - 1];
	int o = 0, x = 1;
	circ (i, 0, k) loop (d, 2) f[0][i][d] = f[1][i][d] = -inf;
	f[o][0][0] = 0;
	circ (i, l, r) {
		circ (k, 0, min(i - l + 1, k)) {
			int w0 = f[o][k][0], w1 = f[o][k][1];
			upd(f[x][k][0], w0);
			upd(f[x][k + 1][1], w0 + a[i]);
			upd(f[x][k][1], w1 + a[i]);
			upd(f[x][k + 1][1], w1 + a[i]);
			upd(f[x][k][0], w1);
		}
		swap(o, x);
		circ (i, 0, k) loop (d, 2) f[x][i][d] = f[x][i][d] = -inf;
	}
	return max(f[o][k][0], f[o][k][1]);
}

int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	scanf("%d%d", &n, &m);
	cont (i, n) scanf("%d", &a[i]), flag &= a[i] >= 0, pre[i] = pre[i - 1] + a[i];
	cont (i, m) {
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", solve(l, r, k));
	}
}