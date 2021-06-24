#include<bits/stdc++.h>
using namespace std;
#define dbg(x) cerr << #x << " = " << x << endl
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define MP make_pair
#define pb push_back
typedef long long LL;
typedef unsigned long long ull;
const int N = 1000 + 10;
template <typename Tp> void read(Tp &x){
	x = 0; int op = 1; char ch = getchar();
	while(!isdigit(ch)){ if(ch == '-') op = -1; ch = getchar(); }
	while(isdigit(ch)){ x = x*10+ch-'0'; ch = getchar(); } x *= op;
}
template <typename Tp> void CMax(Tp &x, Tp y){ if(y > x) x = y; }
template <typename Tp> void CMin(Tp &x, Tp y){ if(y < x) x = y; }

int n, m;
int w[N][N];
int head[N], nxt[N << 1], to[N << 1], tot;
void add_edge(int x, int y){ to[++ tot] = y; nxt[tot] = head[x]; head[x] = tot; }
void add(int x, int y){ add_edge(x, y); add_edge(y, x); }
int dep[N];
void dfs(int x, int fa){
	dep[x] = dep[fa] + 1;
	for(int i = head[x]; i; i = nxt[i]){
		int y = to[i]; if(y == fa) continue;
		dfs(y, x);
	}
}
int f[N], g[N], g0[N], nod;
int ans, sum;
void get(int x, int fa, int rt){
	if((dep[x] & 1) == (dep[rt] & 1)){
		if(w[rt][x] && (!nod || f[x] + w[rt][x] > f[nod] + w[rt][nod])) nod = x;
	}
	for(int i = head[x]; i; i = nxt[i]){
		int y = to[i]; if(y == fa) continue;
		get(y, x, rt);
 	}
}
void DP(int x, int fa){
	for(int i = head[x]; i; i = nxt[i]){
		int y = to[i]; if(y == fa) continue;
		DP(y, x);
		f[x] += g[y];
	}
	if(x != 1) {
		g[x] = f[x];
		for(int i = head[x]; i; i = nxt[i]){
			int y = to[i]; if(y == fa) continue;
			nod = 0; get(y, x, fa);
			if(nod) CMax(g[x], f[x] - g[y] + f[nod] + w[nod][fa]);
		}
	}
}
void Movert(int x, int fa){
	CMax(ans, f[x]);
	for(int i = head[x]; i; i = nxt[i]){
		int y = to[i]; if(y == fa) continue;
		f[x] -= g[y];
		int tmp = f[x];
		for(int j = head[x]; j; j = nxt[j]){
			int v = to[j]; if(v == y) continue;
			nod = 0; get(v, x, y);
			if(nod) CMax(tmp, f[x] - g[v] + f[nod] + w[nod][y]);
		}
		f[y] += tmp;
		int tmp2 = g[x];
		g[x] = tmp;
		Movert(y, x);
		f[y] -= tmp;
		f[x] += g[y];
		g[x] = tmp2;
	}
}
int main()
{
	freopen("training.in", "r", stdin);
	freopen("training.out", "w", stdout);
	read(n); read(m);
	int x, y, z;
	rep(i, 1, m) {
		read(x); read(y); read(z);
		if(!z) add(x, y);
		else CMax(w[x][y], z), CMax(w[y][x], z);
		sum += z;
	}
	dfs(1, 0);
	DP(1, 0);
	Movert(1, 0);
	printf("%d", sum - ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
