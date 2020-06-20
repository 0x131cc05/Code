#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
} 

inline void Inc(int &x, int y = 0) {x += y, x -= x >= mod ? mod : 0;}
inline void Dec(int &x, int y = 0) {x -= y, x += x < 0 ? mod : 0;}
inline int Add(int x, int y) {x += y; return x >= mod ? x - mod : x;}
inline int Sub(int x, int y) {x -= y; return x < 0 ? x + mod : x;}

struct WEN {

int A, B; // Ax + B

WEN operator * (int x) {
    return (WEN){ (LL)A * x % mod, (LL)B * x % mod };
}

WEN operator + (int x) {
    return (WEN){ A, Add(B, x) };
}

WEN operator + (WEN x) {
    return (WEN){ Add(A, x.A), Add(B, x.B) };
}

};

inline int solve(WEN a, int b) {
    return (LL)(b - a.B + mod) * Pow(a.A, mod - 2) % mod;
}

int E[N], P[N], p, t; WEN f[N], g[N]; 

inline void pre(int t) {
    f[0] = g[0] = (WEN){ 0, 0 }, f[1] = g[1] = (WEN){ 1, 0 };
    int A = Pow(p, mod - 2), B = (LL)(mod + 1 - p) * A % mod;
    for (int i = 2; i <= t; i++) {
        f[i] = f[i - 1] * A + f[i - 2] * (mod - B);
        g[i] = g[i - 1] * A + g[i - 2] * (mod - B) + (mod - A);
    }
    P[t] = 1, E[t] = 0, P[1] = solve(f[t], 1), E[1] = solve(g[t], 0);
    for (int i = 1; i < t; i++) {
        P[i] = ((LL)f[i].A * P[1] + f[i].B) % mod;
        E[i] = ((LL)g[i].A * E[1] + g[i].B) % mod;
    }
}

int F[N][2][2], G[N][2][2];

inline int Just_DOIT(LL r) {
    if (r < 0) return 0;
    memset(F, 0, sizeof(F)), memset(G, 0, sizeof(G));
    F[0][0][1] = 1; int i = 0; LL hh = r;
    for (i = 0; hh; i++) {
        int nw = hh % t; hh /= t;
        for (int a = 0; a <= 1; a++)
            for (int b = 0; b <= 1; b++) if (F[i][a][b]) 
                for (int c = 0; c < t; c++) {
                    int nxt = c == nw ? b : (c < nw);
                    if (c + a == t) {
                        Inc(F[i + 1][1][nxt], F[i][a][b]);
                        Inc(G[i + 1][1][nxt], G[i][a][b]);
                    } else if (c + a) {
                        Inc(F[i + 1][1][nxt], (LL)F[i][a][b] * P[c + a] % mod);
                        Inc(F[i + 1][0][nxt], (LL)F[i][a][b] * (mod + 1 - P[c + a]) % mod);
                        Inc(G[i + 1][1][nxt], (G[i][a][b] + (LL)F[i][a][b] * E[c + a]) % mod * P[c + a] % mod);
                        Inc(G[i + 1][0][nxt], (G[i][a][b] + (LL)F[i][a][b] * E[c + a]) % mod * (mod + 1 - P[c + a]) % mod);
                    } else {
                        Inc(F[i + 1][0][nxt], F[i][a][b]);
                        Inc(G[i + 1][0][nxt], G[i][a][b]);
                    }
                }
    }   
    int tmp = (LL)E[1] * Pow(mod + 1 - P[1], mod - 2) % mod;
    return Add(G[i][0][1], Add(G[i][1][1], (LL)F[i][1][1] * tmp % mod));
}

int main() {
    freopen("lowbit.in", "r", stdin), freopen("lowbit.out", "w", stdout); 
    int a, b; LL l, r; 
    scanf("%d%d%d%lld%lld", &t, &a, &b, &l, &r), p = (LL)a * Pow(b, mod - 2) % mod, pre(t);
    printf("%d\n", Sub(Just_DOIT(r), Just_DOIT(l - 1)));
}
