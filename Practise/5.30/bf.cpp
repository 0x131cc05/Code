#include <bits/stdc++.h>
using namespace std;

const int N = 510;
const int mod = 1e9 + 7;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int G[N][N];

int gauss(int n) {
    int res = 1;
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n; j++) if (G[j][i]) {
            swap(G[i], G[j]); break;
        }
        if (!G[i][i]) return 0;
        res = (LL)res * G[i][i] % mod;
        int inv = Pow(G[i][i], mod - 2);
        for (int j = i + 1; j < n; j++) if (G[j][i]) {
            int w = (LL)inv * G[j][i] % mod;
            for (int k = 1; k < n; k++) {
                G[j][k] = (G[j][k] - (LL)G[i][k] * w) % mod;
                G[j][k] = (G[j][k] + mod) % mod;
            }
        }
    }
    res = (res + mod) % mod;
    if (n & 1) res = mod - res;
    return res;
}

void adde(int from, int to) {
    G[from][from]++, G[to][to]++, G[from][to]--, G[to][from]--;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n, m; scanf("%d%d", &n, &m), memset(G, 0, sizeof(G));
        for (int i = 1; i <= n; i++) {
            adde(i, i == n ? 1 : i + 1);
            if (i <= m) adde(i, n + 1);
            else adde(i, n + 2);
        }
        adde(n + 1, n + 2);
        printf("%d\n", gauss(n + 2));
    }
}