#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
struct edge {int to, next;} e[N * 2];
int head[N], ecnt;
inline void adde(int from, int to) {
    e[++ecnt] = (edge){to, head[from]}, head[from] = ecnt;
    e[++ecnt] = (edge){from, head[to]}, head[to] = ecnt;
}
typedef long long LL;
int mx, a[N], b[N]; LL ans;
void dfs(int u, int f, int t) {
    if (a[u] >= t) ans += b[u], t = a[u];
    for (int i = head[u]; i; i = e[i].next)
    	if (e[i].to != f) dfs(e[i].to, u, t);
}
#define OPEN(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
int main() {
	freopen("cave2.in", "r", stdin);
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), mx = max(mx, a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), adde(a, b);
    dfs(1, 0, 0); 
    printf("%lld\n", ans);
    return 0;
}
