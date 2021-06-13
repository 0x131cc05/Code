#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

int fa[N], sz[N], val[N];

int get(int x) {
    return x == fa[x] ? val[x] : val[x] ^ get(fa[x]);
}

int find(int x) {
    return x == fa[x] ? x : find(fa[x]);
}

int ind[N];

int from[N], to[N], w[N], ban[N];

vector<int> G[N];

void merge(int x, int y, int t) {
    int a = find(x), b = find(y);
    if (a == b) {
        if ((get(x) ^ get(y)) != t) 
            puts("-1"), exit(0);
        return;
    }
    if (sz[a] > sz[b]) swap(a, b);
    val[a] = get(x) ^ get(y) ^ t, fa[a] = b, sz[b] += sz[a];
}

int st[N];

int main() {
    freopen("trident.in", "r", stdin), freopen("trident.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d%d", &a, &b, &w[i]), from[i] = a, to[i] = b;
        G[a].push_back(i), G[b].push_back(i);
        ind[a]++, ind[b]++;
    }
    for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
    for (int i = 1; i <= m; i++) if (ind[from[i]] <= 3 && ind[to[i]] <= 3) {
        int u = from[i], v = to[i];
        if (max(ind[u], ind[v]) <= 2) {
            if (w[i]) { puts("-1"); return 0; }
            continue;
        }
        if (ind[u] == 3 && ind[v] == 3) 
            merge(u, v, w[i]);
        else ban[ind[u] < 3 ? v : u] |= w[i] ? 2 : 1;
    }
    for (int i = 1; i <= n; i++) {
        int rev = ((ban[i] & 1) << 1) | (ban[i] >> 1);
        ban[find(i)] |= get(i) ? rev : ban[i];
    }
    for (int i = 1; i <= n; i++) if (ban[i] == 3) {
        puts("-1"); return 0;
    }
    for (int i = 1; i <= n; i++) if (find(i) == i) 
        if (ban[i] == 2) st[i] = 1;
    for (int i = 1; i <= n; i++) if (find(i) != i) 
        st[i] = st[find(i)] ^ get(i);
    vector<tuple<int, int, int>> res;
    auto push = [&](int a, int b, int c) {
        res.push_back(make_tuple(a, b, c));
    };
    for (int i = 1; i <= n; i++) if (ind[i] == 3 && st[i]) {
        push(G[i][0], G[i][1], G[i][2]);
        w[G[i][0]] ^= 1, w[G[i][1]] ^= 1, w[G[i][2]] ^= 1;
    }
    for (int i = 1; i <= n; i++) if (ind[i] >= 4) {
        vector<int> tmp;
        for (auto t : G[i]) if (w[t]) tmp.push_back(t), w[t] = 0;
        while (tmp.size() >= 3) {
            int a = tmp.back(); tmp.pop_back();
            int b = tmp.back(); tmp.pop_back();
            int c = tmp.back(); tmp.pop_back();
            push(a, b, c);
        }
        vector<int> p;
        for (auto t : G[i]) 
            if (find(tmp.begin(), tmp.end(), t) == tmp.end()) 
                p.push_back(t);
        if (tmp.size() == 1) {
            int u = tmp[0], a = p[0], b = p[1], c = p[2];
            push(u, a, b), push(u, a, c), push(u, b, c);
        } else if (tmp.size() == 2) {
            int u = tmp[0], v = tmp[1], a = p[0], b = p[1];
            push(u, a, b), push(v, a, b);
        }
    }
    printf("%d\n", res.size());
    for (auto t : res) printf("%d %d %d\n", get<0>(t), get<1>(t), get<2>(t));
}