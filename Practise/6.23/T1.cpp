#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;
typedef pair<int, int> P;

struct cir {
    int x, y, r, w;
} c[N];

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

int cur;

struct arc {
    int id, type; 
    double get(int pos) const {
        int diff = abs(pos - c[id].x);
        double t = sqrt((LL)c[id].r * c[id].r - (LL)diff * diff);
        return type ? c[id].y + t : c[id].y - t;
    }
    bool operator < (const arc &b) const {
        if (id == b.id) return type < b.type;
        return get(cur) < b.get(cur);
    }
};

set<arc> s;

int fa[N], _fa[N];

int find(int x) {
    return x == _fa[x] ? x : _fa[x] = find(_fa[x]);
}

int main() {
    freopen("circle.in", "r", stdin), freopen("circle.out", "w", stdout);
    int n; scanf("%d", &n);
    vector<P> event;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &c[i].x, &c[i].y, &c[i].r, &c[i].w), val[i] = c[i].w;
        event.push_back(P(i, 0)), event.push_back(P(i, 1));
    }
    auto fuck = [&](P x) {
        return x.second ? c[x.first].x + c[x.first].r : c[x.first].x - c[x.first].r;
    };
    sort(event.begin(), event.end(), [&](P a, P b) {
        return fuck(a) < fuck(b);
    });
    for (int i = 1; i <= n; i++) _fa[i] = i;
    for (auto t : event) {
        cur = fuck(t);
        int id = t.first, tp = t.second;
        if (tp == 0) {
            s.insert({ id, 1 });
            s.insert({ id, 0 });
        } else {
            auto pos = s.find({ id, 1 }); pos++;
            if (pos != s.end()) {
                if (pos->type == 1) fa[id] = pos->id;
                else _fa[find(id)] = find(pos->id);
            }
            pos--, s.erase(pos);
            s.erase({ id, 0 });
        }
    }
    for (int i = 1; i <= n; i++)
        fa[i] = fa[find(i)], adde(i, fa[i]);
    dfs(0, 0), printf("%d\n", dp[0]);
}

