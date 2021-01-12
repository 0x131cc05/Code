#include <bits/stdc++.h>
using namespace std;

const int N = 30010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int Wn[2][17][N << 1], r[N << 2];

inline void Inc(int &x, int y) { x += y, x -= x >= mod ? mod : 0; }
inline int Sub(int x, int y) { int t = x - y; return t < 0 ? t + mod : t; }

inline void Pre(int len) {
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) {
        int t1 = Pow(3, (mod - 1) / mid), t2 = Pow(t1, mod - 2);
        Wn[0][step][0] = Wn[1][step][0] = 1, Wn[1][step][1] = t1, Wn[0][step][1] = t2;
        for (int i = 2; i < (mid >> 1); i++) {
            Wn[1][step][i] = (LL)Wn[1][step][i - 1] * t1 % mod;
            Wn[0][step][i] = (LL)Wn[0][step][i - 1] * t2 % mod;
        }
    }
}

inline void NTT(vector<int> &a, int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++) {
                int t = (LL)Wn[type][step][j - i] * a[j + (mid >> 1)] % mod;
                a[j + (mid >> 1)] = Sub(a[j], t), Inc(a[j], t);
            }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

inline void GetR(int len, int l) {
    for (int i = 1; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
}

int n, m;

inline vector<int> mul(vector<int> a, vector<int> b) { 
    int t = a.size() + b.size() - 2, len = 1, l = 0;
    while (len <= t) len <<= 1, l++;
    GetR(len, l), a.resize(len + 1), b.resize(len + 1);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = (LL)a[i] * b[i] % mod;
    NTT(a, len, 0), a.resize(min(n - 1, t + 1));
    return a;
}

int S[62][62];

inline void GetS() {
    S[0][0] = 1;
    for (int i = 1; i <= 61; i++) 
        for (int j = 1; j <= i; j++) 
            S[i][j] = (S[i - 1][j - 1] + (LL)j * S[i - 1][j]) % mod;
}

struct data {

vector<int> A, B; // A: prod, B: ans

data operator * (const data &b) {
    vector<int> L = mul(B, b.A), R = mul(A, b.B);
    if (L.size() < R.size()) L.resize(R.size());
    for (int i = 0; i < R.size(); i++) Inc(L[i], R[i]);
    return (data){ mul(A, b.A), L };
}

int operator [] (int pos) {
    if (pos >= B.size()) return 0;
    return B[pos];
} 

};

int a[N];

data solve(int l, int r) {
    if (l == r) {
        vector<int> A, B; A.resize(m * 2 + 1), B.resize(m + 1); 
        for (int i = 0, coef = 1; i <= m * 2; i++) {
            coef = (LL)coef * a[l] % mod;
            A[i] = (LL)coef * S[2 * m + 1][i + 1] % mod;
            if (i <= m) B[i] = (LL)coef * S[m + 1][i + 1] % mod;
        }
        return (data){ B, A };
    }
    int mid = (l + r) >> 1;
    return solve(l, mid) * solve(mid + 1, r);
}

int main() {
    scanf("%d%d", &n, &m), GetS(); int len = 1, s = 0;
    while (len <= n * 2) len <<= 1;
    Pre(len);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), Inc(s, a[i]);
    data res = solve(1, n); 
    int ans = 0;
    for (int i = 0, coef = 1; i <= n - 2; i++, coef = (LL)coef * s % mod * Pow(i, mod - 2) % mod) 
        ans = (ans + (LL)coef * res[n - 2 - i]) % mod;
    for (int i = 1; i <= n - 2; i++) ans = (LL)ans * i % mod;
    printf("%d\n", ans);
    return 0;
}
