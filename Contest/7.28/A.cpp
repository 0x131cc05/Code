#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

typedef long long LL;

struct edge {
	int to, next;
} e[N * 2];

int head[N], ecnt, n;

void adde(int from, int to) {
	e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
	e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int sz[N], son[N], w[N]; vector<LL> tmp; LL len[N];

void dfs(int u, int f) {
	sz[u] = u <= n; int t = w[f] - w[u];
	for (int i = head[u]; i; i = e[i].next)
		if (e[i].to != f) {
			dfs(e[i].to, u), sz[u] += sz[e[i].to];
			if (len[e[i].to] > len[u]) len[u] = len[e[i].to], son[u] = e[i].to;
		}
	len[u] += (LL)t * sz[u];
}

void push(int u, int f, int t) {
	if (u == t) tmp.push_back(len[u]);
	if (son[u]) push(son[u], u, t);
	for (int i = head[u]; i; i = e[i].next)
		if (e[i].to != f && e[i].to != son[u])
			push(e[i].to, u, e[i].to);
}

struct WEN { 

int from, to, w;

bool operator < (const WEN &b) const {
	return w < b.w;
}

};

vector<WEN> wkr;

int fa[N], nw[N], h[510][510], _n, _m, nxt[2][2] = { { 1, 0 }, { 0, 1 } }, val[N];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int ID(int x, int y) {
	return (x - 1) * _m + y;
}

int main() {
    freopen("data.txt", "r", stdin);
	int n, m, k; scanf("%d%d%d", &n, &m, &k), _n = n, _m = m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) scanf("%d", &h[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			for (int t = 0; t < 2; t++) {
				int tx = i + nxt[t][0], ty = j + nxt[t][1];
				if (tx > n || ty > m) continue;
				wkr.push_back((WEN){ ID(i, j), ID(tx, ty), max(h[i][j], h[tx][ty]) });
			}
		}
	sort(wkr.begin(), wkr.end()), ::n = ID(n, m); int tot = ::n, mx = 0;
	for (int i = 1; i <= tot; i++) fa[i] = i, nw[i] = i;
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++)
	       w[ID(i, j)] = h[i][j];
	for (auto t : wkr) {
		int a = find(t.from), b = find(t.to);
		if (a == b) continue;
		fa[a] = b, tot++, adde(tot, nw[a]), adde(tot, nw[b]), nw[b] = tot, mx = w[tot] = t.w;
	}
	LL res = 0, ans = 0;
	for (int i = 1; i <= n; i++)
	    for (int j = 1; j <= m; j++) res += mx - h[i][j];
	dfs(tot, tot), push(tot, tot, tot), sort(tmp.rbegin(), tmp.rend());
	for (int i = 1; i <= k; i++) {
		if (i <= tmp.size()) res -= tmp[i - 1];
        ans ^= res;
	}
	printf("%lld\n", ans);
}
