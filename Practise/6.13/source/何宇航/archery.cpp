#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const ull one = 1;

int n, R, my, S;
int a[400010], pa[400010];
ull p[3200], q[3200];
ull win[3200];

int GetPos() {
	int pos = -1; for (int i = 0; i < n + n; i++) if (a[i] == my) pos = i / 2;
	for (int i = 0; i < S; i++) p[i] = q[i] = 0;
	for (int i = 0; i < n + n; i += 2) p[i / 2 >> 6] |= (ull)(a[i] >= my) << (i / 2 & 63);
	for (int i = 1; i < n + n; i += 2) q[i / 2 >> 6] |= (ull)(a[i] >= my) << (i / 2 & 63);
	for (int it = 0; it < R; it++) {
		int big = (p[pos >> 6] >> (pos & 63) & 1) + (q[pos >> 6] >> (pos & 63) & 1);
		if (pos == 0) pos = big == 1 ? n - 1 : 0;
		else pos = big == 1 ? pos : pos - 1;
		int SS = S / 8 * 8;
		for (int i = 0; i < SS; i += 8) {
			win[i + 0] = p[i + 0] & q[i + 0], q[i + 0] |= p[i + 0];
			win[i + 1] = p[i + 1] & q[i + 1], q[i + 1] |= p[i + 1];
			win[i + 2] = p[i + 2] & q[i + 2], q[i + 2] |= p[i + 2];
			win[i + 3] = p[i + 3] & q[i + 3], q[i + 3] |= p[i + 3];
			win[i + 4] = p[i + 4] & q[i + 4], q[i + 4] |= p[i + 4];
			win[i + 5] = p[i + 5] & q[i + 5], q[i + 5] |= p[i + 5];
			win[i + 6] = p[i + 6] & q[i + 6], q[i + 6] |= p[i + 6];
			win[i + 7] = p[i + 7] & q[i + 7], q[i + 7] |= p[i + 7];
		}
		for (int i = SS; i < S; i++) win[i] = p[i] & q[i], q[i] |= p[i]; 
		int ww = win[0] & 1, ll = q[0] & 1; win[0] ^= ww ^ ll, q[0] ^= ww ^ ll;
		for (int i = 0; i < SS; i += 8) {
			p[i + 0] = win[i + 0] >> 1 | win[i + 1] << 63;
			p[i + 1] = win[i + 1] >> 1 | win[i + 2] << 63;
			p[i + 2] = win[i + 2] >> 1 | win[i + 3] << 63;
			p[i + 3] = win[i + 3] >> 1 | win[i + 4] << 63;
			p[i + 4] = win[i + 4] >> 1 | win[i + 5] << 63;
			p[i + 5] = win[i + 5] >> 1 | win[i + 6] << 63;
			p[i + 6] = win[i + 6] >> 1 | win[i + 7] << 63;
			p[i + 7] = win[i + 7] >> 1 | win[i + 8] << 63;
		}
		for (int i = SS; i < S; i++) p[i] = win[i] >> 1 | win[i + 1] << 63;
		p[n - 1 >> 6] |= (win[0] & 1) << (n - 1 & 63);
	}
	return pos;
}

int main() {
	freopen("archery.in", "r", stdin);
	freopen("archery.out", "w", stdout);
	scanf("%d%d", &n, &R), R = (R - n) % n + 2 * n, S = (n - 1) / 64 + 1;
	for (int i = 0; i < n + n; i++) scanf("%d", &a[i]); my = a[0];
	for (int i = 0; i + 1 < n + n; i++) swap(a[i], a[i + 1]);
	if (n <= 3000) {
		int minj = 0x3f3f3f3f, ans = -1;
		for (int i = n + n - 1; i >= 0; i -= 2) {
			int tmp = GetPos();
			if (tmp < minj) ans = i, minj = tmp;
			if (i) swap(a[i], a[i - 1]), swap(a[i - 1], a[i - 2]);
		}
		printf("%d\n", ans / 2 + 1);
		return 0;
	} else {
		printf("1\n");
		return 0;
	}
}
/*
4 8
7 4 2 6 5 8 1 3

*/
