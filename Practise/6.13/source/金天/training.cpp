#include <bits/stdc++.h>

#define eprintf(args...) fprintf(stderr, args)
#define rep(i, n) for (int i = 0; i < (int)(n); ++ i)

struct Edge {
	int u, v, w;

	Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
};

const int mxn = 1005;
const int mxd = 10;

int n, m;
std::vector <int> adj[mxn];
int eid[mxn][mxn];
std::vector <Edge> edge;
int dp[mxn][1 << mxd];
int full[mxn];
int fa[mxn], dep[mxn];
int dfn[mxn], ed[mxn], on[mxn];
std::vector <Edge> ein[mxn][mxd][mxd], eto[mxn][mxd];
int rem[mxn][mxn];

inline void update(int &x, int y) {
	if (y > x) x = y;
}

void dfs0(int u, int p) {
	static int tim = 0;
	on[tim] = u;
	dfn[u] = tim ++;
	for (int v : adj[u]) {
		if (v == p) continue;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs0(v, u);
	}
	ed[u] = tim;
}

inline bool in_subt(int u, int v) {
	return dfn[u] <= dfn[v] && ed[v] <= ed[u];
}

int chain(int u, int v) {
	int nv = v;
	if (rem[u][nv] == -1) {
		int ans = 0;
		while (fa[v] != u) {
			ans += dp[fa[v]][full[fa[v]] ^ 1 << eid[fa[v]][v]];
			v = fa[v];
		}
		rem[u][nv] = ans;
	}
	return rem[u][nv];
}

void dfs1(int u, int p) {
	int pid = -1;
	rep(i, adj[u].size()) if (adj[u][i] == p) pid = i;
	for (int v : adj[u]) {
		if (v == p) continue;
		dfs1(v, u);
	}
	dp[u][0] = 0;
	for (int mask = 1; mask < (1 << (int) adj[u].size()); ++ mask) {
		if (~pid && (mask >> pid & 1)) continue;
		update(full[u], mask);
		int x = __builtin_ctz(mask);
		dp[u][mask] = dp[u][mask ^ 1 << x] + dp[adj[u][x]][full[adj[u][x]]];
		for (Edge e : eto[u][x]) {
			int a = e.u, b = e.v, w = e.w;
			if (a != u) std::swap(a, b);
			if ((dep[b] - dep[a] + 1) % 2 == 0) continue;
			update(dp[u][mask], dp[u][mask ^ 1 << x] + dp[b][full[b]] + chain(u, b) + w);
		}
		for (int y = x + 1; y < (int) adj[u].size(); ++ y) {
			if (mask >> y & 1) {
				for (Edge e : ein[u][x][y]) {
					int a = e.u, b = e.v, w = e.w;
					if (!in_subt(adj[u][x], a)) std::swap(a, b);
					if ((dep[a] + dep[b] + 1) % 2 == 0) continue;
					update(dp[u][mask], dp[u][mask ^ 1 << x ^ 1 << y] + dp[a][full[a]] + dp[b][full[b]] + chain(u, a) + chain(u, b) + w);
				}
			}
		}
	}
}

int main() {
	freopen("training.in", "r", stdin);
	freopen("training.out", "w", stdout);
	scanf("%d %d", &n, &m);
	int sum = 0;
	rep(i, m) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		-- u, -- v;
		if (w == 0) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		} else {
			sum += w;
			edge.emplace_back(u, v, w);
		}
	}
	rep(i, n) rep(j, adj[i].size()) eid[i][adj[i][j]] = j;
	dfs0(0, -1);
	rep(r, n) rep(i, adj[r].size()) rep(j, i) {
		int u1 = adj[r][i], u2 = adj[r][j];
		if (u1 == fa[r] || u2 == fa[r]) continue;
		for (Edge e : edge) {
			int u = e.u, v = e.v, w = e.w;
			if ((in_subt(u1, u) && in_subt(u2, v)) || (in_subt(u1, v) && in_subt(u2, u))) {
				ein[r][i][j].push_back(e);
				ein[r][j][i].push_back(e);
			}
		}
	}
	rep(r, n) rep(i, adj[r].size()) {
		int u = adj[r][i];
		if (u == fa[r]) continue;
		for (Edge e : edge) {
			if ((e.u == r && in_subt(u, e.v)) || (e.v == r && in_subt(u, e.u))) {
				eto[r][i].push_back(e);
			}
		}
	}
	memset(rem, -1, sizeof(rem));
	dfs1(0, -1);
	printf("%d\n", sum - dp[0][full[0]]);
	return 0;
}
