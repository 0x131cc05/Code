#include <bits/stdc++.h>
using namespace std;

const int N = 100100;
const int mod = 1e9 + 7;

typedef long long LL;

inline void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

inline int Add(int x, int y) {
    int t = x + y;
    return t >= mod ? t - mod : t;
}

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

struct Tree {

int tree[N], n;

inline void update(int x, int y) {
    for (; x <= n; x += x & -x) Inc(tree[x], y);
}

inline int query(int x) {
    int res = 0;
    for (; x; x -= x & -x) Inc(res, tree[x]);
    return res;
}

inline int query(int l, int r) {
    return Add(mod - query(l - 1), query(r));
}

} A[11], B[11];

int S[11][11], C[11][11];

inline void pre() {
    S[0][0] = 1;
    for (int i = 1; i <= 10; i++) 
        for (int j = 1; j <= 10; j++) 
            S[i][j] = (S[i - 1][j - 1] + (LL)S[i - 1][j] * (i - 1)) % mod;
    for (int i = 0; i <= 10; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) 
            C[i][j] = Add(C[i - 1][j - 1], C[i - 1][j]);
    }
}

int wkr[N], zjk[N], pw[11][N], inv[11];

inline int FUCK(int n, int r) {
    int res = 1;
    for (int i = 1; i <= r; i++) 
        res = (LL)res * (n - i + 1) % mod * Pow(i, mod - 2) % mod;
    return res;
}

int main() { 
    int n, m, q; scanf("%d%d%d", &n, &m, &q), pre();
    for (int i = 1; i <= n; i++) wkr[i] = i - 1;
    for (int i = 1; i <= m; i++) zjk[i] = i;
    for (int i = 1; i <= max(n, m) + 11; i++) {
        pw[0][i] = 1;
        for (int j = 1; j <= 10; j++) pw[j][i] = (LL)pw[j - 1][i] * i % mod;
    }
    for (int i = 0; i <= 10; i++) {
        A[i].n = n, B[i].n = m;
        for (int j = 1; j <= n; j++) A[i].update(j, (LL)pw[i][j] * wkr[j] % mod); 
        for (int j = 1; j <= m; j++) B[i].update(j, (LL)pw[i][j] * zjk[j] % mod); 
    }
    inv[0] = 1;
    for (int i = 1; i <= 10; i++) 
        inv[i] = (LL)inv[i - 1] * Pow(i, mod - 2) % mod;
    while (q--) {
        char s[5]; int a, b, c, d; scanf("%s%d%d", s + 1, &a, &b);
        if (s[1] == 'Q') {
            scanf("%d%d", &c, &d); int k; scanf("%d", &k);
            static int tmpA[11], tmpB[11];
            for (int i = 0; i <= k; i++) {
                tmpA[i] = A[i].query(a, c), tmpB[i] = B[i].query(b, d);
            }
            auto solve = [&](int lim, int H[]) -> int {
                int res = 0;
                for (int j = 0; j <= k; j++) {
                    int t = 0;
                    for (int i = 0; i <= j; i++) {
                        int h = (LL)H[i] * pw[j - i][lim + k] % mod * C[j][i] % mod;
                        if ((j - i) & 1) h = mod - h;
                        Inc(t, h);
                    }
                    res = (res + (LL)t * S[k][j]) % mod;
                }
                res = (LL)res * inv[k] % mod;
                if (k & 1) res = mod - res;
                return res;
            };
            int res1 = (LL)solve(c, tmpA) * m % mod, res2 = solve(d, tmpB);
            res1 = (LL)res1 * FUCK(d - b + k + 1, k + 1) % mod, res2 = (LL)res2 * FUCK(c - a + k + 1, k + 1) % mod;
            printf("%d\n", Add(res1, res2));
        } else if (s[1] == 'R') {
            for (int i = 0; i <= 10; i++) {
                A[i].update(a, (LL)pw[i][a] * (wkr[b] - wkr[a] + mod) % mod);
                A[i].update(b, (LL)pw[i][b] * (wkr[a] - wkr[b] + mod) % mod);
            }
            swap(wkr[a], wkr[b]);
        } else {
            for (int i = 0; i <= 10; i++) {
                B[i].update(a, (LL)pw[i][a] * (zjk[b] - zjk[a] + mod) % mod);
                B[i].update(b, (LL)pw[i][b] * (zjk[a] - zjk[b] + mod) % mod);
            }
            swap(zjk[a], zjk[b]);
        }
    }
    return 0;
}