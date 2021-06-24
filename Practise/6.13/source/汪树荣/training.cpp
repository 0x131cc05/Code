#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e3, msz = 5e3, dsz = 10, msksz = (1 << dsz) - 1;
const int inf = 0x3f3f3f3f;
short lg[msksz + 5];
int n, m, rt = 1, sum, ans, full[nsz + 5], pr[nsz + 5], dep[nsz + 5], dp[nsz + 5][msksz + 5];
vector<int> g[nsz + 5];

struct edge {
	int S, u, v, w;
	
	edge() {}
	edge(int u, int v, int w): S(0), u(u), v(v), w(w) {}
	edge(int S, int u, int v, int w): S(S), u(u), v(v), w(w) {}
};
edge e[msz + 5];
vector<edge> dat[nsz + 5];

void dfs(int u = rt) {
	for (int v : g[u]) if (v != pr[u]) {
		pr[v] = u, dep[v] = dep[u] + 1;
		dfs(v);
	}
}

inline int lca(int &u, int &v) {
	if (dep[u] > dep[v]) swap(u, v);
	for (; dep[pr[v]] > dep[u]; v = pr[v]);
	if (pr[v] == u) return u;
	if (dep[u] != dep[v]) v = pr[v];
	for (; pr[u] != pr[v]; u = pr[u], v = pr[v]);
	return pr[u];
}

inline int to_S(const vector<int> &a, int u) {
	loop (i, a.size()) if (a[i] == u) return 1 << i;
	return 0;
}

inline void init() {
	loop (i, dsz) lg[1 << i] = i;
	cont (i, m) if (!e[i].w) {
		int u = e[i].u, v = e[i].v;
		g[u].push_back(v), g[v].push_back(u);
	}
	dfs();
	cont (i, m) if (e[i].w) {
		int u = e[i].u, v = e[i].v, w = e[i].w, k = dep[u] + dep[v];
		if (k & 1) ans += w;
		else {
			int p = lca(u, v);
			e[i].S = to_S(g[p], u) | to_S(g[p], v);
			dat[p].push_back(e[i]);
			sum += e[i].w;
		}
	}
}

inline void upd(int &a, int b) {
	if (a < b) a = b;
}

inline int calc(int u, int v) {
	int res = dp[v][full[v]];
	for (; v != u; v = pr[v]) {
		int p = pr[v];
		res += dp[p][full[p] ^ to_S(g[p], v)];
	}
	return res;
}

inline int find_son(int u, int v) {
	for (; pr[v] != u; v = pr[v]);
	return v;
}

inline int calc(int u, int v1, int v2) {
	int res = 0;
	if (u != v1) res += calc(find_son(u, v1), v1);
	if (u != v2) res += calc(find_son(u, v2), v2);
	return res;
}

void calc(int u = rt) {
	int d = g[u].size(), full = ::full[u] = (1 << d) - 1;
	auto &f = dp[u];
	f[0] = 0;
	for (int v : g[u]) if (v != pr[u]) calc(v);
	cont (S, full) {
		int lb = S & -S, v = g[u][lg[lb]];
		if (v == pr[u]) continue;
		f[S] = f[S ^ lb] + dp[v][::full[v]];
	}
	
	for (edge e : dat[u]) {
		int T = e.S, v1 = e.u, v2 = e.v, w = e.w, val = calc(u, v1, v2) + w;
		circ (S, 0, full) if ((S & T) == 0) upd(f[S | T], f[S] + val);
	}
	cont (S, full) {
		loop (i, d) if (S >> i & 1) {
			upd(f[S], f[S ^ (1 << i)]);
		}
	}
}

inline void solve() {
	memset(dp, -inf, sizeof(dp));
	calc();
	ans += sum - dp[rt][full[rt]];
}

int main() {
	freopen("training.in", "r", stdin);
	freopen("training.out", "w", stdout);
	scanf("%d%d", &n, &m);
	cont (i, m) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
	init();
	solve();
	printf("%d\n", ans);
}