#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
const int mod = 1e9 + 7;

typedef pair<int, int> P;

#define fir first
#define sec second

void Inc(int &x, int y) { 
	x += y, x -= x >= mod ? mod : 0;
}

P nxt[N][1 << 15]; int dp[N][1 << 15]; // 走到当前的nxt所需要的步数

void Merge(int cur, int s) {
	if (nxt[cur][s] == P(cur, s)) return;
	int a = nxt[cur][s].fir, b = nxt[cur][s].sec;
	Merge(a, b), Inc(dp[cur][s], dp[a][b]);
	nxt[cur][s] = nxt[a][b];
}

int a[N], pos[N], b[N];

int main() {
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	pos[1] = -1;
	for (int i = 1, ct = 0; i <= n; i++) {
		scanf("%d", &b[i]);
		if (b[i] == 2) pos[i + 1] = ct++; else pos[i + 1] = -1;
	}
	for (int i = 1; i <= n + 1; i++)
		for (int s = 0; s < 1 << m; s++) dp[i][s] = 0, nxt[i][s] = P(i, s);
	for (int s = 0; s < 1 << m; s++) dp[0][s] = 1, nxt[0][s] = P(1, s);
	for (int i = 1; i <= n; i++) {
		static int tmp[1 << 15]; static P nw[1 << 15]; 
		for (int s = 0; s < 1 << m; s++) {
			int t = ~pos[i] ? 1 << pos[i] : 0;
			if (s & t) {
				nw[s] = P(i + b[i], s ^ t), tmp[s] = 1;
				continue;
			}
			int A = i - a[i], B = s ^ t; Merge(A, B);
			if (nxt[A][B].fir == i) nw[s] = P(i + b[i], nxt[A][B].sec ^ t), tmp[s] = dp[A][B] + 2;
			else nw[s] = P(i + 1, nxt[A][B].sec), tmp[s] = dp[A][B] + 1; 
		}
		for (int s = 0; s < 1 << m; s++) dp[i][s] = tmp[s], nxt[i][s] = nw[s];
	}
	Merge(0, 0), printf("%d\n", dp[0][0]);
}
