#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int N = 45;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int G[N][N], inv[N * 2];

int gauss(int n) {
    int res = 1;
    for (int i = 1; i < n; i++) {
        if (!G[i][i]) for (int j = i + 1; j < n; j++) 
            if (G[j][i]) { swap(G[i], G[j]), res = mod - res; break; }
        if (!G[i][i]) return 0;
        res = (LL)res * G[i][i] % mod;
        int inv = Pow(G[i][i], mod - 2);
        for (int j = i + 1; j < n; j++) if (G[j][i]) {
            int w = (LL)inv * G[j][i] % mod;
            for (int k = 1; k < n; k++) {
                G[j][k] = (G[j][k] - (LL)G[i][k] * w) % mod;
                if (G[j][k] < 0) G[j][k] += mod;
            }
        }
    }
    res = (res + mod) % mod;
    return res;
}   

void adde(int from, int to, int w) {
    G[from][from] = (G[from][from] + w) % mod;
    G[to][to] = (G[to][to] + w) % mod;
    G[from][to] = (G[from][to] + mod - w) % mod;
    G[to][from] = (G[to][from] + mod - w) % mod;
}

int largrange(vector<int> val) { 
    int n = val.size(); // 0 ... n - 1
    vector<int> ans(3);
    for (int i = 0; i < n; i++) {
        vector<int> w = { 1, 0, 0 };
        auto mul = [&](int a, int b) { // ax + b;
            vector<int> nxt(3, 0);
            for (int t = 0; t < 3; t++) {
                nxt[t] = (nxt[t] + (LL)w[t] * b) % mod;
                int t1 = (t + 1) % 3;
                nxt[t1] = (nxt[t1] + (LL)w[t] * a) % mod;
            }
            return nxt;
        };
        for (int j = 0; j < n; j++) if (j != i) {
            int a = inv[abs(i - j)];
            if (i < j) a = mod - a;
            int b = (LL)(mod - j) * a % mod;
            w = mul(a, b);
        }
        for (int j = 0; j < 3; j++)
            ans[j] = (ans[j] + (LL)w[j] * val[i]) % mod;
    }
    int res = 0;
    for (int j = 0; j < 3; j++) 
        res = (res + (LL)ans[j] * j) % mod;
    return res;
}

int from[N * N], to[N * N], w[N * N];

int main() {
    freopen("sum.in", "r", stdin), freopen("sum.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) 
        scanf("%d%d%d", &from[i], &to[i], &w[i]);
    for (int i = 1; i <= n * 2; i++) inv[i] = Pow(i, mod - 2);
    int ans = 0;
    for (int t = 1, base = 1; t <= 9; t++, base *= 3) {
        vector<int> val;
        for (int x = 0; x <= 2 * (n - 1) + 1; x++) {
            memset(G, 0, sizeof(G));
            for (int i = 1; i <= m; i++) 
                adde(from[i], to[i], Pow(x, w[i] % 3));
            val.push_back(gauss(n));
        }
        ans = (ans + (LL)largrange(val) * base) % mod;
        for (int i = 1; i <= m; i++) w[i] /= 3;
    }
    printf("%d\n", ans);
}