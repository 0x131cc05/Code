#include <bits/stdc++.h>
using namespace std;

const int maxN = 1005, maxM = 5005, INF = 1e9;

struct Node
{
	int u, v, w;
	Node(int X = 0, int Y = 0, int Z = 0) { u = X; v = Y; w = Z; }
};

int n, m, cnt, clk;
int f[maxN + 1][maxM + 1];
int dfn[maxN + 1], sz[maxN + 1], dep[maxN + 1], fa[maxN + 1];
int g[1 << 11 | 5], id[maxN + 1], bel[maxN + 1];
int G[15][15], pos[15];

Node E[maxM + 1];

vector<int> to[maxN + 1];

inline void chkmx(int &x, int y) { x = x > y ? x : y; }

inline bool check(int u, int rt) { return dfn[u] >= dfn[rt] && dfn[u] <= dfn[rt] + sz[rt] - 1; }

inline void dfs(int u, int pa)
{
	dfn[u] = ++ clk; sz[u] = 1;
	dep[u] = dep[pa] + 1; fa[u] = pa;
	for(int i = 0; i < to[u].size(); i++)
	{
		int v = to[u][i];
		if(v == pa) continue;
		dfs(v, u);
		sz[u] += sz[v];
	}
}

inline void calc(int u, int pa)
{
	for(int i = 0; i < to[u].size(); i++)
	{
		int v = to[u][i];
		if(v == pa) continue;
		calc(v, u);
	}
	int ct = 0;
	for(int i = 0; i < to[u].size(); i++)
	{
		int v = to[u][i];
		if(v == pa) continue;
		pos[ id[v] = ct ++ ] = v;
	}
	for(int s = 1; s <= n; s++)
	{
		bel[s] = -1;
		for(int i = 0; i < to[u].size(); i++)
		{
			int v = to[u][i];
			if(v == pa) continue;
			if(check(s, v)) { bel[s] = id[v]; break; }
		}
	}
	for(int i = 0; i <= ct; i++)
		for(int j = 0; j <= ct; j++)
			G[i][j] = -INF;
	for(int i = 1; i <= cnt; i++)
	{
		int tu = E[i].u, tv = E[i].v, w = E[i].w;
		if(tu == u && bel[tv] != -1)
		{
			int tp = f[ pos[ bel[tv] ] ][i] + w;
			chkmx(G[ bel[tv] ][ct], tp);
		}
		if(tv == u && bel[tu] != -1)
		{
			int tp = f[ pos[ bel[tu] ] ][i] + w;
			chkmx(G[ bel[tu] ][ct], tp);
		}
		if(bel[tu] == -1 || bel[tv] == -1 || bel[tu] == bel[tv]) continue;
		int tp = f[ pos[ bel[tu] ] ][i] + f[ pos[ bel[tv] ] ][i] + w;
		chkmx(G[ bel[tu] ][ bel[tv] ], tp);
		chkmx(G[ bel[tv] ][ bel[tu] ], tp);
	}
	int lim = (1 << ct);
	for(int s = 0; s < lim; s++) g[s] = -INF;
	g[0] = 0;
	for(int i = 0; i < ct; i++)
		for(int s = 0; s < (1 << i); s++)
		{
			if(g[s] == -INF) continue;
			for(int j = 0; j < i; j++)
				if(!(s >> j & 1) && G[i][j] != -INF)
					chkmx(g[s | (1 << j) | (1 << i)], g[s] + G[i][j]);
			if(G[i][ct] != -INF) chkmx(g[s | (1 << i)], g[s] + G[i][ct]);
		}
	for(int i = 0; i < ct; i++)
	{
		int t = f[ pos[i] ][0];
		for(int s = 0; s < lim; s++)
			if(!(s >> i & 1)) chkmx(g[s | (1 << i)], g[s] + t);
	} 
	chkmx(f[u][0], g[lim - 1]);
	for(int i = 1; i <= cnt; i++)
	{
		int tu = E[i].u, tv = E[i].v, t = E[i].w;
		if(bel[tu] != -1 && bel[tv] != -1) continue;
		if(tu == u && bel[tv] != -1) continue;
		if(tv == u && bel[tu] != -1) continue;
		if(tu == u || tv == u) chkmx(f[u][i], f[u][0]);
		else
		{
			int x = max(bel[tu], bel[tv]);
			if(x == -1) continue;
			chkmx(f[u][i], g[(lim - 1) ^ (1 << x)] + f[ pos[x] ][i]);
		}
	}
}

int main()
{
	freopen("training.in", "r", stdin);
	freopen("training.out", "w", stdout);
	scanf("%d %d", &n, &m);

	int sum = 0;
	for(int i = 1; i <= m; i++)
	{
		int u, v, t;
		scanf("%d %d %d", &u, &v, &t);
		if(!t) to[u].push_back(v), to[v].push_back(u);
		else E[++ cnt] = Node(u, v, t);
		sum += t;
	}

	dfs(1, 0);

	int tc = cnt; cnt = 0;
	for(int i = 1; i <= tc; i++)
	{
		int u = E[i].u, v = E[i].v, flag = 0;
		while(u != v)
		{
			if(dep[u] < dep[v]) swap(u, v);
			u = fa[u];
			flag ^= 1;
		}
		if(!flag) E[++ cnt] = E[i];
	}

	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= cnt; j++)
			f[i][j] = -INF;
	calc(1, 0);

	printf("%d\n", sum - f[1][0]);
	return 0;
}
