#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int G[N][N], fa[N], val[N], sz[N];

int get(int x) {
    return x == fa[x] ? val[x] : val[x] ^ get(fa[x]);
}

int find(int x) {
    return x == fa[x] ? x : find(fa[x]);
}

void merge(int x, int y) {
    if (find(x) == find(y)) {
        if (get(x) == get(y)) puts("NO"), exit(0); 
    }
    int v = 1 ^ get(x) ^ get(y);
    x = find(x), y = find(y);
    if (sz[x] > sz[y]) swap(x, y);
    fa[x] = y, val[x] = v, sz[y] += sz[x];
}

int col[N], ct = 0;

int main() {
    int n, m; scanf("%d%d", &n, &m);
    if (n % 3) return puts("NO"), 0;
    for (int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b), G[a][b] = G[b][a] = 1;
    }
    vector<tuple<int, int, int>> vec;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) if (!G[i][j])
            for (int k = j + 1; k <= n; k++) {
                if (!G[i][k] && !G[j][k]) {
                    if (col[i] || col[j] || col[k]) 
                        return puts("NO"), 0;
                    col[i] = col[j] = col[k] = ++ct;
                    vec.push_back(make_tuple(i, j, k));
                }
            }
    if (ct * 3 != n) return puts("NO"), 0;
    for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) if (col[i] != col[j] && !G[i][j])
            merge(i, j);
    for (auto t : vec) {
        int a = get<0>(t), b = get<1>(t), c = get<2>(t);
        if (find(a) == find(b) || find(a) == find(c) || find(b) == find(c)) {
            return puts("NO"), 0;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) if (find(i) == find(j)) {
            if (G[i][j] == (get(i) ^ get(j))) return puts("NO"), 0;
        }
    puts("YES");
}
