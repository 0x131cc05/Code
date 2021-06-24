#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

typedef pair<int, int> P;

vector<P> res;

int G[N][N], n;

void operate(int a, int b, bool type) {
    assert(G[a][b]);
    int x = 0, y = 0;
    for (int i = 1; i <= n; i++) {
        if (G[a][i] && G[b][i]) {
            if (!x) x = i;
            else y = i;
        }
    }
    G[x][y] = G[y][x] = 1, G[a][b] = G[b][a] = 0;
    if (type) res.push_back(P(a, b));
    else res.push_back(P(x, y));
}

void run(bool type) {
    for (int i = 1; i <= n; i++) {
        int nxt = i == n ? 1 : i + 1;
        G[i][nxt] = G[nxt][i] = 1;
    }
    for (int i = 1; i < n; i++) if (G[1][i]) {
        int j = i + 1;
        while (!G[1][j]) j++;
        if (j == i + 1) continue;
        operate(i, j, type), i--;
    }
}

int main() {
    scanf("%d", &n); vector<P> A, B;
    for (int i = 1, a, b; i <= n - 3; i++) scanf("%d%d", &a, &b), G[a][b] = G[b][a] = 1;
    run(true), A = res, res.clear(), memset(G, 0, sizeof(G));
    for (int i = 1, a, b; i <= n - 3; i++) scanf("%d%d", &a, &b), G[a][b] = G[b][a] = 1;
    run(false), B = res, reverse(B.begin(), B.end());
    printf("%d\n", A.size() + B.size());
    for (auto t : A) printf("%d %d\n", t.first, t.second);
    for (auto t : B) printf("%d %d\n", t.first, t.second);
}