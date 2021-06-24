#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int N = 510;
const int M = 110;

typedef long long LL;

inline void Inc(int &x, int y) { x += y, x -= x >= mod ? mod : 0; }
inline void Dec(int &x, int y) { x -= y, x += x < 0 ? mod : 0; }
inline int Add(int x, int y) { int t = x + y; return t >= mod ? t - mod : t; }
inline int Sub(int x, int y) { int t = x - y; return t < 0 ? t + mod : t; }

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int n, k;

int flag[N], prime[N], tot;

int G[N][N], G1[N][N];

inline void sieve() {
    for (int i = 2; i <= n; i++) {
        if (!flag[i]) prime[++tot] = i;
        for (int j = 1; j <= tot && i * prime[j] <= n; j++) {
            flag[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    for (int i = 1; i <= n; i++) {
        int tmp = i;
        for (int j = 1; j <= tot; j++) {
            int ct = 0;
            while (tmp % prime[j] == 0) tmp /= prime[j], ct++;
            G[j][ct]++, G1[i][prime[j]] = ct;
        }
    }
}

namespace task1 {

int dimension, lim, sum;

int up[110];

inline void pre(int type = 0) {
    lim = ceil(sqrt(n)), sum = 1; int hh = n;
    if (!type) hh = lim;
    for (int i = 1; i <= tot; i++) {
        if (prime[i] > lim) break;
        dimension = i, up[i] = 1;
        int tmp = hh; 
        while (tmp /= prime[i]) up[i]++; 
        sum *= up[i];
    }
}

inline int encode(const int base[]) {
    int code = 0;
    for (int i = 1; i <= dimension; i++) 
        code *= up[i], code += base[i];
    return code;
} 

inline int getLCM(int code) {
    int res = 1;
    for (int i = dimension; i >= 1; i--) {
        int t = code % up[i]; code /= up[i];
        for (int j = 1; j <= t; j++) res = (LL)res * prime[i] % mod;
    }
    return res;
}

inline void decode(int code, int result[]) {
    for (int i = dimension; i >= 1; i--) 
        result[i] = code % up[i], code /= up[i];
}

inline void unpack(int n, int result[]) {
    for (int i = 1; i <= dimension; i++) {
        result[i] = 0; 
        while (n % prime[i] == 0) n /= prime[i], result[i]++;
    }
}

inline void FWT(int a[]) {
    for (int nw = dimension, step = 1; nw >= 1; step *= up[nw--]) 
        for (int i = 0; i < sum; i += step * up[nw])
            for (int j = i; j < i + step * (up[nw] - 1); j += step)
                for (int k = 0; k < step; k++)
                    Inc(a[j + k + step], a[j + k]);
}

inline void IFWT(int a[]) {
    for (int nw = dimension, step = 1; nw >= 1; step *= up[nw--]) 
        for (int i = 0; i < sum; i += step * up[nw])
            for (int j = i + step * (up[nw] - 2); j >= i; j -=  step)
                for (int k = 0; k < step; k++)
                    Dec(a[j + k + step], a[j + k]);
}

// g[i][j][k]: [1, i]的数，选j个，lcm为k
int g[80][M][1010];

inline void solve_g() {
    for (int i = 1; i <= lim; i++) {
        g[i][0][0] = 1;
        for (int j = 1; j <= k; j++) 
            for (int l = 0; l < sum; l++) if (g[i][j - 1][l]) {
                static int buk[60]; decode(l, buk);
                for (int nw = 1; nw <= i; nw++) {
                    static int hh[60];
                    for (int t = 1; t <= dimension; t++) 
                        hh[t] = max(G1[nw][prime[t]], buk[t]);
                    Inc(g[i][j][encode(hh)], g[i][j - 1][l]);
                }
            }
    }
    // cout << "g: " << endl;
    // for (int i = 0; i <= k; i++)
    //     for (int j = 0; j < sum; j++)
    //         cout << i << ' ' << getLCM(j) << ' ' << g[1][i][j] << endl;
    // cout << "end" << endl;
}

int C[N][N];

// f[i][j][k]: 考虑了[i, n]的质数，已经有j个位置确定好了，[1, sqrt(n)]的lcm为k
int f[N][M][1010], tp[1010], id[1010];

inline int solve() {
    pre(), solve_g();
    for (int i = 0; i <= k; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = Add(C[i - 1][j - 1], C[i - 1][j]);
    }
    f[tot + 1][0][0] = 1;
    for (int i = tot; i > dimension; i--) {
        cout << "solve: " << prime[i] << endl;
        for (int j = 0; j <= k; j++) if (f[i + 1][j][0])
            for (int nw = 0; nw + j <= k; nw++) {
                // cout << j << ' ' << nw << endl;
                int w = C[nw + j][j], t = n / prime[i]; static int A[1010], B[1010];
                if (nw) w = (LL)w * prime[i] % mod;
                for (int l = 0; l < sum; l++) A[l] = f[i + 1][j][l], B[l] = g[t][nw][l];
                FWT(A), FWT(B);
                for (int l = 0; l < sum; l++) A[l] = (LL)A[l] * B[l] % mod;
                IFWT(A); 
                for (int l = 0; l < sum; l++) Inc(f[i][j + nw][l], (LL)A[l] * w % mod);
            }
    }
    // cout << prime[dimension + 1] << endl;
    // for (int j = 0; j <= k; j++)
    //     for (int l = 0; l < sum; l++)
    //         cout << j << ' ' << getLCM(l) << ' ' << f[dimension + 1][j][l] << endl;
    for (int i = 0; i < sum; i++) tp[i] = getLCM(i);
    int last = sum; pre(1);
    static int fk[110];
    for (int i = 0; i < last; i++) 
        unpack(tp[i], fk), id[i] = encode(fk);
    static int B[100010]; memset(B, 0, sizeof(B));
    for (int i = 1; i <= n; i++) {
        int mx = 0;
        for (int j = 1; j <= tot; j++) if (i % prime[j] == 0) mx = j;
        if (mx > dimension) continue;
        unpack(i, fk), B[encode(fk)]++;
    }
    FWT(B); int res = 0;
    for (int i = 0; i <= k; i++) {
        static int A[100010];
        for (int l = 0; l < sum; l++) A[l] = 0;
        for (int l = 0; l < last; l++) A[id[l]] = f[dimension + 1][i][l];
        FWT(A);
        for (int l = 0; l < sum; l++)
            A[l] = (LL)A[l] * Pow(B[l], k - i) % mod;
        IFWT(A);
        for (int l = 0; l < sum; l++) {
            res = (res + (LL)getLCM(l) * A[l] % mod * C[k][i]) % mod;
            // cout << "fuck: " << getLCM(l) << ' ' << (LL)getLCM(l) * A[l] % mod * C[k][i] % mod << endl;
            // cout << k << ' ' << i << ' ' << C[k][i] << endl;
        }
        // cout << i << ' ' << res << endl;
    }
    return res;
}

}

namespace task2 {

int dp[M][30];

inline int solve() {
    int res = 1;
    for (int i = 1; i <= tot; i++) {
        memset(dp, 0, sizeof(dp)), dp[0][0] = 1;
        int tp = 1;
        while (G[i][tp + 1]) tp++;
        for (int j = 1; j <= k; j++)
            for (int a = 0; a <= tp; a++)
                for (int b = 0; b <= tp; b++) 
                    dp[j][max(a, b)] = (dp[j][max(a, b)] + (LL)dp[j - 1][a] * G[i][b]) % (mod - 1);
        for (int j = 0, t = 1; j <= tp; j++, t = (LL)t * prime[i] % mod)
            res = (LL)res * Pow(t, dp[k][j]) % mod;
    }
    return res;
}

}

int main() {
    cin >> n >> k, sieve();
    printf("%d %d\n", task1::solve(), task2::solve());
    return 0;
}