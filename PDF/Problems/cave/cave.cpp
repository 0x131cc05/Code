#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
struct edge {int to, next;} e[N * 2];
int head[N], ecnt;
inline void adde(int from, int to) {
    e[++ecnt] = (edge){to, head[from]}, head[from] = ecnt;
    e[++ecnt] = (edge){from, head[to]}, head[to] = ecnt;
}
typedef long long LL;
map<int, LL> f[N]; int a[N], b[N], rt[N];
inline void merge(int x, int y) {
    if (f[rt[x]].size() > f[rt[y]].size()) swap(x, y);
    for (map<int, LL>::iterator it = f[rt[x]].begin(); it != f[rt[x]].end(); it++) 
        f[rt[y]][it->first] += it->second;
    f[rt[x]].clear(), rt[x] = rt[y];
}
inline void update(int u, map<int, LL>::iterator it) {
    int t = rt[u]; map<int, LL>::iterator it2;
    for (int nw = b[u]; it != f[t].begin(); nw += it2->second, f[t].erase(it2)) {
        it2 = it, it2--;
        if (-it2->second > nw) {it2->second += nw; break;}
    }
}
void dfs(int u, int fa) {
    rt[u] = u;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != fa) dfs(e[i].to, u), merge(u, e[i].to);
    int t = rt[u]; map<int, LL>::iterator it;
    if (f[t].count(a[u])) it = f[t].find(a[u]), it->second -= b[u], update(u, it);
    else f[t][a[u]] = -b[u], update(u, f[t].find(a[u]));
} 
#define OPEN(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
int main() {
	OPEN("cave20");
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), adde(a, b);
    dfs(1, 0); long long res = 0;
    for (map<int, LL>::iterator it = f[rt[1]].begin(); it != f[rt[1]].end(); it++) res -= it->second;
    printf("%lld\n", res);
    cerr << res << endl;
    return 0;
}
