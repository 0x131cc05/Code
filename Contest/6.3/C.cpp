#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 200010;

int n; LL tot;

int fa[N], leaf[N], ind[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

struct edge {

int from, to, w;

bool operator < (const edge &b) {
    return w > b.w;
}

};

vector<edge> wkr;

inline void adde(int from, int to, int w) {
    ind[from]++, ind[to]++, tot += w, wkr.push_back((edge){ from, to, w });
}

inline void solve() {
    int hh = 0;
    for (int i = 1; i <= n; i++) if (ind[i] == 1 && i != 1 && i != n + 1) 
        leaf[i] = 1, hh++;
    for (int i = 1; i <= n; i++) fa[i] = i;
    int tmp = hh; hh = hh / 2 + 1, sort(wkr.begin(), wkr.end());
    fa[1] = n / 2 + 1;
    for (auto e : wkr) {
        int u = e.from, v = e.to, w = e.w;
        if (find(u) == find(v)) continue;
        u = find(u), v = find(v);
        assert(u), assert(v);
        if (leaf[u] == 0 || leaf[v] == 0 || tmp > hh) 
            tmp -= leaf[v] & leaf[u], leaf[v] |= leaf[u], fa[u] = v, tot -= w;
    }
}

int main() {
    int n; scanf("%d", &n); ::n = n * 2;
    for (int i = 1, a, b, c; i < n; i++) 
        scanf("%d%d%d", &a, &b, &c), adde(a, b, c);
    for (int i = 1, a, b, c; i < n; i++)
        scanf("%d%d%d", &a, &b, &c), adde(a + n, b + n, c);
    solve(), printf("%lld\n", tot);
}
