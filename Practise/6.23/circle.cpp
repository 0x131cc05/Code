#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;
typedef pair<int, int> P;

struct cir {
    int x, y, r, w;
} c[N];

bool check(int x, int y, cir c) {
    LL tmp = (LL)(x - c.x) * (x - c.x) + (LL)(y - c.y) * (y - c.y);
    return tmp < (LL)c.r * c.r;
}

struct edge {
    int to, next; 
} e[N * 2];

int head[N], ecnt, val[N], dp[N];

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

void dfs(int u, int f) {
    for (int i = head[u]; i; i = e[i].next) 
        if (e[i].to != f) 
            dfs(e[i].to, u), dp[u] += dp[e[i].to];
    dp[u] = max(dp[u], val[u]);
}

int fa[N];

struct node {
    int l, r; set<P> s;
} T[N << 2];

vector<int> seg;

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
}

void update(int rt, int x, P v, int type) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (type) T[rt].s.insert(v);
    else T[rt].s.erase(v);
    if (l == r) return;
    if (x <= mid) update(rt << 1, x, v, type);
    else update(rt << 1 | 1, x, v, type);
}

void query(int rt, int start, int end) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) { seg.push_back(rt); return; }
    if (start <= mid) query(rt << 1, start, end);
    if (end > mid) query(rt << 1 | 1, start, end);
}

int pos[N];

template<class T> void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
    freopen("circle.in", "r", stdin), freopen("circle.out", "w", stdout);
    int n; read(n);
    for (int i = 1; i <= n; i++) 
        read(c[i].x), read(c[i].y), read(c[i].r), read(c[i].w);
    sort(c + 1, c + n + 1, [&](cir a, cir b) {
        return a.r < b.r;
    });
    if (n <= 5000) {
        for (int i = 1; i <= n; i++) 
            for (int j = 1; j < i; j++) if (!fa[j] && check(c[j].x, c[j].y, c[i])) 
                fa[j] = i;
    } else {
        vector<int> X;
        for (int i = 1; i <= n; i++) X.push_back(c[i].x);
        sort(X.begin(), X.end()), X.resize(unique(X.begin(), X.end()) - X.begin());
        int all = X.size(); build(1, 1, all);
        for (int i = 1; i <= n; i++) {
            int l = c[i].x - c[i].r, r = c[i].x + c[i].r;
            l = lower_bound(X.begin(), X.end(), l) - X.begin() + 1;
            r = upper_bound(X.begin(), X.end(), r) - X.begin();
            if (l <= r) {
                seg.clear(), query(1, l, r);
                vector<int> del;
                for (auto rt : seg) {
                    int d = 0;
                    if (X[T[rt].r - 1] < c[i].x) 
                        d = c[i].x - X[T[rt].r - 1];
                    if (X[T[rt].l - 1] > c[i].x)
                        d = X[T[rt].l - 1] - c[i].x;
                    d = ceil(sqrt((LL)c[i].r * c[i].r - (LL)d * d));
                    auto pos = T[rt].s.upper_bound(P(c[i].y - d, -1e9));
                    while (pos != T[rt].s.end()) {
                        if (pos->first >= c[i].y + d) break;
                        int id = pos->second;
                        if (check(c[id].x, c[id].y, c[i])) del.push_back(id);
                        pos++;
                    }
                }
                for (auto t : del) 
                    update(1, pos[t], P(c[t].y, t), 0), fa[t] = i;
            }
            pos[i] = lower_bound(X.begin(), X.end(), c[i].x) - X.begin() + 1;
            update(1, pos[i], P(c[i].y, i), 1);
        }
    }
    for (int i = 1; i <= n; i++) val[i] = c[i].w;
    for (int i = 1; i <= n; i++) adde(fa[i], i);
    dfs(0, 0), printf("%d\n", dp[0]);
}