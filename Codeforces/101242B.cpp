#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> P;
typedef long long LL;

template<class T> void read(T &x) {
    x = 0; char c = getchar(); bool flag = false;
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (flag) x = -x;
}

template<class T, typename... Tail> void read(T &x, Tail&... tail) {
   read(x), read(tail...);
}

const int N = 5010;

int n;

void Dijkstra(vector<int> &dis, vector<P> G[N], int s) {
	vector<int> vis(n + 1); fill(dis.begin(), dis.end(), 1e9);
	priority_queue<P> q; q.push(P(0, s)), dis[s] = 0;
	while (!q.empty()) {
		int u = q.top().second; q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto [v, w] : G[u]) if (dis[v] > dis[u] + w) 
			dis[v] = dis[u] + w, q.push(P(-dis[v], v));
	}
}

vector<P> G1[N], G2[N];

void adde(vector<P> G[N], int from, int to, int w) {
	G[from].push_back(P(to, w));
}

LL dp[2][N], v[N];

void solve(int layer, int l, int r, int L, int R) { 
	if (l > r) return;
	int mid = (l + r) >> 1, pos = -1; LL tmp = 1e18;
	for (int i = L; i <= R && i < mid; i++) if (dp[layer ^ 1][i] < 1e15) {
		LL w = (mid - i - 1) * (v[mid] - v[i]) + dp[layer ^ 1][i];
		if (w < tmp) tmp = w, pos = i;		
	}
	dp[layer][mid] = tmp;
	solve(layer, l, mid - 1, L, pos), solve(layer, mid + 1, r, pos, R);
}

int main() {
	int b, s, m; read(n, b, s, m);
	for (int i = 1, a, b, c; i <= m; i++) 
		read(a, b, c), adde(G1, a, b, c), adde(G2, b, a, c);
	vector<int> disA(n + 1), disB(n + 1);
	Dijkstra(disA, G1, b + 1), Dijkstra(disB, G2, b + 1);
	for (int i = 1; i <= b; i++) v[i] = disA[i] + disB[i];
	sort(v + 1, v + b + 1);
	for (int i = 2; i <= b; i++) v[i] += v[i - 1];
	memset(dp, 0x3f, sizeof(dp)), dp[0][0] = 0; int cur = 0;
	for (int i = 1; i <= s; i++) {
		cur ^= 1;
		for (int j = 0; j <= b; j++) dp[cur][j] = 1e18;
		solve(cur, 1, b, 0, b);
		if (dp[cur][b] == dp[cur ^ 1][b]) break;
	}
	printf("%lld\n", dp[cur][b]);
	return 0;
}