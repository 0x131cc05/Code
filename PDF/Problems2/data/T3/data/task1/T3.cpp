#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 10;
const int M = 4000;

inline double Pow(double x, LL y) {
    double res = 1;
    for (; y; y >>= 1, x = x * x) if (y & 1) res = res * x;
    return res;
}

map<vector<int>, int> ID; vector<int> present[M];

int tot, r;

int ok[N][M]; // 每种状态的最后一列是否与 (1, 1) 连通

// 新增第 0 行，与第一行连边被保留的概率为 0
// A 中两个位置的数相同表示这两个位置处于同一个连通块 
inline int process(vector<int> &A) { // 重标号
    static int buk[N]; int tmp = 0, flag = 0;
    memset(buk, 0, sizeof(buk));
    for (int i = 0; i <= r; i++) {
        if (!buk[A[i]]) buk[A[i]] = ++tmp;
        A[i] = buk[A[i]];
        if (i && A[i] == A[0]) flag = 1;
    }
    if (!flag) return -1; // 没有格子与 (1, 1) 连通
    if (ID.count(A)) return ID[A];
    ID[A] = tot + 1, ok[r][tot + 1] = A[r] == A[0], present[tot + 1] = A; // 新增一种状态
    return tot + 1;
}

int trans[N][M][N][4], all[N];

void dfs(int status) { // 爆搜所有状态
    for (int i = 1; i <= r; i++) {
        auto A = present[status];
        auto run = [&](const int &x) -> void {
            if (x == tot + 1) 
                tot++, dfs(tot);
        };
        // 与左边和上面的格子均没有连边
        A[i] = r + 1, run(trans[r][status][i][0] = process(A));
        // 与上面的格子有连边
        if (i > 1) {
            A = present[status], A[i] = A[i - 1];
            run(trans[r][status][i][1] = process(A));
        }
        // 与左边的格子有连边
        trans[r][status][i][2] = status;
        // 与左边和上面的格子都有连边
        if (i > 1) {
            A = present[status]; int tmp = A[i - 1];
            for (int j = 0; j <= r; j++) if (A[j] == tmp) A[j] = A[i];
            run(trans[r][status][i][3] = process(A));
        }
    }
}

double dp[51][N][M];

inline double Just_DOIT() {
    int n; LL m; double p; scanf("%d%lld%lf", &n, &m, &p);
    if (m > 1e9) return 0;
    int full = all[n], t = min(50ll, m);
    for (int i = 1; i <= t; i++)
        for (int j = 1; j <= n; j++)
            for (int t = 1; t <= full; t++)
                dp[i][j][t] = 0;
    dp[1][1][1] = 1;
    double P[4] = { p * p, (1 - p) * p, p * (1 - p), (1 - p) * (1 - p) };
    for (int i = 1; i <= t; i++) 
        for (int j = 1; j <= n; j++) if (!(i == 1 && j == 1)) {
            double *f = j == 1 ? dp[i - 1][n] : dp[i][j - 1], *g = dp[i][j], zjk[4];
            if (i == 1) zjk[0] = p, zjk[1] = 1 - p, zjk[2] = zjk[3] = 0;
            else if (j == 1) zjk[0] = p, zjk[2] = 1 - p, zjk[1] = zjk[3] = 0;
            else memcpy(zjk, P, sizeof(P));
            for (int k = 1; k <= full; k++)
                for (int l = 0; l < 4; l++) {
                    int to = trans[n][k][j][l];
                    if (to != -1) g[to] += f[k] * zjk[l];
                }
        }
    double ans = 0, ls = 0;
    for (int i = 1; i <= full; i++) if (ok[n][i]) ans += dp[t][n][i];
    if (t == m) return ans;
    for (int i = 1; i <= full; i++) if (ok[n][i]) ls += dp[t - 1][n][i];
    if (ls < 1e-8) return 0;
    return ls * Pow(ans / ls, m - t + 1);
}

inline void pre(int nw) {
    vector<int> base;
    r = nw, tot = 1, ID.clear(), ok[nw][1] = nw == 1; 
    for (int i = 0; i <= r; i++) base.push_back(max(i, 1));
    ID[base] = 1, present[1] = base, dfs(1), all[r] = tot;
}

#define open(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)

int main() {
    open("task5");
    memset(trans, -1, sizeof(trans));
    for (int i = 1; i <= 8; i++) pre(i);
    int T; scanf("%d", &T);
    while (T--) printf("%.13lf\n", Just_DOIT());
    return 0;
}
