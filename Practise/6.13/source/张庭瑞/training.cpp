#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
const int M = 5005;
struct EDGE {
	int to, next;
} e[N * 2];
int lastE[N], eid;
void initE() {
	memset(lastE, -1, sizeof(lastE));
	eid = 0;
}
void add_edge(int u, int v) {
	e[eid].to = v;
	e[eid].next = lastE[u];
	lastE[u] = eid++;
}
struct EDGES {
	int u, v, c, lca;
} ne[M];
int n, m, cc[N], cd[N][15];
int dp[N][1 << 10];
int dep[N], fa[N], fr[N];
vector<int> has[N];
void predfs(int u, int lst, int D) {
	fa[u] = lst;
	dep[u] = D;
	cc[u] = 0;
	for (int i = lastE[u]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (v == lst) continue;
		predfs(v, u, D + 1);
		fr[v] = 1 << cc[u];
		cd[u][cc[u]++] = v;
	}
}
int LCA(int u, int v) {
	if (dep[u] < dep[v])
		swap(u, v);
	while (dep[u] > dep[v])
		u = fa[u];
	while (u != v) {
		u = fa[u];
		v = fa[v];
	}
	return u;
}
void dfs(int u) {
	for (int i = 0; i < cc[u]; i++) {
		int v = cd[u][i];
		if (v == fa[u]) continue;
		dfs(v);
	}
	for (int j = 0; j < (int)has[u].size(); j++) {
		int a = ne[has[u][j]].u, ma = 0, b = ne[has[u][j]].v, mb = 0, sum = ne[has[u][j]].c;
		while (a != u) {
			sum += dp[a][ma];
			ma = fr[a];
			a = fa[a];
		}
		while (b != u) {
			sum += dp[b][mb];
			mb = fr[b];
			b = fa[b];
		}
		for (int mask = 0; mask < (1 << cc[u]); mask++)
			if (!(mask & ma) && !(mask & mb))
				dp[u][mask] = max(dp[u][mask], sum + dp[u][mask | ma | mb]);
	}
}
int main() {
	freopen("training.in", "r", stdin);
	freopen("training.out", "w", stdout);
	scanf("%d%d", &n, &m);
	initE();
	int sum = 0;
	for (int i = 1; i <= m; i++) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		ne[i].u = u;
		ne[i].v = v;
		ne[i].c = c;
		if (!c) {
			add_edge(u, v);
			add_edge(v, u);
		} else {
			sum += c;
		}
	}
	predfs(1, 0, 0);
	for (int i = 1; i <= m; i++) {
		int u = ne[i].u, v = ne[i].v;
		int lca = LCA(u, v);
		ne[i].lca = lca;
		if (ne[i].c && ((dep[u] - dep[lca] + dep[v] - dep[lca]) & 1))
			continue;
		has[lca].push_back(i);
	}
	dfs(1);
	printf("%d\n", sum - dp[1][0]);
	return 0;
}
