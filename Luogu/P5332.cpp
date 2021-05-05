#include <bits/stdc++.h>
using namespace std;

const int N = 400010;

typedef bitset<10010> BIT;
typedef pair<int, int> P;
typedef long long LL;

struct edge {
    int to, next;
} e[N * 4];

int head[N], ecnt, ind[N];

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt, ind[to]++;
}

BIT dp[N];

int que[N], tot, id[N]; // only death node has id

void Topsort() {
    int cur = 0; queue<int> q;
    for (int i = 1; i <= tot; i++)
        if (!ind[i]) q.push(i);
    while (!q.empty()) {
        int u; u = que[++cur] = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next)
            if (!--ind[e[i].to]) q.push(e[i].to);
    }
}

void DP(int l, int r) {
    for (int i = tot; i >= 1; i--) {
        int u = que[i]; dp[u].reset();
        if (l <= id[u] && id[u] <= r) dp[u][id[u] - l] = 1;
        for (int j = head[u]; j; j = e[j].next)
            dp[u] |= dp[e[j].to];
    }
}

int n, m, c[N], t[N], x[N], y[N], lst[N];

set<int> s[N]; map<P, int> mp;

int get(int t, int u) {
    s[u].insert(t), lst[u] = max(lst[u], t); P nw(u, t);
    if (mp.count(nw)) return mp[nw];
    mp[nw] = tot + 1, id[tot + 2] = u, tot += 2;
    return tot - 1;
}

void build() {
    for (int i = 1; i <= m; i++) {
        if (c[i] == 0) {
            adde(get(t[i], x[i]) + 1, get(t[i] + 1, y[i]) + 1);
            adde(get(t[i] + 1, y[i]), get(t[i], x[i]));
        } else {
            adde(get(t[i], x[i]), get(t[i], y[i]) + 1);
            adde(get(t[i], y[i]), get(t[i], x[i]) + 1);
        }
    }
    for (int i = 1; i <= n; i++) {
        int lst = 0;
        for (auto t : s[i]) {
            if (lst) adde(lst + 1, get(t, i) + 1), adde(get(t, i), lst);
            lst = get(t, i);
        }
    }
    Topsort();
}

int ans[N], flg[N];

int main() {
    int T; scanf("%d%d%d", &T, &n, &m);
    for (int i = 1; i <= m; i++) 
        scanf("%d%d%d%d", &c[i], &t[i], &x[i], &y[i]);
    build();
    for (int l = 1, r; l <= n; l = r + 1) {
        r = min(n, l + 10000), DP(l, r); BIT biss;
        for (int i = l; i <= r; i++) if (lst[i]) {
            int t = get(lst[i], i);
            if (dp[t][i - l]) biss[i - l] = 1, flg[i] = 1;
        }
        for (int i = 1; i <= n; i++) {
            if (!lst[i]) { ans[i] += r - l + 1 - biss.count(); continue; }
            ans[i] += r - l + 1 - (biss | dp[get(lst[i], i)]).count();
        }
    }
    for (int i = 1; i <= n; i++) printf("%d ", flg[i] ? 0 : ans[i] - 1);
}