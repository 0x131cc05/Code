#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

typedef pair<int, int> P;

vector<int> G[N];
void adde(int u, int v) { G[u].push_back(v), G[v].push_back(u); }

int col[N], ct;
vector<int> p[N][2];
bool dfs(int u, int c, int tp = 1) {
    col[u] = c; if (tp) p[ct][c - 1].push_back(u);
    for (auto v : G[u]) 
        if (!col[v]) { if (!dfs(v, 3 - c, tp)) return false; } 
        else if (col[v] != 3 - c) return false;
    return true;
}

P seg[N]; int pre[N];

struct DisjointSemicircles {
    string getPossibility(vector<int> num) {
        for (auto &t : num) if (t >= 0) t++;
        int n = num.size(), m = n / 2;
        for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + (num[i - 1] == -1);
        for (int i = 0; i < n; i++) if (num[i] != -1)
            for (int j = i + 1; j < n; j++) if (num[i] == num[j])
                seg[num[i]] = P(i + 1, j + 1);
        for (int i = 1; i <= m; i++) if (seg[i].first)
            for (int j = i + 1; j <= m; j++) if (seg[j].first)
                if (max(seg[i].first, seg[j].first) <= min(seg[i].second, seg[j].second)
                    && (seg[i].first < seg[j].first) == (seg[i].second < seg[j].second))
                    adde(i, j);
        vector<P> lim;
        for (int i = 1; i <= m; i++) if (seg[i].first && !col[i]) {
            if (G[i].size()) {
                ct++;
                if (!dfs(i, 1)) return "IMPOSSIBLE";
            } else if ((seg[i].second - seg[i].first) & 1)
                lim.push_back(P(seg[i].first, seg[i].second));
        }
        // cout << ct << ' ' << lim.size() << endl;
        for (int s = 0; s < 1 << ct; s += 2) {
            for (int i = 0; i <= 2 * n + 1; i++) G[i].clear(), col[i] = 0;
            auto link = [&](int l, int r, int tp) { 
                if (tp == 0) adde(l - 1, r + n + 1), adde(l - 1 + n + 1, r);
                else adde(l - 1, r), adde(l - 1 + n + 1, r + n + 1);
            };
            for (auto t : lim) link(t.first, t.second, 0);
            for (int i = 1; i <= ct; i++) {
                int st = (s >> (i - 1)) & 1;
                for (auto t : p[i][st ^ 1]) link(seg[t].first, seg[t].second, 0);
                for (auto t : p[i][st]) {
                    int l = seg[t].first, r = seg[t].second;
                    link(l, r, (pre[r] - pre[l]) & 1);
                }
            }
            for (int i = 1; i <= n; i++) if (num[i - 1] != -1)
                adde(i - 1, i + n + 1), adde(i - 1 + n + 1, i);
            for (int i = 0; i <= n; i++) adde(i, i + n + 1);
            link(1, n, 0);
            bool flag = true;
            for (int i = 0; i <= n * 2 + 1 && flag; i++) if (!col[i])
                if (!dfs(i, 1, 0)) { flag = false; break; }
            if (flag) return "POSSIBLE";
        }
        return "IMPOSSIBLE";
    }
};

// int main() {
//     DisjointSemicircles solver;
//     cout << solver.getPossibility(	
// { -1, 5, -1, -1, 3, 6, 8, -1, 10, 7, -1, 7, 8, 0, 11, -1, -1, 11, 0, 10, 4, -1, 6, 5, -1, -1, 9, 9, 4, 3 }
// ) << endl;
// }