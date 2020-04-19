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
LL dp[N][N]; int mx, a[N], b[N];
void dfs(int u, int f) {
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u);
            for (int j = 0; j <= mx; j++)
                dp[u][j] += dp[e[i].to][j];
        }
    LL tmp = dp[u][a[u]] + b[u];
    for (int i = 0; i <= a[u]; i++) dp[u][i] = max(dp[u][i], tmp);
}
#define OPEN(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
int main() {
	OPEN("cave5");
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), mx = max(mx, a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), adde(a, b);
    dfs(1, 0); 
    printf("%lld\n", dp[1][0]);
    return 0;
}
