#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int mod = 998244353;

typedef long long LL;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt; 
}

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int n, pw[11][N], type, q;

namespace sol1 {

int ct[N], hh[N];

void pre(int u, int f) {
    bool flag = false;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) pre(e[i].to, u), flag = true;
    hh[u] = !flag;
}

int L, R, tot, k, res = 0;

void dfs(int u, int f) {
    ct[u] = hh[u] && L <= u && u <= R;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u), ct[u] += ct[e[i].to];
    res = (res + pw[k][ct[u]] + (LL)pw[k][tot - ct[u]]) % mod;
}

inline int solve(int L, int R, int k) {
    sol1::k = k, sol1::L = L, sol1::R = R, res = 0, tot = 0;
    for (int i = L; i <= R; i++) tot += hh[i];
    if (!tot) return 0;
    dfs(1, 0), res = n - (LL)res * Pow(Pow(tot, k), mod - 2) % mod;
    res = (res + mod) % mod;
    return res;
}

void main() {
    pre(1, 0); int lastans = 0;
    while (q--) {
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        if (type) l ^= lastans, r ^= lastans;
        printf("%d\n", lastans = solve(l, r, k) % mod);
    }
}

}

int coef[11][11][N];

namespace sol2 {

int C[11][11], mx[N], ct[N], hh[N], mn[N];

vector<int> wkr[100], son[N]; int layer;

inline void fuck(int u, int s) {
    for (int i = 2, tmp = (LL)s * s % mod; i <= 10; i++, tmp = (LL)tmp * s % mod) {
        for (int j = i, t = 1; j >= 0; j--) {
            coef[i][j][u] = (LL)C[i][j] * t % mod;
            if ((i - j) & 1) coef[i][j][u] = mod - coef[i][j][u];
            t = (LL)t * s % mod;
        }
        Inc(coef[i][0][u], tmp);
    }
}

void dfs(int dep, int u, int f) {
    wkr[dep].push_back(u), mx[u] = u, mn[u] = 1e9;
    bool flag = false;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(dep + 1, e[i].to, u), mx[u] = mx[e[i].to], ct[u] += ct[e[i].to], mn[u] = min(mn[u], mn[e[i].to]);
            for (auto t : son[e[i].to]) son[u].push_back(t);
            flag = true;
        }
    if (!flag) hh[u] = 1, son[u].push_back(u), ct[u] = 1, mx[u] = mn[u] = u;
    fuck(u, ct[u]), layer = max(layer, dep);
//    assert(layer <= 30);
}

int tot, L, R, k, tmp;

inline int calc(int u) {
    int ct = upper_bound(son[u].begin(), son[u].end(), R) - lower_bound(son[u].begin(), son[u].end(), L);
    return (pw[k][ct] + pw[k][tot - ct]) % mod;
}

inline int solve(int layer) {
    int l = 0, r = wkr[layer].size() - 1, mid, posL = -1, posR = -1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (mx[wkr[layer][mid]] >= L) posL = mid, r = mid - 1;
        else l = mid + 1;
    }
    l = 0, r = wkr[layer].size() - 1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (mn[wkr[layer][mid]] <= R) posR = mid, l = mid + 1;
        else r = mid - 1;
    }
    if (posL == -1 || posR == -1) return 0;
    if (posL > posR) return 0;
    tmp += posR - posL + 1;
    int res = 0;
//    cout << posL << ' ' << posR << endl;
    if (posL < posR - 1) for (int i = 0, tmp = 1; i <= k; i++, tmp = (LL)tmp * tot % mod) {
//        cout << k << ' ' << i << ' ' << coef[k][i][wkr[layer][posL]] << endl;
        int w = (coef[k][i][wkr[layer][posR - 1]] - coef[k][i][wkr[layer][posL]] + mod) % mod;
//        cout << posL << ' ' << posR << ' ' << w << endl;
//        cout << "layer: " << layer << ' ' << (LL)w * tmp % mod << endl;
        res = (res + (LL)w * tmp) % mod;
    }
    Inc(res, calc(wkr[layer][posL]));
    if (posR != posL) Inc(res, calc(wkr[layer][posR]));
    return res;
}

void main() {
    for (int i = 0; i <= 10; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    dfs(1, 1, 0);
    for (int i = 1; i <= layer; i++) {
        for (int j = 0; j + 1 < wkr[i].size(); j++) {
            int A = wkr[i][j], B = wkr[i][j + 1];
//            cout << i << ' ' << A << ' ' << B << ' ' << coef[2][0][A] << ' ' << coef[2][0][B] << endl;
            for (int t = 2; t <= 10; t++)
                for (int t1 = 0; t1 <= t; t1++) 
                    Inc(coef[t][t1][B], coef[t][t1][A]);
        }
            
    }
//    cout << coef[2][0][3] << endl;
    int lastans = 0;
    while (q--) {
        scanf("%d%d%d", &L, &R, &k), tmp = 0; int res = 0;
        if (type) L ^= lastans, R ^= lastans;
        tot = upper_bound(son[1].begin(), son[1].end(), R) - lower_bound(son[1].begin(), son[1].end(), L);
        if (!tot) { puts("0"), lastans = 0; continue; }
        for (int i = layer; i >= 1; i--) Inc(res, solve(i));
        res = tmp - (LL)res * Pow(Pow(tot, k), mod - 2) % mod, Inc(res, mod);
        printf("%d\n", lastans = res);
    }
}


}

int f[N];

int main() {
    scanf("%d%d%d", &type, &n, &q);
    for (int i = 2; i <= n; i++) scanf("%d", &f[i]);
    for (int i = 1; i <= n; i++) {
        pw[0][i] = 1;
        for (int j = 1; j <= 10; j++) pw[j][i] = (LL)pw[j - 1][i] * i % mod;
    }
    for (int i = n; i >= 2; i--) adde(f[i], i);
    if (n <= 5000) sol1::main();
    else sol2::main();
}
