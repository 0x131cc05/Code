#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

typedef long long LL;

int G[11][11], id[11];

int main() {
    freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) G[i][j] = 1;
    for (int i = 1; i <= n; i++) id[i] = i;
    for (int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c), G[a][b] = c;
    }   
    int ans = 0; 
    do {
        int res = 1;
        for (int i = 1; i <= n; i++) res = (LL)res * G[i][id[i]] % mod;
        ans = (ans + res) % mod;
    } while (next_permutation(id + 1, id + n + 1));
    printf("%d\n", ans);
}