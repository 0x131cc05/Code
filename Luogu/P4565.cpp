#include <bits/stdc++.h>
using namespace std;

const int N = 400010;

typedef pair<int, int> P;
typedef long long LL;

/*
 * dis1(a, b) + dep1[a] + dep1[b] - dep2[lca(a, b)]
 * 对T1建边分树，维护左右儿子的dep1 + dis1(a, t0 / t1)的最大值
 * 对T2dfs，同时合并对应的边分树
 */

// 三度化之后的树
struct edge {
    int to, next, w;
} e[N * 4];

int head[N * 2], ecnt = 1, ncnt;

inline void adde(int from, int to, int w) {
    // cout << "adde: " << from << ' ' << to << ' ' << w << endl;
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

// T1, T2
vector<P> G1[N], G2[N];

// 每个点在T1中的深度
LL dep[N];

// 三度化
void Rebuild(int u, int f) {
    int last = u;
    for (auto v : G1[u]) if (v.first != f) {
        dep[v.first] = dep[u] + v.second, Rebuild(v.first, u), adde(last, v.first, v.second);
        adde(last, ++ncnt, 0), last = ncnt;
    }
}

int sz[N * 2], cur, fucked[N * 4], n; LL ans = -1e18;

// 边分树结构
int lst[N], lst1[N], tot, tmp = 1e9, RT[N], ch[2][N * 30]; LL val[2][N * 30];

// 对T1中的每个点单独求出其在边分树上的链
void dfs(int u, int f, int nw, LL dis) {
    sz[u] = 1;
    if (u <= n) {
        if (!lst[u]) lst[u] = RT[u] = ++tot;
        else ch[lst1[u]][lst[u]] = ++tot, lst[u] = tot;
        lst1[u] = nw, val[nw][lst[u]] = dis + dep[u], val[nw ^ 1][lst[u]] = -1e18;
    }
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !fucked[i]) 
            dfs(e[i].to, u, nw, dis + e[i].w), sz[u] += sz[e[i].to];
}

// 合并边分树
void Merge(int &rt1, int rt2, LL diff) {
    if (!rt1 || !rt2) return rt1 |= rt2, void();
    ans = max(ans, max(val[0][rt1] + val[1][rt2] + diff, val[1][rt1] + val[0][rt2] + diff));
    val[0][rt1] = max(val[0][rt1], val[0][rt2]), val[1][rt1] = max(val[1][rt1], val[1][rt2]);
    Merge(ch[0][rt1], ch[0][rt2], diff), Merge(ch[1][rt1], ch[1][rt2], diff);
}

// 找中心边
void GetEG(int u, int f, int tot) {
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !fucked[i]) {
            GetEG(e[i].to, u, tot);
            if (abs(tot - 2 * sz[e[i].to]) < tmp) 
                tmp = abs(tot - 2 * sz[e[i].to]), cur = i;
        } 
}

void Divide(int ed) {
    fucked[ed] = fucked[ed ^ 1] = 1, dfs(e[ed].to, 0, 0, 0), dfs(e[ed ^ 1].to, 0, 1, e[ed].w);
    auto find = [&](int u) -> int {
        cur = -1, tmp = 1e9, GetEG(u, 0, sz[u]);
        return cur;
    };
    int L = find(e[ed].to), R = find(e[ed ^ 1].to);
    if (~L) Divide(L); if (~R) Divide(R);
}

inline void Divide() {
    ncnt = n, Rebuild(1, 0), tmp = 1e9, GetEG(1, 0, n), Divide(cur);
}

// 在T2上边分树合并
void dfs(int u, int f, LL dis) {
    ans = max(ans, dep[u] * 2 - dis * 2);
    for (auto v : G2[u]) if (v.first != f) 
        dfs(v.first, u, dis + v.second), Merge(RT[u], RT[v.first], -dis * 2);
}

int main() {
    scanf("%d", &n);
    for (int i = 1, a, b, c; i < n; i++) {
        scanf("%d%d%d", &a, &b, &c);
        G1[a].push_back(P(b, c)), G1[b].push_back(P(a, c));
    } 
    for (int i = 1, a, b, c; i < n; i++) {
        scanf("%d%d%d", &a, &b, &c);
        G2[a].push_back(P(b, c)), G2[b].push_back(P(a, c));
    }
    Divide(), dfs(1, 0, 0), printf("%lld\n", ans / 2);
    return 0;
}