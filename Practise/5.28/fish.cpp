#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
const int M = 20000010;

typedef long long LL;

const LL INF = 1e12;

typedef pair<int, int> P;

struct edge {
    int to, next; LL w;
} e[M];

int head[N], ecnt = 1, ncnt;

void adde(int from, int to, LL w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], 0 }, head[to] = ecnt;
}

int dep[N], cur[N];

bool BFS(int s, int t) {
    for (int i = 1; i <= ncnt; i++) dep[i] = -1;
    dep[t] = 0; queue<int> q; q.push(t);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next)
            if (e[i ^ 1].w && dep[e[i].to] == -1) {
                dep[e[i].to] = dep[u] + 1;
                if (e[i].to == s) return true;
                q.push(e[i].to);
            }
    }
    return false;
}

LL DFS(int u, LL f, int t) {
    if (u == t || !f) return f;
    LL res = 0, tmp;
    for (int &i = cur[u]; i; i = e[i].next)
        if (e[i].w && dep[e[i].to] == dep[u] - 1 && (tmp = DFS(e[i].to, min(f, e[i].w), t))) {
            res += tmp, f -= tmp, e[i].w -= tmp, e[i ^ 1].w += tmp;
            if (!f) break;
        }
    return res;
}

LL dinic(int s, int t) {
    LL res = 0;
    while (BFS(s, t)) {
        for (int i = 1; i <= ncnt; i++) cur[i] = head[i];
        res += DFS(s, 1e18, t);
    }
    return res;
}

int id1[N], id2[N];

void build(int rt, int l, int r) {
    id1[rt] = ++ncnt, id2[rt] = ++ncnt;
    if (l == r) {adde(id1[rt], id2[rt], INF); return;}
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
    adde(id1[rt], id1[rt << 1], INF), adde(id1[rt], id1[rt << 1 | 1], INF); 
    adde(id2[rt << 1], id2[rt], INF), adde(id2[rt << 1 | 1], id2[rt], INF);
}

int st, ed;

void link(int rt, int l, int r, int p) {
    if (st <= l && r <= ed) return adde(p, id1[rt], INF), void();
    int mid = (l + r) >> 1;
    if (st <= mid) link(rt << 1, l, mid, p);
    if (ed > mid) link(rt << 1 | 1, mid + 1, r, p);
}

void link(int rt, int l, int r, int start, int end, int p) {
    if (start > end) return;
    st = start, ed = end, link(rt, l, r, p);
}

void out(int rt, int l, int r, int p) {
    if (st <= l && r <= ed) return adde(id2[rt], p, INF), void();
    int mid = (l + r) >> 1;
    if (st <= mid) out(rt << 1, l, mid, p);
    if (ed > mid) out(rt << 1 | 1, mid + 1, r, p);
}

void out(int rt, int l, int r, int start, int end, int p) {
    if (start > end) return;
    st = start, ed = end, out(rt, l, r, p);
}

LL pre[N];

int main() {
    freopen("fish.in", "r", stdin), freopen("fish.out", "w", stdout);
    int n, q; scanf("%d%d", &n, &q);
    build(1, 1, n);
    for (int i = 1; i <= n; i++) 
        scanf("%lld", &pre[i]), pre[i] += pre[i - 1];
    LL ans = 0;
    int S = ++ncnt, T = ++ncnt; LL ans1 = 0;
    for (int i = 1; i <= q; i++) {
        int u = ++ncnt; int s, t; scanf("%d%d", &s, &t);
        LL tmp = s <= t ? pre[t] - pre[s] : pre[n] - (pre[s] - pre[t]), other = pre[n] - tmp;
        ans += tmp;
        if (s <= t) {
            link(1, 1, n, 1, s, u), link(1, 1, n, t + 1, n, u);
            out(1, 1, n, s + 1, t, u);
        } else {
            link(1, 1, n, t + 1, s, u);
            out(1, 1, n, 1, t, u), out(1, 1, n, s + 1, n, u);
        }
        if (other < tmp) adde(S, u, tmp - other), ans1 += tmp - other;
        else adde(u, T, other - tmp);
    }
    printf("%lld\n", ans - ans1 + dinic(S, T));
}