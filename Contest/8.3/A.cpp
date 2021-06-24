#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int M = 6000010;

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

int tree[M], k;

void upd(int x, int y) {
    for (x += M / 2; x <= M - 10; x += x & -x) tree[x] += y;
}

int qry(int x) {
    int res = 0;
    for (x += M / 2; x; x -= x & -x) res += tree[x];
    return res;
}

int res, mid, dep[N], ans[N];

void count(int u, int f, int len) {
    if (len <= mid) res++;
    if (len > mid || res > k) return;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) count(e[i].to, u, len + e[i].w);
}

void add(int u, int f, int len, int y) {
    upd(len, y);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) add(e[i].to, u, len + e[i].w, y);
}

void dfs(int u, int f) {
    int l = 0, r = 3e6;
    while (l <= r) {
        mid = (l + r) >> 1, res = qry(mid - dep[u]), count(u, f, 0);
        if (res >= k) ans[u] = mid, r = mid - 1;
        else l = mid + 1;
    }
    add(u, f, -dep[u], 1);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) 
            add(e[i].to, u, -dep[u] + e[i].w, -1), dep[e[i].to] = dep[u] + e[i].w, dfs(e[i].to, u), add(e[i].to, u, -dep[u] + e[i].w, 1);
    add(u, f, -dep[u], -1);
}

int main() {
//    freopen("test1.in", "r", stdin), freopen("out.out", "w", stdout);
    int n; scanf("%d%d", &n, &k);
    for (int i = 1, a, b, c; i < n; i++) scanf("%d%d%d", &a, &b, &c), adde(a, b, c);
    dfs(1, 0);
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
}
