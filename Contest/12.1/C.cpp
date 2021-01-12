#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;

typedef long long LL;
typedef pair<int, int> P;

const int N = 410;
const LL INF = 1e18;

struct node {
    LL dis; int u, v, type;
    bool operator > (const node &b) const {
        return dis > b.dis;
    }
};

typedef __gnu_pbds::priority_queue<node, greater<node>> PQ;

PQ q;
vector<P> e1[N], e2[N];
LL F[N][N], G[N][N]; int vis[N][N];
PQ::point_iterator f[N][N], g[N][N];

int main() {
    int n, m, T; scanf("%d%d%d", &n, &m, &T);
    for (int i = 1; i <= m; i++) {
        int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
        if (d == 1) e1[b].push_back(P(a, c));
        else e2[a].push_back(P(b, c));
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            F[i][j] = i == j ? 0 : INF, G[i][j] = INF;
            f[i][j] = q.push((node){ F[i][j], i, j, 0 });
            g[i][j] = q.push((node){ G[i][j], i, j, 1 });
        }   
    while (!q.empty()) {
        auto nw = q.top(); q.pop();
        int u = nw.u, v = nw.v;
        if (nw.type == 1) {
            for (auto [t, c] : e2[v]) 
                if (G[u][v] + c < F[u][t]) {
                    F[u][t] = G[u][v] + c;
                    q.modify(f[u][t], (node){ F[u][t], u, t, 0 });
                }
        } else {
            for (int i = 1; i <= n; i++) {
                if (F[u][v] + F[v][i] < F[u][i]) {
                    F[u][i] = F[u][v] + F[v][i];
                    q.modify(f[u][i], (node){ F[u][i], u, i, 0 });
                }
                if (F[i][u] + F[u][v] < F[i][v]) {
                    F[i][v] = F[i][u] + F[u][v];
                    q.modify(f[i][v], (node){ F[i][v], i, v, 0 });
                }
            }
            for (auto [t, c] : e1[u]) 
                if (c + F[u][v] < G[t][v]) {
                    G[t][v] = c + F[u][v];
                    q.modify(g[t][v], (node){ G[t][v], t, v, 1 });
                }
        }
    }
    while (T--) {
        int a, b; scanf("%d%d", &a, &b);
        if (F[a][b] > 1e16) puts("-1");
        else printf("%d\n", F[a][b] % 998244353);
    }
}