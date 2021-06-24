#include <bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;

const int INF = 0x3f3f3f3f;

typedef pair <int, int> pii;
typedef pair <pii, int> ppi;

vector <int> son[1010];
vector <pii> G[1010];
int fa[1010], dep[1010];
vector <ppi> edge;
vector <int> all[1010];
int tmp[1 << 10];
int dp[1010][1010];
int dfn[1010], sz[1010], TOT;

void GetTree(int x, int last) {
	fa[x] = last, dfn[x] = ++TOT, sz[x] = 1;
	for (int i = 0; i < son[x].size(); i++) if (son[x][i] == last) {
		son[x].erase(son[x].begin() + i);
		break;
	}
	sort(son[x].begin(), son[x].end());
	for (auto v : son[x]) dep[v] = dep[x] + 1, GetTree(v, x), sz[x] += sz[v];
}

int GetAnc(int x, int k) {while (k--) x = fa[x]; return x;}

int GetLca(int x, int y) {
	while (x != y) {
		if (dep[x] < dep[y]) swap(x, y);
		x = fa[x];
	}
	return x;
}

bool IsAnc(int x, int y) {
	return dfn[x] <= dfn[y] && dfn[x] + sz[x] > dfn[y];
}

int GetSonId(int x, int t) {
	return lower_bound(son[x].begin(), son[x].end(), t) - son[x].begin();
}

int n;

void GetDp(int x) {
	for (auto v : son[x]) GetDp(v);
	int N = son[x].size();
	for (int i = 0; i < (1 << N); i++) tmp[i] = i == 0 ? 0 : -INF;
	for (auto id : all[x]) {
		int p = edge[id].fi.fi, q = edge[id].fi.se, w = edge[id].se;
		int need = 0, val = w;
		if (p != x) {
			int t = GetAnc(p, dep[p] - dep[x] - 1);
			need |= 1 << GetSonId(x, t), val += dp[t][p];
		}
		if (q != x) {
			int t = GetAnc(q, dep[q] - dep[x] - 1);
			need |= 1 << GetSonId(x, t), val += dp[t][q];
		}
		for (int mask = (1 << N) - 1; mask >= 0; mask--) if ((mask & need) == need) {
			tmp[mask] = max(tmp[mask], tmp[mask ^ need] + val);
		}
	}
	for (int i = 0; i < son[x].size(); i++) {
		int v = son[x][i];
		for (int mask = (1 << N) - 1; mask >= 0; mask--) if (mask >> i & 1) {
			tmp[mask] = max(tmp[mask], tmp[mask ^ 1 << i] + dp[v][v]);
		}
	}
	for (int i = 1; i <= n; i++) if (IsAnc(x, i)) {
		if (i == x) dp[x][i] = tmp[(1 << N) - 1];
		else {
			int t = GetAnc(i, dep[i] - dep[x] - 1);
			int need = 1 << GetSonId(x, t);
			dp[x][i] = tmp[(1 << N) - 1 ^ need] + dp[t][i];
		}
	}
}

int main() {
	freopen("training.in", "r", stdin);
	freopen("training.out", "w", stdout);
	int m; scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int x, y, w; scanf("%d%d%d", &x, &y, &w);
		if (w == 0) son[x].push_back(y), son[y].push_back(x);
		else edge.push_back(mp(mp(x, y), w));
	}
	dep[1] = 0, GetTree(1, 1);
	int ans = 0;
	for (int i = 0; i < edge.size(); i++) {
		int x = edge[i].fi.fi, y = edge[i].fi.se, w = edge[i].se;
		if (dep[x] + dep[y] & 1) ans += w;
		else all[GetLca(x, y)].push_back(i), ans += w;
	}
	GetDp(1);
	printf("%d\n", ans - dp[1][1]);
	return 0;
}
/*
5 8
2 1 0
3 2 0
4 3 0
5 4 0
1 3 2
3 5 2
2 4 5
2 5 1

15 25
7 10 4
13 5 0
12 6 1
10 9 4
3 15 9
5 12 3
3 10 0
8 1 0
15 2 8
11 7 3
14 11 0
15 11 7
2 4 5
3 6 0
2 7 0
1 4 0
9 3 0
14 7 6
5 14 0
3 12 0
7 13 0
5 8 7
5 1 0
15 7 0
14 3 0

*/
