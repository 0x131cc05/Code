#include <bits/stdc++.h>
using namespace std;

const int N = 1510 * 1510;

typedef pair<int, int> P;

int fa[N];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

char s[1510][1510], t[1510][1510];

int id[1510][1510], ncnt;

void merge(int a, int b) {
    if (a > b) swap(a, b);
    fa[find(a)] = find(b);
}

vector<int> G[1510];

int ind[1510];

vector<P> fuck[N];

int main() {
//    freopen("matrix.in", "r", stdin), freopen("matrix.out", "w", stdout);
    int n, m; scanf("%d", &n), m = n;
    for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++) if (i != j) id[i][j] = ++ncnt;
    for (int i = 1; i <= ncnt; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) {
        vector<int> hh;
        for (int j = 1; j <= m; j++) if (s[i][j] == '1') hh.push_back(j);
        for (int j = 1; j <= m; j++) if (s[i][j] == '0') {
            int ls = 0;
            for (auto t : hh) {
                if (ls) merge(id[ls][j], id[t][j]), merge(id[j][ls], id[j][t]);
                ls = t;
            }
        }
    }
    for (int i = 1; i <= m; i++)
        for (int j = i + 1; j <= m; j++)
            if (find(id[i][j]) == find(id[j][i])) {
                return puts("NO"), 0;
            }
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++) if (i != j) {
            fuck[find(id[i][j])].push_back(P(i, j));
        }
    for (int i = 1; i <= m; i++)
        for (int j = i + 1; j <= m; j++) if (find(id[i][j]) == id[i][j]) {
            for (auto t : fuck[id[i][j]]) 
                G[t.first].push_back(t.second), ind[t.second]++;
        }
    queue<int> q; 
    for (int i = 1; i <= m; i++) if (!ind[i]) q.push(i);
    puts("YES");
    int ct = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop(), ct++;
        for (int i = 1; i <= n; i++) t[i][ct] = s[i][u];
        for (auto v : G[u]) if (!--ind[v]) q.push(v);
    }
    for (int i = 1; i <= n; i++, puts(""))
        for (int j = 1; j <= m; j++) putchar(t[i][j]);
}
