#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int col[N]; vector<int> G[N];

const double fin = 1e-14;

int upd(int u, int c) {
    int ct = 0;
    for (auto v : G[u]) if (col[u] == col[v]) ct--;
    col[u] = c;
    for (auto v : G[u]) if (col[u] == col[v]) ct++;
    return ct;
}

int main() {
    freopen("03colors7.in", "r", stdin); freopen("03colors7.out", "w", stdout);
    int n, m, ct = 0; scanf("%d%d", &n, &m), srand(clock() + (unsigned long long)(new char));
    for (int i = 1; i <= m; i++) {
        int u, v; scanf("%d%d", &u, &v), col[i] = 1, ct++;
        G[u].push_back(v), G[v].push_back(u);
    }
    double T = 1, step = 0.999999;
    while (T > fin) {
        T *= step;
        int u = rand() % n + 1, tmp = col[u], nw = rand() % 3 + 1;
        while (tmp == nw) nw = rand() % 3 + 1;
        int wkr = ct + upd(u, nw);
        if (wkr <= ct) ct = wkr;
        else if (exp((ct - wkr) / T) > fabs((double)(rand() % 1000) / 1000.)) ct = wkr;
        else col[u] = tmp;
        if (!ct) break;
    }
    assert(!ct);
    for (int i = 1; i <= n; i++) printf("%d ", col[i]);
}
