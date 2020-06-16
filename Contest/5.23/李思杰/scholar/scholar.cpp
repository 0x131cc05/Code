#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
const int mod = 1e9 + 7;

typedef long long LL;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){to, head[from]}, head[from] = ecnt;
    e[++ecnt] = (edge){from, head[to]}, head[to] = ecnt;
}

int val[N], now[N], before[N], after[N], buk[N];

inline int Add(int x, int y) {
    int res = x + y;
    if (res >= mod) res -= mod;
    return res;
}

void dfs1(int u, int f) {
    int ls = buk[now[u]];
    before[u] = buk[val[u] - 1], after[u] = buk[now[u] - 1];
    buk[now[u]] = Add(buk[now[u]], buk[now[u] - 1]);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs1(e[i].to, u);
    buk[now[u]] = ls;
}

int n, m, L;

int buk2[N];

void dfs2(int u, int f) {
    int ls = buk2[val[u] + 1], ls2 = buk2[now[u] + 1];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) 
            dfs2(e[i].to, u);
    int t1 = buk2[val[u] + 1] - ls, t2 = buk2[now[u] + 1] - ls2;
    if (val[u] == L) t1 = 1;
    if (now[u] == L) t2 = 1;
    before[u] = (LL)before[u] * t1 % mod, after[u] = (LL)after[u] * t2 % mod;
    buk2[val[u]] += t1;
    if (buk2[val[u]] >= mod) buk2[val[u]] -= mod;
    else if (buk2[val[u]] < 0) buk2[val[u]] += mod;
}

int v[N * 2], ans, res = 0;

inline void work(int st) {
    for (int i = 1; i <= L; i++) buk2[i] = 0;
    for (int i = 1; i <= n; i++) {
        val[i] = now[i];
        if (st + i - 1 > m) now[i] = val[i];
        else now[i] = v[st + i - 1]; 
    }
    dfs1(1, 0), dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        if (st + i - 1 > m) break;
        ans = ans - before[i] + after[i];
        if (ans >= mod) ans -= mod;
        else if (ans < 0) ans += mod;
        if (L == 1) ans = n;
        res = (res + (LL)(st + i - 1) * ans) % mod;
    }
}

int tmp[N];

void dfs3(int u, int f) {
    if (now[u] == L) ans = (ans + tmp[L - 1]) % mod;
    int ls = tmp[now[u]];
    if (now[u] == 1) tmp[1]++;
    else tmp[now[u]] = (tmp[now[u]] + tmp[now[u] - 1]) % mod;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs3(e[i].to, u);
    tmp[now[u]] = ls;
}

template<class T> inline void read(T &x) {
    x = 0; char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = getchar();
}

int main() {
    freopen("scholar.in", "r", stdin), freopen("scholar.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &L); 
    for (int i = 2, f; i <= n; i++) read(f), adde(f, i);
    for (int i = 1; i <= n; i++) read(now[i]), now[i] = L - now[i] + 1;
    dfs3(1, 0), buk[0] = 1;
    for (int i = 1; i <= m; i++) read(v[i]), v[i] = L - v[i] + 1;
    for (int i = 1; i <= m; i += n) work(i);
    printf("%d\n", (res + mod) % mod);
}
