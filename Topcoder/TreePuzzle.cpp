#include <bits/stdc++.h>
using namespace std;

const int N = 310;

typedef tuple<int, int, int> T;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int ct[N][N], sz[N][N], blk[N];

void dfs(int rt, int u, int f) {
    ct[rt][u] = blk[u], sz[rt][u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(rt, e[i].to, u), ct[rt][u] += ct[rt][e[i].to], sz[rt][u] += sz[rt][e[i].to];
}

set<T> s;

class TreePuzzle {
public:
    vector<int> reachable(vector<int> parent, vector<int> v) {
        int n = parent.size();
        for (int i = 1; i < n; i++) adde(parent[i] + 1, i + 1);
        for (int i = 1; i < n; i++) blk[i + 1] = v[i];
        for (int i = 1; i <= n; i++) dfs(i, i, 0);
        queue<T> q; 
        for (int i = head[1]; i; i = e[i].next) 
            if (ct[1][e[i].to] < sz[1][e[i].to]) {
                auto tmp = T(e[i].to, 1, ct[1][e[i].to]);
                q.push(tmp), s.insert(tmp);
            }
        vector<int> res(n); res[0] = 1; 
        int all = ct[1][1];
        while (!q.empty()) {
            T tmp = q.front(); q.pop();
            int u = get<0>(tmp), v = get<1>(tmp), c = get<2>(tmp);
            res[u - 1] = 1;
            if (all - c < sz[u][v]) {
                auto tmp = T(v, u, all - c);
                if (!s.count(tmp)) s.insert(tmp), q.push(tmp);
            }
            for (int i = head[u]; i; i = e[i].next)
                if (e[i].to != v) {
                    int t = e[i].to, fuck = sz[v][u] - 1 - sz[u][t];
                    for (int j = 0; j <= c && j < sz[u][t]; j++) if (c - j <= fuck) {
                        auto nxt = T(t, u, j);
                        if (!s.count(nxt)) s.insert(nxt), q.push(nxt);
                    }
                        
                }
        } 
        return res;
    }
};

int main() {
    TreePuzzle solver;
    auto res = solver.reachable({-1, 0, 1, 2, 3, 4, 0, 5, 7, 8, 6, 10, 11, 9, 13, 14, 12, 16, 16, 18,
15, 10, 17, 2, 23, 22, 21, 20, 27, 24, 19, 30, 28, 29, 17, 21, 34, 35, 31, 30,
36, 32, 31, 39, 26, 40, 3, 38, 45, 25, 49, 46, 41, 44, 51, 47, 18, 54, 48, 36,
43, 57, 52, 56, 60, 59, 53, 61, 64, 68, 37, 55, 71, 32, 26, 73, 28, 50, 75, 72,
70, 67, 74, 66, 79, 76, 78, 63, 69, 41, 83, 86, 80, 18, 82, 87, 58, 62, 42, 20},
{1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1}
);
    for (auto t : res) cout << t << ' ';
    cout << endl;
}
