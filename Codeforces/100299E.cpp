#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 200010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

struct wkr {
    LL a, b; int pos;

    bool operator < (const wkr &t) const {
        LL t1 = max(a, t.a - b), t2 = max(t.a, a - t.b);
        return t1 != t2 ? t1 < t2 : pos < t.pos;
    }
} w[N];

wkr merge(wkr a, wkr b) {
    return (wkr){ max(a.a, b.a - a.b), a.b + b.b, a.pos };
}

int fa[N];

void dfs(int u, int f) {
    fa[u] = f;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u);
}

struct DSU {
    int fa[N];

    void init(int n) {
        for (int i = 1; i <= n; i++) 
            fa[i] = i;
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    void merge(int x, int y) {
        fa[find(x)] = find(y);
    }
} D;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n, t; scanf("%d%d", &n, &t), ecnt = 0;
        for (int i = 1; i <= n; i++) head[i] = 0;
        set<wkr> s;
        for (int i = 1; i <= n; i++) {
            int a; scanf("%d", &a);
            s.insert(w[i] = (wkr){ max(0, -a), a + (i == t ? (LL)1e13 : 0), i });
        }
        for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), adde(a, b);
        dfs(1, 0), D.init(n);
        while (!s.empty()) {
            auto t = *s.begin(); s.erase(t);
            int u = t.pos, f = D.find(fa[u]);
            // cout << u << endl;
            if (f) {
                s.erase(w[f]);
                w[f] = merge(w[f], t);
                s.insert(w[f]), D.merge(u, f);
                // cout << "merge:" << u << ' ' << f << endl;
            }
        }
        puts(w[1].a <= 0 ? "escaped" : "trapped");
    }
}