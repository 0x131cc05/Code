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

    int tree[N]; vector<tuple<int, int, int>> buf;
    void upd(int x, int y, int t) {
        for (x += N; x; x -= x & -x) 
            buf.push_back({t, x, tree[x]}), tree[x] = max(tree[x], y);
    }

    int que(int x) {
        int res = 0;
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
        int wkr = max(dp1[u] + dp2[u], g1[u]);
        int tmp = que(x + 1 - d - wkr);
        if (wkr <= x && d + max(mx, tmp + wkr - d) <= x) res++;
        for (auto v : G[u]) if (v != f) {
            int nw = clk, len1 = 0, len2 = 0;
            if (dp1[u] == dp1[v] + 1) len1 = dp2[u] + dp3[u];
            else if (dp2[u] == dp1[v] + 1) len1 = dp1[u] + dp3[u];
            else len1 = dp1[u] + dp2[u];
            int fuck = max(g1[v], dp1[v] + dp2[v]);
            if (g1[u] == fuck) len2 = g2[u];
            else len2 = g1[u];
            int len = max(len1, len2), lst = que(x + 1 - d - len) + len - d;
            upd(len - d, len + d, ++clk);
            dfs1(v, u, d + 1, max(mx, lst));
            trace(clk = nw);
        }
    }

public: 
    PublicTransitHard() {}
    int countValidTeleporters(int n1, vector<int> edges, int x1) {
        n = n1, x = x1;
        for (int i = 0; i < n - 1; i++) adde(i + 2, edges[i] + 1);
        for (int i = 1; i <= n; i++) {
            dfs(i, 0);
            for (int j = 1; j <= n; j++) cout << g1[j] << ' ';
            cout << endl;
            dfs1(i, 0, 1, 0);
        }
        return res / 2;
    }
};

int main() {
    PublicTransitHard test;
    cout << test.countValidTeleporters(4, {0, 1, 2}, 1) << endl;
}