#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef pair<int, int> P;
typedef long long LL;

vector<P> G[N];

int sz[N], n, mn = 1e9;

LL res;

void dfs(int u, int f) {
  sz[u] = 1;
  for (auto [v, w] : G[u]) if (v != f)
    dfs(v, u), sz[u] += sz[v], res += (LL)min(n - sz[v], sz[v]) * w, mn = min(mn, w);
}

int main() {
  scanf("%d", &n);
  for (int i = 1, a, b, c; i < n; i++) scanf("%d%d%d", &a, &b, &c), G[a].push_back(P(b, c)), G[b].push_back(P(a, c));
  dfs(1, 0), cout << res << endl, printf("%lld\n", res * 2 - mn);
}
