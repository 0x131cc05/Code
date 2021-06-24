#include <bits/stdc++.h>

using namespace std;

#define FOR(i, x, y) for(int i = (int)(x); i < (int)(y); ++i)
#define REP(i, x, y) for(int i = (int)(x); i <= (int)(y); ++i)
#define PB push_back

const int maxn = 1005;
const int maxm = 5005;
const int maxd = 11;

int n, m, ctot;
int ed[maxm][3];
int dep[maxn], par[maxn], stot[maxn], pos[maxn];
int low[1 << maxd];
int f[maxn][1 << maxd];
vector<int> g[maxn], vec[maxn], cyc[maxn];

inline int lca(int u, int v){
	for(; dep[u] > dep[v]; u = par[u]);
	for(; dep[u] < dep[v]; v = par[v]);
	for(; u != v; u = par[u], v = par[v]);
	return u;
}

inline void dfs(int u, int p){
	if(~p)
		dep[u] = dep[p] + 1;
	par[u] = p;
	FOR(i, 0, g[u].size()){
		int v = g[u][i];
		if(v == p)
			continue;
		dfs(v, u);
	}
	return;
}

inline void calcF(int u, int p){
	stot[u] = 0;

	vector<int> son; son.clear();
	FOR(i, 0, g[u].size()){
		int v = g[u][i];
		if(v == p)	
			continue;
		calcF(v, u);
		pos[v] = stot[u]++, son.PB(v);
	}
	
	FOR(i, 0, vec[u].size()){
		int e = vec[u][i], s = ed[e][0], t = ed[e][1];
		int w = 0;
		for(int lst = -1; s != u; lst = s, s = par[s]){
			if(!~lst)
				w += f[s][(1 << stot[s]) - 1];
			else
				w += f[s][((1 << stot[s]) - 1) ^ (1 << pos[lst])];
			ed[e][0] = s;
		}
		for(int lst = -1; t != u; lst = t, t = par[t]){
			if(!~lst)
				w += f[t][(1 << stot[t]) - 1];
			else
				w += f[t][((1 << stot[t]) - 1) ^ (1 << pos[lst])];
			ed[e][1] = t;
		}
		ed[e][2] += w;
		if(ed[e][0] != u)
			cyc[ed[e][0]].PB(e);
		if(ed[e][1] != u)
			cyc[ed[e][1]].PB(e);
	}
	
	FOR(S, 0, 1 << stot[u])
		f[u][S] = -0x3f3f3f3f;
	f[u][0] = 0;
	
	FOR(S, 1, 1 << stot[u]){
		int i = low[S], v = son[i];
		// no cycle edge
		if(f[u][S ^ (1 << i)] >= 0)
			f[u][S] = max(f[u][S], f[u][S ^ (1 << i)] + f[v][(1 << stot[v]) - 1]);
		FOR(j, 0, cyc[v].size()){
			int e = cyc[v][j];
			int oth = (ed[e][0] ^ ed[e][1] ^ v);
			if(oth == u){ // edge back to ancestor
				if(f[u][S ^ (1 << i)] >= 0)
					f[u][S] = max(f[u][S], f[u][S ^ (1 << i)] + ed[e][2]);
			}
			else{ // heng'cha edge
				if((S >> pos[oth] & 1) && f[u][S ^ (1 << i) ^ (1 << pos[oth])] >= 0)
					f[u][S] = max(f[u][S], f[u][S ^ (1 << i) ^ (1 << pos[oth])] + ed[e][2]);
			}
		}
	}
	return;
}

int main(){
	freopen("training.in", "r", stdin);
	freopen("training.out", "w", stdout);
	scanf("%d%d", &n, &m);
	
	int ctot = 0;
	FOR(i, 0, m){
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		--u, --v;
		if(!w)
			g[u].PB(v), g[v].PB(u);
		else
			ed[ctot][0] = u, ed[ctot][1] = v, ed[ctot][2] = w, ++ctot;
	}
	
	dfs(0, -1);
	
	int sum = 0;
	FOR(i, 0, ctot){
		int u = ed[i][0], v = ed[i][1], r = lca(u, v);
		sum += ed[i][2];
		if((dep[u] & 1) == (dep[v] & 1))
			vec[r].PB(i);
	}
	
	FOR(S, 0, 1 << maxd) FOR(i, 0, maxd) if(S >> i & 1){
		low[S] = i;
		break;
	}
	
	calcF(0, -1);
	
	printf("%d\n", sum - f[0][(1 << stot[0]) - 1]);
	return 0; 
}
