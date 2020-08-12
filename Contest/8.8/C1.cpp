#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef long long LL;
typedef vector<LL> vec;

struct edge {
    int to, next, w;
} e[N * 2];
int head[N], ecnt;
void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

void getDiff(vec &a) { for (int i = a.size() - 1; i; i--) a[i] -= a[i - 1]; }
void reduce(vec &a) { for (int i = 1; i < a.size(); i++) a[i] += a[i - 1]; }
vec maxConv(vec a, vec b) {
    getDiff(a), getDiff(b);
    vec res = { a[0] + b[0] }; 
    merge(a.begin() + 1, a.end(), b.begin() + 1, b.end(), back_inserter(res), [](LL a, LL b){ return a > b; });
    return reduce(res), res;
}
vec maxVec(vec a, vec b) {
    vec res;
    for (int i = 0; i < max(a.size(), b.size()); i++) {
        if (i >= a.size()) res.push_back(b[i]);
        else if (i >= b.size()) res.push_back(a[i]);
        else res.push_back(max(a[i], b[i]));
    }
    return res;
}
vec addWithShift(vec a, int x) {
    vec res = { -(LL)1e17 };
    for (int i = 0; i < a.size(); i++)
        res.push_back(a[i] + x);
    return res;
}

int sz[N], son[N], fa[N], val[N];
void dfs(int u, int f) {
    fa[u] = f, sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            val[e[i].to] = e[i].w, dfs(e[i].to, u), sz[u] += sz[e[i].to];
            if (sz[son[u]] < sz[e[i].to]) 
                son[u] = e[i].to;
        }
}

vec dp[N][2], tmp, wkr[N << 2][2], zjk[N << 2][2][2];
void solve(int rt, int l, int r) {
    if (l > r) return;
    if (l == r) return wkr[rt][0] = maxVec(dp[tmp[l]][0], dp[tmp[l]][1]), wkr[rt][1] = addWithShift(dp[tmp[l]][0], val[tmp[l]]), void();
    int mid = (l + r) >> 1;
    solve(rt << 1, l, mid), solve(rt << 1 | 1, mid + 1, r);
    wkr[rt][0] = maxConv(wkr[rt << 1][0], wkr[rt << 1 | 1][0]);
    wkr[rt][1] = maxVec(maxConv(wkr[rt << 1][1], wkr[rt << 1 | 1][0]), maxConv(wkr[rt << 1][0], wkr[rt << 1 | 1][1]));
}
void mergeSon(int u) {
    tmp.clear(), wkr[1][0] = { 0 }, wkr[1][1] = { (LL)-1e17 };
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != son[u] && e[i].to != fa[u]) tmp.push_back(e[i].to);
    solve(1, 0, tmp.size() - 1);
}

void solve1(int rt, int l, int r) {
    if (l > r) return;
    if (l == r) {
        zjk[rt][0][0] = dp[tmp[l]][0], zjk[rt][1][1] = dp[tmp[l]][1];
        zjk[rt][0][1] = zjk[rt][1][0] = { (LL)-1e17 };
        return;
    }
    int mid = (l + r) >> 1;
    solve1(rt << 1, l, mid), solve1(rt << 1 | 1, mid + 1, r);
    zjk[rt][0][0] = zjk[rt][0][1] = zjk[rt][1][0] = zjk[rt][1][1] = { -(LL)1e17 };
    for (int a = 0; a <= 1; a++)
        for (int b = 0; b <= 1; b++)
            for (int c = 0; c <= 1; c++)
                for (int d = 0; d <= 1; d++) {
                    vec t = maxConv(zjk[rt << 1][a][b], zjk[rt << 1 | 1][c][d]);
                    zjk[rt][a][d] = maxVec(zjk[rt][a][d], t);
                    if (!b && !c) {
                        int ta = a | (l == mid), td = d | (r == mid + 1);
                        zjk[rt][ta][td] = maxVec(zjk[rt][ta][td], addWithShift(t, val[tmp[mid + 1]]));
                    }
                }
}
void mergeChain(int u, int t) {
    tmp.clear();
    for (int v = u; v; v = fa[v]) {
        tmp.push_back(v);
        if (v == t) break;
    }
    reverse(tmp.begin(), tmp.end());
    solve1(1, 0, tmp.size() - 1);
    dp[t][0] = maxVec(zjk[1][0][1], zjk[1][0][0]), dp[t][1] = maxVec(zjk[1][1][0], zjk[1][1][1]);
} 

void dfs1(int u, int t) {
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != fa[u] && e[i].to != son[u]) 
            dfs1(e[i].to, e[i].to);
    if (!son[u]) {
        dp[u][0] = { 0 }, dp[u][1] = { (LL)-1e17 }, mergeChain(u, t);
    } else {
        mergeSon(u), dp[u][0] = wkr[1][0], dp[u][1] = wkr[1][1];
        dfs1(son[u], t);
    }
}

int main() {
    int n, l, r; scanf("%*d%d%d%d", &n, &l, &r);
    for (int i = 1, a, b, c; i < n; i++) scanf("%d%d%d", &a, &b, &c), adde(a, b, c);
    dfs(1, 0), dfs1(1, 1);
    for (int i = l; i <= r; i++) {
        LL a = i < dp[1][0].size() ? dp[1][0][i] : (LL)-1e17, b = i < dp[1][1].size() ? dp[1][1][i] : (LL)-1e17;
        if (max(a, b) < -1e16) printf("- ");
        else printf("%lld ", max(a, b));
    }
}
