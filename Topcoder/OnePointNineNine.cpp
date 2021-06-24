#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int mod = 1e9 + 7;

typedef long long LL;

bitset<N> p[N], c[N];

bool isRT[N], vis[N];

int dp[2][2][N];

int solve(vector<int> v, int type) {
//    cout << "solve: ";
//    for (auto t : v) cout << t << ' ';
//    cout << endl;
//    cout << type << endl;
    int n = v.size();
    for (int t = 0; t < 4; t++)
        for (int i = 1; i <= n; i++) dp[t & 1][t >> 1][i] = 0;
    dp[1][1][1] = v[0], dp[0][0][1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int a = 0; a <= 1; a++)
            for (int b = 0; b <= 1; b++) if (dp[a][b][i - 1]) {
                if (!b) dp[a][1][i] = (dp[a][1][i] + (LL)dp[a][b][i - 1] * v[i - 1]) % mod;
                dp[a][0][i] = (dp[a][0][i] + dp[a][b][i - 1]) % mod;
            }
    }
    // cout << type << endl;
    if (!type) return ((LL)dp[0][1][n] + dp[1][0][n] + dp[1][1][n] + dp[0][0][n]) % mod;
    return ((LL)dp[0][1][n] + dp[1][0][n] + dp[0][0][n]) % mod;
}

vector<int> G[N]; int ind[N];

struct OnePointNineNine {
    int countSubsets(vector<int> x, vector<int> y, int D) {
        int n = x.size();
        auto check = [&](int a, int b) { // 1-base
            a--, b--;
            return (LL)(x[a] - x[b]) * (x[a] - x[b]) + 
                (LL)(y[a] - y[b]) * (y[a] - y[b]) <= (LL)D * D;
        };
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) if (check(i, j)) p[i][j] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++) if (!check(i, j)) {
                // cout << "fuck: " << i << ' ' << j << endl;
                bitset<N> res = p[i] & p[j]; 
                if (!res.any()) continue;
                p[i] ^= res, p[j] ^= res;
                int u = res._Find_first();
                // cout << u << endl;
                if (!c[u].any()) c[u] = res;
            } 
//        for (int i = 1; i <= n; i++)
//            for (int j = 1; j <= n; j++) if (i != j && c[j].any()) {
//                bitset<N> tp = p[i] & c[j];
//                if (tp.any()) p[i] ^= tp;
//            }
        for (int i = 1; i <= n; i++) if (!vis[i]) {
            isRT[i] = 1; 
            // cout << "isrt: " << i << endl;
            if (!c[i].any()) c[i] = p[i];
            for (int j = 1; j <= n; j++) if (c[i][j]) vis[j] = 1;
        } 
        memset(vis, 0, sizeof(vis));
        int res = 1;
        for (int i = 1; i <= n; i++) if (isRT[i]) {
            for (int j = 1; j <= n; j++) if (j != i && isRT[j] && check(i, j)) {
                G[i].push_back(j), ind[i]++;
            }
        }
        auto push = [&](int i) {
            int nw = i, ls = 0, flag = 0; 
            vector<int> tmp = { (int)c[i].count() };
            while (233) {
                vis[nw] = 1; int nxt = 0;
                for (auto v : G[nw]) if (v != ls) {
                    if (vis[v]) { flag = 1; break; }
                    tmp.push_back(c[v].count()), nxt = v; break;
                }
                if (nxt) ls = nw, nw = nxt;
                else break;
            }
            res = (LL)res * solve(tmp, flag) % mod;
        };
        for (int i = 1; i <= n; i++) 
            if (isRT[i] && ind[i] <= 1 && !vis[i]) push(i);
        for (int i = 1; i <= n; i++) 
            if (isRT[i] && !vis[i]) push(i);
        return res;
    }
};

