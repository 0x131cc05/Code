#include <bits/stdc++.h>
using namespace std;

int rnd() {
    return rand() | (rand() << 16);
}

int dep[110], fa[110], G[110][110];

int lca(int u, int v) {
    while (u != v) {
        if (dep[u] < dep[v]) swap(u, v);
        u = fa[u];
    }
    return u;
}

int main() {
//    freopen("B.in", "w", stdout);
    srand((long long)new char + time(0));
    int n = 10, m = 5; printf("%d %d\n", n, n + m - 1);
    for (int i = 2; i <= n; i++) {
        int f = rand() % (i - 1) + 1; fa[i] = f, G[f][i] = G[i][f] = 1;
        printf("%d %d\n", f, i), dep[i] = dep[f] + 1;
    }
    for (int i = 1; i <= m; i++) {
        int a = rand() % n + 1, b = rand() % n + 1;
        while (b == a || lca(a, b) != 1 || G[a][b] || G[b][a]) a = rand() % n + 1, b = rand() % n + 1;
        G[a][b] = G[b][a] = 1;
        printf("%d %d\n", a, b);
    }
} 
