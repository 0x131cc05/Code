#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;
typedef pair<int, LL> P;

/**
 * dis1(a, b) + dep2[a] + dep2[b] - 2dep2[lca2(a, b)] + dis3(a, b)
 * 对T1边分治，在T2上合并边分树，维护T3的加权直径
 */

// 三度化
struct edge {
    int to, next; LL w;
} e[N * 4];

int head[N * 2], ecnt = 1, ncnt;

inline void adde(int from, int to, LL w) {
//    cout << "--adde: " << from << ' ' << to << ' ' << w << endl;
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

vector<P> G1[N], G2[N], G3[N];

void Rebuild(int u, int f) {
    int last = u, t = 0;
    for (auto v : G1[u]) if (v.first != f) t = v.first;
    for (auto v : G1[u]) if (v.first != f) {
        Rebuild(v.first, u), adde(last, v.first, v.second);
        if (v.first != t) adde(last, ++ncnt, 0), last = ncnt;
    }
}

// T2, T3
LL dep2[N], dep3[N]; int dep[N];

int st[18][N * 2], lg[N * 2];

void dfs1(int u, int f) {
    for (auto v : G2[u]) if (v.first != f) 
        dep2[v.first] = dep2[u] + v.second, dfs1(v.first, u);
}

int dfn, fir[N * 2];

void dfs2(int u, int f) {
    st[0][++dfn] = u, fir[u] = dfn, dep[u] = dep[f] + 1;
    for (auto v : G3[u]) if (v.first != f) 
        dep3[v.first] = dep3[u] + v.second, dfs2(v.first, u), st[0][++dfn] = u;
}

inline int Min(int &x, int &y) {
    return dep[x] < dep[y] ? x : y;
}

inline void ST() {
    for (int i = 1; i <= 17; i++)
        for (int j = 1; j + (1 << i) - 1 <= dfn; j++)
            st[i][j] = Min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
    for (int i = 2; i <= dfn; i++) lg[i] = lg[i >> 1] + 1;
}

// LCA on T3
inline int LCA(int a, int b) {
    if (a == b) return a;
    a = fir[a], b = fir[b];
    if (a > b) swap(a, b);
    int len = lg[b - a + 1];
    return Min(st[len][a], st[len][b - (1 << len) + 1]);
}

inline LL Dis(int a, int b) {
    return dep3[a] + dep3[b] - 2 * dep3[LCA(a, b)];
}

// 合并直径
struct data {
    int a, b; LL A, B, dis;
} val[2][N * 30];

inline data Max(data a, data b) {
    return a.dis > b.dis ? a : b;
}

LL ans = 0;

inline data Merge(data a, data b, LL diff) {
    if ((!a.a) || (!b.a)) return a.a ? a : b;
    static LL tmp[4]; int pos = 0;
    tmp[0] = Dis(a.a, b.a) + a.A + b.A, tmp[1] = Dis(a.a, b.b) + a.A + b.B;
    tmp[2] = Dis(a.b, b.a) + a.B + b.A, tmp[3] = Dis(a.b, b.b) + a.B + b.B;
    for (int i = 1; i < 4; i++) if (tmp[i] > tmp[pos]) pos = i;
    data res = (data){ (pos & 2) ? a.b : a.a, (pos & 1) ? b.b : b.a, (pos & 2) ? a.B : a.A, (pos & 1) ? b.B : b.A, tmp[pos] };
    if (diff != 233) ans = max(ans, tmp[pos] + diff); 
    return Max(res, Max(a, b));
}

// 边分治
int sz[N * 2], cur, fucked[N * 4], n, ch[2][N * 30]; 

int lst[N * 2], lst1[N * 2], RT[N * 2], tot;

void dfs(int u, int f, int nw, LL dis) {
    sz[u] = 1;
    if (u <= n) {
        if (!lst[u]) lst[u] = RT[u] = ++tot;
        else tot++, ch[lst1[u]][lst[u]] = tot, lst[u] = tot;
//        cout << "fuck: " << u << ' ' << dis << ' ' << dep2[u] << endl;
        lst1[u] = nw, val[nw][tot] = (data){ u, u, dis + dep2[u], dis + dep2[u], dis * 2 + dep2[u] * 2 };
    }
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !fucked[i]) dfs(e[i].to, u, nw, dis + e[i].w), sz[u] += sz[e[i].to];
}

void Merge(int &rt1, int rt2, LL diff) {
    if ((!rt1) || (!rt2)) return rt1 |= rt2, void();
//    cout << ch[0][rt1] << ' ' << ch[1][rt1] << ' ' << ch[0][rt2] << ' ' << ch[1][rt2] << endl;
    Merge(val[0][rt1], val[1][rt2], diff), Merge(val[1][rt1], val[0][rt2], diff);
    val[0][rt1] = Merge(val[0][rt1], val[0][rt2], 233), val[1][rt1]= Merge(val[1][rt1], val[1][rt2], 233);
    Merge(ch[0][rt1], ch[0][rt2], diff), Merge(ch[1][rt1], ch[1][rt2], diff);
}

int tmp = 1e9;

// 找中心边
void GetEG(int u, int f, int tot) {
    sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !fucked[i]) {
            GetEG(e[i].to, u, tot), sz[u] += sz[e[i].to];
            if (abs(tot - 2 * sz[e[i].to]) < tmp) 
                tmp = abs(tot - 2 * sz[e[i].to]), cur = i;
        } 
}

void Divide(int ed) {
//    cout << "--find: " << e[ed].to << ' ' << e[ed ^ 1].to << endl;
    fucked[ed] = fucked[ed ^ 1] = 1, dfs(e[ed].to, 0, 0, 0), dfs(e[ed ^ 1].to, 0, 1, e[ed].w);
    auto find = [&](int u) -> int {
        cur = -1, tmp = 1e9, GetEG(u, 0, sz[u]);
        return cur;
    };
    int L = find(e[ed].to), R = find(e[ed ^ 1].to);
    if (~L) Divide(L); if (~R) Divide(R);
//    cout << "--end" << endl;
}

inline void Divide() {
    ncnt = n, Rebuild(1, 0), tmp = 1e9, GetEG(1, 0, n), Divide(cur);
}

void dfs3(int u, int f) {
    for (auto v : G2[u]) if (v.first != f) 
        dfs3(v.first, u), Merge(RT[u], RT[v.first], -2 * dep2[u]);
}

template<class T> inline void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
    int a, b; LL c; read(n);
    for (int i = 1; i < n; i++) {
        read(a), read(b), read(c);
        G1[a].push_back(P(b, c)), G1[b].push_back(P(a, c));
    }
    for (int i = 1; i < n; i++) {
        read(a), read(b), read(c);
        G2[a].push_back(P(b, c)), G2[b].push_back(P(a, c));
    }
    for (int i = 1; i < n; i++) {
        read(a), read(b), read(c);
        G3[a].push_back(P(b, c)), G3[b].push_back(P(a, c));
    }
    dfs1(1, 0), dfs2(1, 0), ST(), Divide(), dfs3(1, 0);
//    Merge(RT[2], RT[3], 0);
    printf("%lld\n", ans);
    return 0;
}
