#include <bits/stdc++.h>
using namespace std;

const int N = 2010;

class PublicTransitHard {
private:
    vector<int> G[N];
    void adde(int a, int b) {
        G[a].push_back(b), G[b].push_back(a);
    }

    int dp1[N], dp2[N], dp3[N], g1[N], g2[N], n, x;
    void dfs(int u, int f) {
        dp1[u] = dp2[u] = dp3[u] = g1[u] = g2[u] = 0;
        for (auto v : G[u]) if (v != f) {
            dfs(v, u); int len = dp1[v] + 1;
            if (len > dp1[u]) dp3[u] = dp2[u], dp2[u] = dp1[u], dp1[u] = len;
            else if (len > dp2[u]) dp3[u] = dp2[u], dp2[u] = len;
            else if (len > dp3[u]) dp3[u] = len;
            len = max(g1[v], dp1[v] + dp2[v]);
            if (len > g1[u]) g2[u] = g1[u], g1[u] = len;
            else if (len > g2[u]) g2[u] = len;
        }
    }

    int tree[N * 2]; vector<tuple<int, int, int>> buf;
    void upd(int x, int y, int t) {
        for (x += N; x; x -= x & -x) 
            buf.push_back(make_tuple(t, x, tree[x])), tree[x] = max(tree[x], y);
    }

    int que(int x) {
        int res = -1e9;
        for (x += N; x <= n + N; x += x & -x) res = max(res, tree[x]);
        return res;
    }

    void trace(int t) {
        while (buf.size() && get<0>(buf.back()) > t) {
            auto tmp = buf.back(); buf.pop_back();
            tree[get<1>(tmp)] = get<2>(tmp);
        }
    }

    int res = 0, clk = 0;
    void dfs1(int u, int f, int d, int mx) {
        int tmp = que(x + 1 - d - dp1[u]);
        if (max(dp1[u] + dp2[u], g1[u]) <= x && d + max(mx, tmp + dp1[u] - d) <= x) res++;
        for (auto v : G[u]) if (v != f) {
            int nw = clk, len1 = 0, len2 = 0, len = 0;
            if (dp1[u] == dp1[v] + 1) len1 = dp2[u] + dp3[u], len = dp2[u];
            else if (dp2[u] == dp1[v] + 1) len1 = dp1[u] + dp3[u], len = dp1[u];
            else len1 = dp1[u] + dp2[u], len = dp1[u];
            int fuck = max(g1[v], dp1[v] + dp2[v]);
            if (g1[u] == fuck) len2 = g2[u];
            else len2 = g1[u];
            if (max(len1, len2) > x) continue;
            int lst = que(x + 1 - d - len) + len - d;
            upd(len - d, len + d, ++clk);
            dfs1(v, u, d + 1, max(mx, lst));
            trace(clk = nw);
        }
    }

public: 
    PublicTransitHard() { memset(tree, -0x3f, sizeof(tree)); }
    int countValidTeleporters(int n1, vector<int> edges, int x1) {
        n = n1, x = x1;
        for (int i = 0; i < n - 1; i++) adde(i + 2, edges[i] + 1);
        for (int i = 1; i <= n; i++) {
            dfs(i, 0), dfs1(i, 0, 0, -1e9);
            if (i == 1 && res == n) return n * (n + 1) / 2;
        }
        return res / 2;
    }
};

// int main() {
//     PublicTransitHard test;
//     cout << test.countValidTeleporters(56, {0, 1, 1, 3, 1, 5, 1, 0, 8, 8, 10, 10, 12, 10, 10, 8, 16, 16, 18, 19, 19, 21, 19, 19, 24, 25, 25, 27, 18, 0, 30, 30, 30, 33, 34, 34, 34, 30, 38, 39, 39, 38, 42, 43, 0, 45, 45, 45, 48, 45, 45, 51, 45, 53, 54}, 12) << endl;
// }