#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

typedef long long LL;
typedef pair<int, int> P;

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

LL dp[N][N], val[N][N];

vector<P> tmp[N][N];

int main() {
    int n, q, t, w; scanf("%d%d%d%d", &n, &q, &t, &w);
    for (int i = 1, a, b, c; i < n; i++)
        scanf("%d%d%d", &a, &b, &c), adde(a, b, c * w);
    for (int i = 1; i <= q; i++) {
        int d, a, k, p; scanf("%d%d%d%d", &d, &a, &k, &p);
        if (k == 0) val[a][d] += p;
        else tmp[a][d].push_back(P(k, p));
    }
    for (int i = t; i >= 0; i--) {
        for (int j = 1; j <= n; j++) {
            for (auto t : tmp[i][j]) dp[i][j] = max(dp[i][j], dp[i + t.first][j] + t.second);
            if (i != t) for (int l = head[j]; l; l = e[l].next)
                dp[i][j] = max(dp[i][j], dp[i + 1][e[l].to] + e[l].w);
            dp[i][j] = max(dp[i][j], dp[i + 1][j]);
            dp[i][j] += val[i][j];
        } 
    }
    for (int i = 1; i <= n; i++) printf("%lld ", dp[0][i]);
}
