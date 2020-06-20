#include <bits/stdc++.h>
using namespace std;

const int N = 60;

int ct, w, n, m, fa[N], sz[N];

int find(int x) {
    return x == fa[x] ? x : find(fa[x]);
}

struct WEN {

int from, to, w;

bool operator < (const WEN &b) {
    return w < b.w;
}

} e[2010];

int mid, k, res;

bool dfs(int cur, int ct, int w) {
    if (w > mid) return false;
    if (m - cur + 1 + ct < n - 1) return false;
    if (ct == n - 1) return res++, true;
    if ((n - 1 - ct) * e[cur].w + w > mid) return false;
    bool hh = false;
    for (int i = cur; i <= m; i++) {
        int u = e[i].from, v = e[i].to; 
        if (find(u) == find(v)) continue;
        u = find(u), v = find(v);
        if (sz[u] > sz[v]) swap(u, v);
        sz[v] += sz[u], fa[u] = v;
        bool t = dfs(i + 1, ct + 1, w + e[i].w); hh |= t;
        sz[v] -= sz[u], fa[u] = u;
        if (res >= k) return true;
        if (!t) break;
    }
    return hh;
}

inline bool check(int mid) {
    ::mid = mid, res = 0;
    for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
    dfs(1, 0, 0);
    return res >= k;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &e[i].from, &e[i].to, &e[i].w);
    sort(e + 1, e + m + 1);
    int l = n - 1, r = 5e7, mid, res = -1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (check(mid)) res = mid, r = mid - 1;
        else l = mid + 1;
    } 
    printf("%d\n", res);
}
