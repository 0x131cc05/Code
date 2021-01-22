#include <bits/stdc++.h>
using namespace std;

const int N = 250010;
const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int w[2][N << 2], _all;

void pre(int n) {
    int &len = _all = 1;     
    while (len <= n * 2) len <<= 1;
    w[0][0] = w[1][0] = 1, w[1][1] = Pow(3, (mod - 1) / len), w[0][1] = Pow(w[1][1], mod - 2);
    for (int i = 2; i < len; i++) 
        w[0][i] = (LL)w[0][i - 1] * w[0][1] % mod, w[1][i] = (LL)w[1][i - 1] * w[1][1] % mod;
}

int r[N << 2];

void getR(int len, int l) {
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
}

template<class T>
void NTT(T a, int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2, step = 1; mid <= len; mid <<= 1, step++) 
        for (int i = 0; i < len; i += mid) {
            int cur = 0, tmp = _all >> step;
            for (int j = i; j < i + (mid >> 1); j++, cur += tmp) {
                int t = (LL)a[j + (mid >> 1)] * w[type][cur] % mod;
                a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
            } 
        }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

vector<int> Mul(vector<int> A, vector<int> B) {
    int a = A.size(), b = B.size(), len = 1, l = 0;
    while (len <= a + b) len <<= 1, l++;
    getR(len, l), A.resize(len), B.resize(len);
    NTT<vector<int>&>(A, A.size(), 1), NTT<vector<int>&>(B, B.size(), 1);
    for (int i = 0; i < len; i++) A[i] = (LL)A[i] * B[i] % mod;
    NTT<vector<int>&>(A, A.size(), 0), A.resize(a + b - 1);
    return A;
}

int f[3][3][N << 2];

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

void solve(int n) {
    assert(n);
    f[0][0][0] = f[1][1][0] = f[2][2][0] = 1;
    if (n == 1) return;
    static int g[3][3][N << 2]; 
    auto clr = [&](int m) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) 
                fill(g[i][j], g[i][j] + m + 1, 0);
    };
    if (n & 1) {
        solve(n - 1), clr(n);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) 
                for (int t = 0; t < n; t++) if (f[i][j][t]) 
                    for (int k = 0; k < 3; k++) 
                        Inc(g[i][k][t + (k > j)], f[i][j][t]);
    } else {
        solve(n / 2);
        int len = 1, l = 0;
        while (len <= n) len <<= 1, l++;
        getR(len, l), clr(len);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) NTT<int*>(f[i][j], len, 1);
        int w = Pow(3, (mod - 1) / len);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++)
                    for (int l = 0; l < 3; l++) 
                        for (int t = 0, tmp = 1; t < len; t++, tmp = (LL)tmp * w % mod) 
                            g[i][l][t] = (g[i][l][t] + (LL)f[i][j][t] * f[k][l][t] % mod * (k > j ? tmp : 1)) % mod;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) NTT<int*>(g[i][j], len, 0), fill(f[i][j], f[i][j] + len, 0);
    }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int t = 0; t <= n; t++) f[i][j][t] = g[i][j][t];
}

char s[N]; double pos[256];

vector<vector<int>> poly;
vector<int> solve(int l, int r) {
    if (l > r) return { 1 };
    if (l == r) return poly[l];
    int mid = (l + r) >> 1;
    return Mul(solve(l, mid), solve(mid + 1, r));
}

int C[N];

int main() {
    LL k; scanf("%lld%s", &k, s + 1);
    int n = strlen(s + 1), ct = 0; pre(n);
    pos['k'] = -1, pos['y'] = 0.1, pos['n'] = 1.1, pos['c'] = 1.2;
    for (int i = 1; i <= n; i++) {
        int j = i;
        while (j < n && (s[i] == 'e') == (s[j + 1] == 'e')) j++;
        if (s[i] == 'e') {
            solve(j - i + 1); 
            vector<int> tmp(j - i + 3);
            for (int a = 0; a < 3; a++)
                for (int b = 0; b < 3; b++) {
                    int delta = (i == 1 ? 0 : (a > pos[s[i - 1]])) + (j == n ? 0 : (pos[s[j + 1]] > b));
                    for (int t = 0; t <= j - i; t++) 
                        Inc(tmp[delta + t], f[a][b][t]), f[a][b][t] = 0;
                }
            while (!tmp.back()) tmp.pop_back();
            poly.push_back(tmp);
        } else {
            for (int a = i + 1; a <= j; a++)
                if (pos[s[a]] > pos[s[a - 1]]) ct++;
        }
        i = j;
    }
    vector<int> ans = solve(0, (int)poly.size() - 1);
    int res = 0, c = 1; k = (k + ct) % mod;
    for (int i = 1; i <= n; i++) c = (LL)c * Pow(i, mod - 2) % mod * (k - i + 1) % mod;    
    for (int i = 0; i < ans.size(); i++) {
        if (k + i == n) c = 1;
        res = (res + (LL)c * ans[i]) % mod;
        c = (LL)c * (k + i + 1) % mod * Pow(k - n + i + 1, mod - 2) % mod;
    }
    printf("%d\n", (res + mod) % mod);
}