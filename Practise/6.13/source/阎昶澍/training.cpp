#include <bits/stdc++.h>
using namespace std;
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define loop(i, a) for (int i = 0; i < (a); ++i)
#define cont(i, a) for (int i = 1; i <= (a); ++i)
#define circ(i, a, b) for (int i = (a); i <= (b); ++i)
#define range(i, a, b, c) for (int i = (a); (c) > 0 ? i <= (b) : i >= (b); i += (c))
#define parse(it, x) for (auto &it : (x))
#define pub push_back
#define pob pop_back
#define emb emplace_back
#define mak make_pair
#define mkt make_tuple
typedef long long ll;
typedef long double lf;
const int Inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

int n, m;
vector<int> nei[1005], son[1005];
vector<pair<pair<int, int>, int> > fes, fe[1005];
int Fa[15][1005], *fa = Fa[0], lvl[1005], sid[1005][1005];
vector<int> hou[1005];

void inline predfs(int now, int lst) {
    fa[now] = lst;
    cont(i, 11) Fa[i][now] = Fa[i - 1][Fa[i - 1][now]];
    lvl[now] = lvl[lst] + 1;
    hou[now].pub(now);
    loop(i, SZ(nei[now])) {
        int to = nei[now][i];
        if (to == lst) continue;
        predfs(to, now);
        parse(it, hou[to]) sid[now][it] = SZ(son[now]);
        hou[now].insert(hou[now].end(), hou[to].begin(), hou[to].end());
        son[now].pub(to);
    }
}

int inline lca(int a, int b) {
    if (lvl[a] < lvl[b]) swap(a, b);
    int toup = lvl[a] - lvl[b];
    loop(i, 12) if ((toup >> i) & 1) a = Fa[i][a];
    if (a == b) return a;
    range(i, 11, 0, -1) if (Fa[i][a] != Fa[i][b]) a = Fa[i][a], b = Fa[i][b];
    return fa[a];
}

int f[1005][15], g[1005];
int dp[1024], tmp[1024];

void dfs(int now) {
    int ss = SZ(son[now]), ful = (1 << ss) - 1;
    parse(to, son[now]) dfs(to);
    memset(tmp, 0, sizeof(int) * (1 << ss));
    loop(i, 1 << ss) loop(j, ss) if ((i >> j) & 1) tmp[i] += g[son[now][j]];
    memset(dp, 0, sizeof(int) * (1 << ss));
    parse(it, fe[now]) {
        int u = it.first.first, v = it.first.second, w = it.second;
        int res = w;
        if (u != now) res += g[u];
        if (v != now) res += g[v];
        while (u != now && fa[u] != now) {
            int t = fa[u];
            res += f[t][sid[t][u]];
            u = t;
        }
        while (v != now && fa[v] != now) {
            int t = fa[v];
            res += f[t][sid[t][v]];
            v = t;
        }
        int msk = 0;
        if (u != now) msk |= 1 << sid[now][u];
        if (v != now) msk |= 1 << sid[now][v];
        dp[msk] = max(dp[msk], res);
    }
    loop(i, 1 << ss) for (int j = i & (i - 1); j; j = (j - 1) & i) {
        dp[i] = max(dp[i], dp[j] + dp[i ^ j]);
    }
    loop(i, ss) loop(j, 1 << ss) if (!((j >> i) & 1)) f[now][i] = max(f[now][i], dp[j] + tmp[ful ^ j ^ (1 << i)]);
    loop(j, 1 << ss) g[now] = max(g[now], dp[j] + tmp[ful ^ j]);
}

int main() {
    #ifndef Acetyl
    freopen("training.in", "r", stdin);
    freopen("training.out", "w", stdout);
    #endif
    scanf("%d%d", &n, &m);
    cont(i, m) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        if (!w) {
            nei[u].pub(v);
            nei[v].pub(u);
        }
        else fes.emb(mak(u, v), w);
    }
    predfs(1, 0);
    int ans = 0;
    parse(it, fes) {
        int u = it.first.first, v = it.first.second;
        ans += it.second;
        if ((lvl[u] + lvl[v]) & 1) continue;
        int c = lca(u, v);
        fe[c].pub(it);
    }
    dfs(1);
    printf("%d\n", ans - g[1]);
    return 0;
}
/*

5 8
2 1 0
3 2 0
4 3 0
5 4 0
1 3 2
3 5 2
2 4 5
2 5 1

15 25
7 10 4
13 5 0
12 6 1
10 9 4
3 15 9
5 12 3
3 10 0
8 1 0
15 2 8
11 7 3
14 11 0
15 11 7
2 4 5
3 6 0
2 7 0
1 4 0
9 3 0
14 7 6
5 14 0
3 12 0
7 13 0
5 8 7
5 1 0
15 7 0
14 3 0

*/