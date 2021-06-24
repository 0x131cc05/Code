#include <bits/stdc++.h>
using namespace std;

const int N = 110;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt, ind[N];

void adde(int from, int to) {
    // cout << "adde: " << from << ' ' << to << endl;
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
    ind[from]++, ind[to]++;
}

double dp[N][N][N], C[N][N];

int sz[N], n, lim;

void dfs(int u, int f) {
    sz[u] = 1, dp[u][0][0] = 1;
    vector<double> coef; coef.push_back(1);
    double p = 1;
    if (ind[u]) for (int i = 1; i <= lim; i++) 
        p /= ind[u], coef.push_back(p);
    // if (u == 1) cout << "fuck: " << ind[1] << ' ' << coef[1] << endl;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            int v = e[i].to; dfs(v, u);
            static double g[N][N]; memset(g, 0, sizeof(g));
            for (int j = 0; j <= sz[v]; j++) 
                for (int k = j; k <= lim; k++) 
                    for (int l = 0; l <= sz[u]; l++)
                        for (int t = l; t + k <= lim; t++) 
                            g[j + l][k + t] += dp[v][j][k] * dp[u][l][t] * C[k + t][k] * coef[k];
            sz[u] += sz[v];
            for (int j = 0; j <= sz[u]; j++)
                for (int k = j; k <= lim; k++)
                    dp[u][j][k] = g[j][k];
        }
    static double g[N][N]; memset(g, 0, sizeof(g)), g[0][0] = 1;
    for (int i = 0; i < sz[u]; i++)
        for (int j = i; j < lim; j++) 
            g[i + 1][j + 1] += dp[u][i][j];
    memcpy(dp[u], g, sizeof(g));
    if (!ind[u]) {
        for (int i = 2; i <= lim; i++)
            dp[u][1][i] = dp[u][1][1];
    }
}

class EagleInZoo {
public:
    double calc(vector<int> p, int k) {
        lim = k, n = p.size() + 1;
        for (int i = 0; i < p.size(); i++) adde(p[i] + 1, i + 2);
        for (int i = 0; i <= lim; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++)
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
        for (int i = 2; i <= n; i++) ind[i]--;
        dfs(1, 0);
        // cout << dp[1][2][3] << endl;
        double res = 0;
        for (int i = 1; i <= n; i++)
            res += (dp[1][i][lim] - dp[1][i][lim - 1]) * i;
        return res;
    }
};

int main() {
    EagleInZoo solver;
    cout << solver.calc(
{0,0,0},
5) << endl;
}