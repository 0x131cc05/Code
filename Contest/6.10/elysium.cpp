#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

#pragma GCC optimize("Ofast")

typedef long long LL;
typedef pair<int, int> P;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
} 

int ls[N * 23], rs[N * 23], ncnt, fir[N * 23]; LL val[N * 23];

queue<int> buff;

inline int wkr() {
    if (buff.size()) {
        int t = buff.front(); buff.pop();
        ls[t] = rs[t] = val[t] = 0, fir[t] = 1e9; return t;
    }
    return fir[ncnt + 1] = 1e9, ++ncnt;
}

void insert(int &rt, int l, int r, int pos, int x) {
    if (!rt) rt = wkr();
    val[rt] += x, fir[rt] = min(fir[rt], pos);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) insert(ls[rt], l, mid, pos, x);
    else insert(rs[rt], mid + 1, r, pos, x);
}

void merge(int &x, int y, int l, int r) {
    if (!x || !y) return x |= y, void();
    val[x] += val[y], fir[x] = min(fir[x], fir[y]), buff.push(y);
    if (l == r) return;
    int mid = (l + r) >> 1;
    merge(ls[x], ls[y], l, mid), merge(rs[x], rs[y], mid + 1, r);
}

int flow, res;

inline void pushup(int rt) {
    val[rt] = val[ls[rt]] + val[rs[rt]], fir[rt] = 1e9;
    if (ls[rt]) fir[rt] = fir[ls[rt]];
    if (rs[rt]) fir[rt] = min(fir[rt], fir[rs[rt]]);
}

void go(int rt, int l, int r, int end) {
    if (!rt || !flow || !val[rt]) return;
    if (fir[rt] > end) return;
    if (l == r) {
        int t = min((LL)flow, val[rt]);
        flow -= t, val[rt] -= t, res += t;
        if (!val[rt]) fir[rt] = 1e9;
        return;
    }
    int mid = (l + r) >> 1;
    if (val[rs[rt]]) go(rs[rt], mid + 1, r, end);
    if (flow) go(ls[rt], l, mid, end);
    pushup(rt);
}

int RT[N], v[N], n, dep[N];

vector<P> p[N]; LL ans = 0;

void dfs(int u, int f) {
    dep[u] = dep[f] + 1, insert(RT[u], 1, n, dep[u], v[u]);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) 
            dfs(e[i].to, u), merge(RT[u], RT[e[i].to], 1, n);
    for (auto t : p[u]) 
        res = 0, flow = t.second, go(RT[u], 1, n, dep[u] + t.first), ans += res;
}

inline char gc() {
    static char buf[1000000], *p1, *p2;
    if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin);
    return p1 == p2 ? EOF : *p1++;
}

template<class T> inline void read(T &x) {
    x = 0; char c = gc();
    while (!isdigit(c)) c = gc();
    while (isdigit(c)) x = x * 10 + c - '0', c = gc();
}

int main() {
//    freopen("elysium.in", "r", stdin), freopen("elysium.out", "w", stdout);
    int m; read(n), read(m); LL tot = 0;
    for (int i = 2, f; i <= n; i++) read(f), adde(f, i);
    for (int i = 1; i <= n; i++) read(v[i]), tot += v[i];
    while (m--) {
        int x, d, c; read(x), read(d), read(c);
        p[x].push_back(P(d, c));
    }
    for (int i = 1; i <= n; i++) if (p[i].size())
        sort(p[i].begin(), p[i].end(), [](P a, P b) {
            return a.first > b.first;
        });
    dfs(1, 0);
    printf("%lld\n", tot - ans);
}
