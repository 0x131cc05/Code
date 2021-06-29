#include <bits/stdc++.h>
using namespace std;

const int N = 15;

typedef long long LL;

vector<LL> path[N][1 << 14];

LL L, G[N][N];

int lim, n, lim1, hh;

void dfs(int u, int s, LL cur, int ct) {
    if (cur > L) return;
    if (ct == lim || ct == lim1) 
        path[u][s].push_back(cur);
    if (ct == lim) return;
    int remain = ((1 << n) - 1) ^ s;
    while (remain) {
        int p = __builtin_ctz(remain) + 1;
        dfs(p, s | (1 << p - 1), cur + G[u][p], ct + 1);
        remain ^= (1 << p - 1);
    }
}

int main() {
    freopen("hamilton.in", "r", stdin), freopen("hamilton.out", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> L;
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= n; j++) 
            cin >> G[i][j];
    lim = (n + 1) / 2 + 1, lim1 = n + 2 - lim;  
    dfs(1, 1, 0, 1);
    for (int j = 2; j <= n; j++)
        for (int s = 1; s < 1 << n; s += 2) sort(path[j][s].begin(), path[j][s].end());
    for (int j = 2; j <= n; j++) {
        for (int s = 1; s < 1 << n; s += 2) if (__builtin_popcount(s) == lim) {
            if (!(s & (1 << j - 1))) continue;
            int other = ((1 << n) - 1) ^ s;
            other = other | 1 | (1 << j - 1);
            for (auto t : path[j][s]) {
                while (path[j][other].size() && path[j][other].back() + t > L) path[j][other].pop_back();
                if (path[j][other].size() && path[j][other].back() + t == L) {
                    cout << "possible" << endl;
                    return 0;
                }
            }
        } 
    }
    cout << "impossible" << endl;
}
