#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int mod = 1e9 + 7;

typedef long long LL;

int chain[2][N], cir[N], vis[N];

typedef pair<int, int> P;

vector<P> G[N];

bool flag; int nw, A, B;

void dfs(int u, int ls) {
    vis[u] = 1, nw++;
    for (auto t : G[u]) if (t.first != ls) {
        if (!vis[t.first]) {
            dfs(t.first, u);
            if (t.second) A++;
            else B++;
        }
        else flag = true;
    } 
}

int frac[N];

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int main() {
    int n, m1, m2; scanf("%d%d%d", &n, &m1, &m2);
    for (int i = 1, a, b; i <= m1 + m2; i++) 
        scanf("%d%d", &a, &b), G[a].push_back(P(b, i <= m1)), G[b].push_back(P(a, i <= m1));
    frac[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod;
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        nw = 0, flag = false, A = 0, B = 0, dfs(i, 0);
        if (flag) cir[nw]++; else chain[A <= B][nw]++;
    }
    int res = 1;
    for (int i = 1; i <= n; i++) {
        res = (LL)res * Pow(i, cir[i]) % mod * frac[cir[i]] % mod;
        if (i & 1) res = (LL)res * frac[chain[1][i]] % mod;
        else {
            res = (LL)res * frac[chain[0][i]] % mod * Pow(2, chain[0][i]) % mod;
            res = (LL)res * frac[chain[1][i]] % mod * Pow(2, chain[1][i]) % mod;
        }
    }
    printf("%d\n", res);
    return 0;
}
