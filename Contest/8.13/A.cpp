#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef unsigned long long uLL;

vector<int> G[N];

int ind[N];

void adde(int from, int to) {
    G[from].push_back(to);
    ind[to]++;
}

int p[N], n;

void topSort() {
    queue<int> q; int tot = 0;
    for (int i = 1; i <= n; i++) 
        if (!ind[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); p[++tot] = u, q.pop();
        for (auto v : G[u])
            if (!--ind[v]) q.push(v);
    }
}

struct wen {
    int op, a, b;
} q[N];

int val[N], tim[N]; 
uLL upper[N], lastCover[N], mask[N], mask1[N];

int fuck[N];

int main() {
    int m, t; scanf("%d%d%d", &n, &m, &t);
    for (int i = 1, a, b; i <= m; i++) scanf("%d%d", &a, &b), adde(a, b);
    topSort();
    for (int i = 1; i <= t; i++) {
        scanf("%d%d", &q[i].op, &q[i].a);
        if (q[i].op != 3) scanf("%d", &q[i].b);
    }
    for (int l = 1, r; l <= t; l = r + 1) {
        while (l <= t && q[l].op == 3) {
            q[l].b = val[q[l].a];
            l++;
        }
        if (l > t) break;
        int nw = 1; r = l, fuck[l] = 1; static int at[65]; at[1] = l;
        while (r + 1 <= t && nw <= 64) {
            if (q[r + 1].op != 3) {
                if (nw == 64) break;
                fuck[r + 1] = ++nw, at[nw] = r + 1;
            }
            r++;
        }
        for (int i = 1; i <= n; i++) mask1[i] = 0;
        for (int i = l; i <= r; i++) if (q[i].op != 3) mask1[q[i].a] |= 1ull << (fuck[i] - 1);
        for (int i = 1; i <= n; i++) lastCover[i] = mask[i] = tim[i] = 0;
        upper[0] = (uLL)-1;
        for (int i = l; i <= r; i++) if (q[i].op == 1) 
            lastCover[q[i].a] = i, tim[q[i].a] = i;
        for (int i = 1; i <= n; i++) {
            int u = p[i];
            if (lastCover[u]) for (auto v : G[u])
                if (tim[v] < tim[u]) tim[v] = tim[u], lastCover[v] = lastCover[u];
        }
        static int id[65], rk[65]; int tot = 0;
        for (int i = l; i <= r; i++) if (q[i].op != 3) tot++, id[tot] = tot;
        sort(id + 1, id + tot + 1, [&](int a, int b) { return q[at[a]].b < q[at[b]].b; });
        for (int i = 1; i <= tot; i++) rk[id[i]] = i;
        for (int i = l; i <= r; i++) if (q[i].op == 1) {
            for (int j = i + 1; j <= r; j++) if (q[j].op != 3)
                upper[i] |= 1ull << (rk[fuck[j]] - 1);
        } else if (q[i].op == 2) mask[q[i].a] |= 1ull << (rk[fuck[i]] - 1);
        for (int i = 1; i <= n; i++) {
            int u = p[i];
            for (auto v : G[u])
                mask1[v] |= mask1[u], mask[v] |= mask[u];
        }
        for (int i = l; i <= r; i++) if (q[i].op == 3) {
            int u = q[i].a, v = val[u];
            for (int j = l; j < i; j++) if (q[j].op != 3 && ((mask1[u] >> (fuck[j] - 1)) & 1)) {
                if (q[j].op == 1) v = q[j].b;
                else v = min(v, q[j].b);
            }
            q[i].b = v;
        }
        for (int i = 1; i <= n; i++) {
            uLL hh = mask[i] & upper[lastCover[i]];
            if (lastCover[i]) val[i] = q[lastCover[i]].b;
            if (!hh) continue;
            int pos = __builtin_ctzll(hh) + 1, v = q[at[id[pos]]].b;
            val[i] = min(val[i], v);
        }
    }
    for (int i = 1; i <= t; i++) 
        if (q[i].op == 3) printf("%d\n", q[i].b);
}
