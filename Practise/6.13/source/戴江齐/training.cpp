#include <bits/stdc++.h>
#define rep(i, n) for(int i = 0; i < (int)(n); i ++)
#define rep1(i, n) for(int i = 1; i <= (int)(n); i ++)
#define MP make_pair

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int MOD = 998244353;

int n, m, u[5005], v[5005], w[5005];
vector<int> T[1005];
int par[1005], dep[1005];
vector<int> hv[1005];

void dfs(int c, int p, int d)
{
	par[c] = p; dep[c] = d;
	rep(i, T[c].size()) if(T[c][i] == p) {
		rotate(T[c].begin(), T[c].begin() + i, T[c].end());
		T[c].erase(T[c].begin()); break;
	}
	rep(i, T[c].size()) dfs(T[c][i], c, d + 1);
}

int dp[1005], odp[1005];
int id[1005], tmp[1024];
void gen_dp(int c)
{
	int l = T[c].size();
	rep(i, l) gen_dp(T[c][i]);
	
	rep(i, l) {
		int u = T[c][i]; id[u] = i;
	}
	tmp[0] = 0; rep(i, l) tmp[1 << i] = dp[T[c][i]];
	rep(i, 1 << l) if(i & (i - 1)) tmp[i] = tmp[i & (i - 1)] + tmp[i & -i];
	
	rep(i, hv[c].size()) {
		int e = hv[c][i], cw = w[e], cm = 0, x, y;
		if(u[e] != c) {
			for(x = u[e]; par[x] != c; x = par[x]) cw += odp[x];
			cw += dp[u[e]]; cm |= 1 << id[x];
		}
		if(v[e] != c) {
			for(y = v[e]; par[y] != c; y = par[y]) cw += odp[y];
			cw += dp[v[e]]; cm |= 1 << id[y];
		}
		rep(j, 1 << l) if(!(j & cm)) tmp[j | cm] = max(tmp[j | cm], tmp[j] + cw);
	}
	
	int tot = (1 << l) - 1;
	dp[c] = tmp[tot];
	rep(i, l) odp[T[c][i]] = tmp[tot ^ 1 << i];
}

int main()
{
	freopen("training.in", "r", stdin);
	freopen("training.out", "w", stdout);
	
	scanf("%d%d", &n, &m);
	rep(i, m) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		if(z == 0) {
			T[x].push_back(y); T[y].push_back(x);
		} else {
			u[i] = x; v[i] = y; w[i] = z;
		}
	}
	
	dfs(1, 0, 0);
	int sum = 0;
	rep(i, m) if(w[i]) {
		int x = u[i], y = v[i];
		sum += w[i];
		if((dep[x] - dep[y]) & 1) continue;
		while(x != y) {
			if(dep[x] < dep[y]) swap(x, y);
			x = par[x];
		}
		hv[x].push_back(i);
	}
	
	gen_dp(1);
	printf("%d\n", sum - dp[1]);
	return 0;
}
