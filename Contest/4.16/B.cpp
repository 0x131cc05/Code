#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to, int w) {
    e[++ecnt] = (edge){to, head[from], w}, head[from] = ecnt;
    e[++ecnt] = (edge){from, head[to], w}, head[to] = ecnt;
}

int l[N], r[N], mx = 0;

void dfs(int u, int f, int w) {
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u, e[i].w);
            l[u] = max(l[u], l[e[i].to]), r[u] = min(r[u], r[e[i].to]);
        }
    mx = max(mx, l[u] - r[u]);
    l[u] -= w, r[u] += w;
}


inline char gc() {
    static const int IN_LEN = 1 << 18 | 1;
    static char buf[IN_LEN], *s, *t;
    return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)), s == t ? -1 : *s++;
}

template<class T> inline void read(T &x) {
    x = 0; char c = gc(); bool flag = false;
    while (!isdigit(c)) flag |= c == '-', c = gc();
    while (isdigit(c)) x = x * 10 + c - '0', c = gc();
    if (flag) x = -x;
}

int main() {
//    freopen("data.in", "r", stdin);
    int type, T, n; scanf("%d%d", &T, &type);
    while (T--) {
        memset(head, 0, sizeof(head)), ecnt = mx = 0, read(n);
        for (int i = 1; i <= n; i++) read(l[i]);
        for (int i = 1; i <= n; i++) read(r[i]);
        for (int i = 1, a, b, c; i < n; i++) read(a), read(b), read(c), adde(a, b, c);
        dfs(1, 0, 0); int ans = (mx + 1) / 2;
        if (type) printf("%d\n", ans);
        else printf("%d\n", !!ans);
    }
    return 0;
}
