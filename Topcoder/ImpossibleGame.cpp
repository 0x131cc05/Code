#include <bits/stdc++.h>
using namespace std;

const int N = 20010;

typedef long long LL;

struct edge {
    int to, next;
} e[N * 50];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
}

int dfn[N], low[N], vis[N], dfsn, scc[N], tot; LL sz[N], val[N];
vector<int> stk;

void tarjan(int u) {
    dfn[u] = low[u] = ++dfsn, vis[u] = 1, stk.push_back(u);
    for (int i = head[u]; i; i = e[i].next)
        if (!dfn[e[i].to]) tarjan(e[i].to), low[u] = min(low[u], low[e[i].to]);
        else if (vis[e[i].to]) low[u] = min(low[u], dfn[e[i].to]);
    if (low[u] >= dfn[u]) {
        tot++, sz[tot] = 0;
        while (stk.size()) {
            int v = stk.back(); stk.pop_back();
            vis[v] = 0, scc[v] = tot, sz[tot] += val[v];
            if (u == v) break;
        }
    }
}

LL dp[N]; int ncnt; vector<int> G[N];
LL solve() {
    for (int i = 1; i <= ncnt; i++) 
        for (int j = head[i]; j; j = e[j].next)
            if (scc[i] != scc[e[j].to]) G[scc[i]].push_back(scc[e[j].to]);
    LL ans = 0;
    for (int i = 1; i <= tot; i++) {
        for (auto v : G[i]) dp[i] = max(dp[i], dp[v]);
        dp[i] += sz[i], ans = max(ans, dp[i]);
    }
    return ans;
}

int ct[60][4], ct1[60][4], id[31][31][31];
struct ImpossibleGame {
    LL getMinimum(int k, vector<string> lst, vector<string> nxt) {
        int m = lst.size();
        for (int i = 1; i <= m; i++) 
            for (int j = 0; j < lst[i - 1].size(); j++) 
                ct[i][lst[i - 1][j] - 'A']++, ct1[i][nxt[i - 1][j] - 'A']++;
        vector<int> FUCK = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
        for (int A = 0; A <= k; A++)
            for (int B = 0; A + B <= k; B++)
                for (int C = 0; A + B + C <= k; C++) {
                    int D = k - A - B - C;
                    static int ct[12];
                    auto push = [&](int x, int w) {
                        for (int i = 0; i < FUCK.size(); i++) {
                            int tmp = x;
                            while (tmp) ct[i] += w * (tmp /= FUCK[i]);
                        }
                    };
                    push(A, -1), push(B, -1), push(C, -1), push(D, -1), push(k, 1);
                    int id = ++ncnt; val[id] = 1, ::id[A][B][C] = ncnt;
                    for (int i = 0; i < FUCK.size(); i++) 
                        while (ct[i]) val[id] *= FUCK[i], ct[i]--;
                }
        for (int A = 0; A <= k; A++)
            for (int B = 0; A + B <= k; B++)
                for (int C = 0; A + B + C <= k; C++) {
                    int D = k - A - B - C;
                    for (int i = 1; i <= m; i++) {
                        if (A >= ct[i][0] && B >= ct[i][1] && C >= ct[i][2] && D >= ct[i][3]) {
                            adde(id[A][B][C], id[A - ct[i][0] + ct1[i][0]][B - ct[i][1] + ct1[i][1]][C - ct[i][2] + ct1[i][2]]);
                        }
                    }
                }
        for (int i = 1; i <= ncnt; i++) if (!dfn[i]) tarjan(i);
        return solve();
    }
};

// int main() {
//     ImpossibleGame solver;
//     cout << solver.getMinimum(5, {"AAC", "DAAA", "CD", "BA"}, {"ABC", "AAAA", "AB", "DA"}) << endl;
// }
