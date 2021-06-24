#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int MAXN = 1e3 + 5;
const int MAXM = 5e3 + 5;
const int ALL = (1<<10) + 5;

#define bbit(i) (1<<(i))
#define bdig(x,i) (((x)>>(i))&1)

int n,m;
int dep[MAXN], anc[MAXN];
vector<int> g[MAXN];
int sid[MAXN];

void dfs_tree(int u,int fa)
{
	anc[u] = fa;
	if(fa) g[u].erase(find(g[u].begin(), g[u].end(), fa));
	for(int i=0; i<(int)g[u].size(); ++i)
	{
		int v = g[u][i];
		dep[v] = dep[u] + 1; sid[v] = i;
		dfs_tree(v, u);
	}
}

int nfa[MAXN][MAXN];
void dfs_nfa(int u,int rt)
{
	for(int i=0; i<(int)g[u].size(); ++i)
	{
		int v = g[u][i];
		nfa[rt][v] = nfa[rt][u];
		dfs_nfa(v,rt);
	}
}

inline int slow_lca(int u,int v)
{
	if(dep[u] < dep[v]) swap(u,v);
	while(dep[u] > dep[v]) u = anc[u];
	while(u != v) u = anc[u], v = anc[v];
	return u;
}

vector<int> pths[MAXN];

struct Edge_uvw
{
	int u,v,w;
	Edge_uvw(void){}
	Edge_uvw(int _u,int _v,int _w): u(_u), v(_v), w(_w) {}
}es[MAXM];

int dp[MAXN][MAXN], f[MAXN][ALL];

void dfs_dp(int u)
{
	int gsiz = (int)g[u].size();
	if(!gsiz) return;
	for(int i=0; i<gsiz; ++i)
		dfs_dp(g[u][i]);
	
	const vector<int> &vec = pths[u];
	
	int all = (1<<gsiz) - 1;
	for(int mask=all-1; mask>=0; --mask)
	{
		for(int i=0; i<gsiz; ++i) if(!bdig(mask, i))
			f[u][mask] += dp[g[u][i]][0];
		
		for(int i=0; i<(int)vec.size(); ++i)
		{
			int v1 = es[vec[i]].u, v2 = es[vec[i]].v, w = es[vec[i]].w;
			if(v2 == u) swap(v1, v2);
			if(v1 == u)
			{
				int t = sid[nfa[u][v2]];
				if(bdig(mask, t)) continue;
				f[u][mask] = max(f[u][mask],
					f[u][mask | bbit(t)] + w
					+ dp[ g[u][t] ][v2]
				);
			}
			else
			{
				int t1 = sid[nfa[u][v1]], t2 = sid[nfa[u][v2]];
				if(bdig(mask, t1) || bdig(mask, t2)) continue;
				f[u][mask] = max(f[u][mask],
					f[u][mask | bbit(t1) | bbit(t2)] + w
					+ dp[ g[u][t1] ][v1]
					+ dp[ g[u][t2] ][v2]
				);
			}
		}
	}
	
	dp[u][0] = dp[u][u] = f[u][0];
	for(int i=1; i<=n; ++i) if(nfa[u][i])
	{
		int t = sid[nfa[u][i]];
		dp[u][i] = f[u][bbit(t)] + dp[ g[u][t] ][i];
	}
}

int main(void)
{
	freopen("training.in","r",stdin);
	freopen("training.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		es[i] = Edge_uvw(u, v, w);
		if(!w) g[u].push_back(v), g[v].push_back(u);
	}
	
	dfs_tree(1, 0);
	
	for(int u=1; u<=n; ++u)
		for(int i=0; i<(int)g[u].size(); ++i)
		{
			int v = g[u][i];
			nfa[u][v] = v;
			dfs_nfa(v, u);
		}
	
	int sumw = 0;
	for(int i=1; i<=m; ++i) if(es[i].w)
	{
		sumw += es[i].w;
		int u = es[i].u, v = es[i].v;
		if(dep[u] % 2 != dep[v] % 2) continue;
		
		int uv = slow_lca(u, v);
		pths[uv].push_back(i);
	}
	
	dfs_dp(1);
	
	printf("%d",sumw - dp[1][0]);
	return 0;
}
