#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

struct edge {
    int to, next; LL w;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to, LL w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

set<LL> one[N];

int tag[N], rt[N];

void insert(int u, LL x) {
    LL pos = x - tag[u];
    while (one[u].count(pos)) 
        one[u].erase(pos), pos++;
    one[u].insert(pos);
}

int calc(int u) {
    int res = 0;
    for (auto t : one[rt[u]]) res = (res + Pow(2, (tag[rt[u]] + t) % (mod - 1))) % mod;
    return res;
}

bool cmp(int u, int v) { // u > v
    auto p1 = one[u].rbegin(), p2 = one[v].rbegin();
    while (233) {
        if (p1 == one[u].rend()) return false;
        if (p2 == one[v].rend()) return true;
        if (*p1 + tag[u] != *p2 + tag[v]) 
            return *p1 + tag[u] > *p2 + tag[v];
        p1++, p2++;
    }
}

void merge(int u, int v) {
    if (one[rt[u]].size() < one[rt[v]].size()) swap(rt[u], rt[v]);
    for (auto t : one[rt[v]]) insert(rt[u], t + tag[rt[v]]);
    one[rt[v]].clear();
}

void dfs(int u, int f, LL w) {
    rt[u] = u; int mx = 0;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u, e[i].w);
            if (!mx || cmp(rt[e[i].to], rt[mx])) mx = e[i].to;
        }
    if (mx) tag[rt[mx]]++;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) merge(u, e[i].to);
    if (f) insert(rt[u], w);
}

int main() {
    int n; LL b; scanf("%d", &n);
    for (int i = 2, a; i <= n; i++) scanf("%d%lld", &a, &b), adde(a, i, b);
    dfs(1, 0, 0), printf("%d\n", calc(1));
}
