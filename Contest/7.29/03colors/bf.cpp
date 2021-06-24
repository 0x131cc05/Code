#include <bits/stdc++.h>
using namespace std;

const int N = 510;

int col[N], n; bitset<N> G[N], S[3]; int ls = 0;

void dfs(int cur) {
    ls = max(ls, cur);
    cerr << ls << endl;
    if (cur == n + 1) {
        for (int i = 1; i <= n; i++) printf("%d ", col[i]);
        exit(0);
    }
    int nxt = G[cur].count();
    if (!nxt) {
        col[cur] = 1, dfs(cur + 1);
        return;
    }
//    int r[4] = { 0 }, id[4] = { 0, 1, 2, 3 };
    for (int i = 1; i <= 3; i++) if (!((G[cur] & S[i - 1]).count())) {
//        int remain = (G[cur] ^ (G[cur] & S[i - 1])).count();
//        if (remain) continue;
//        if (remain == nxt) {
            col[cur] = i, S[i - 1][cur] = 1;
            dfs(cur + 1), S[i - 1][cur] = 0;
//            if (rand() & 1) return;
//        }
//        r[i] = remain;
    }
//    sort(id + 1, id + 4, [&](int a, int b) { return r[a] > r[b]; });
//    for (int i = 1; i <= 3; i++) {
//        int t = id[i];
//        if (r[t]) {
//            col[cur] = id[i], S[id[i] - 1][cur] = 1;
//            dfs(cur + 1), S[id[i] - 1][cur] = 0;
//        }
//    }
}

int main() {
    freopen("03colors5.in", "r", stdin), freopen("03colors5.out", "w", stdout);
    int m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G[u][v] = G[v][u] = 1;
    }
    dfs(1);
}

