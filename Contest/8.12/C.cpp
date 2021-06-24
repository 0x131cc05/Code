#include <bits/stdc++.h>
using namespace std;

const int N = 400010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline void Inc(int &x, int y) { x += y, x -= x >= mod ? mod : 0; }
inline void Dec(int &x, int y) { x -= y, x += x < 0 ? mod : 0; }
inline int Add(int x, int y) { int t = x + y; return t >= mod ? t - mod : t; }
inline int Sub(int x, int y) { int t = x - y; return t < 0 ? t + mod : t; }

int Wn[2][20][N << 1], r[N << 2];

inline void pre(int len) {
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) {
        int t = Pow(3, (mod - 1) / mid), t1 = Pow(t, mod - 2);
        Wn[0][step][0] = Wn[1][step][0] = 1, Wn[1][step][1] = t, Wn[0][step][1] = t1;
        for (int i = 2; i < (mid >> 1); i++) {
            Wn[1][step][i] = (LL)Wn[1][step][i - 1] * t % mod;
            Wn[0][step][i] = (LL)Wn[0][step][i - 1] * t1 % mod;
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

inline vector<int> mul(vector<int> A, vector<int> B) {
    int tot = A.size() + B.size() - 2, len = 1, l = 0;
    while (len <= tot) len <<= 1, l++;
    A.resize(len), B.resize(len); 
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    NTT(A, len, 1), NTT(B, len, 1);
    for (int i = 0; i < len; i++) A[i] = (LL)A[i] * B[i] % mod;
    NTT(A, len, 0), A.resize(tot + 1);
    return A;
}

int frac[N * 2], inv[N * 2];

inline int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int num[N]; vector<int> F[N];

vector<int> solve(int l, int r) {
    if (l == r) return F[l];
    int mid = (l + r) >> 1;
    return mul(solve(l, mid), solve(mid + 1, r));
}

vector<int> get(int a) {
    vector<int> A(a + 1, 0), B(a + 1, 0);
    for (int i = 0; i <= a; i++) A[i] = (LL)Pow(i, a) * inv[i] % mod;
    for (int i = 0; i <= a; i++) {
        B[i] = inv[i];
        if (i & 1) B[i] = mod - B[i];
    }
    A = mul(A, B), A.resize(a + 1);
    for (int i = 0; i <= a; i++) A[i] = (LL)A[i] * frac[i] % mod * inv[a] % mod;
    return A;
}

int main() {
    int n, m = 0, len = 1; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]), m += num[i];
    sort(num + 1, num + n + 1);
    while (len <= m * 2) len <<= 1;
    pre(len), frac[0] = inv[0] = 1;
    for (int i = 1; i <= m * 2; i++) frac[i] = (LL)frac[i - 1] * i % mod;
    inv[m * 2] = Pow(frac[m * 2], mod - 2);
    for (int i = m * 2 - 1; i >= 1; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % mod;
    for (int i = 1; i <= n; i++) {
        F[i].resize(num[i] + 1); vector<int> A(num[i] + 1, 0), B(num[i] + 1, 0);
        vector<int> tmp = get(num[i]);
        for (int j = 1; j <= num[i]; j++) {
            A[j] = (LL)tmp[j] * frac[j - 1] % mod;
            // cout << C(num[i] + j - 1, j * 2 - 1) << ' ' << num[i] << ' ' << j << endl;
            if (j & 1) A[j] = mod - A[j];
            if (i == 1) A[j] = (LL)A[j] * Pow(j, mod - 2) % mod;
        }
        for (int j = 0; j < num[i]; j++) B[num[i] - j] = inv[j];
        A = mul(A, B);
        for (int j = 1; j <= num[i]; j++) {
            F[i][j] = (LL)A[j + num[i]] * inv[j] % mod * inv[j - 1] % mod;
            if (j & 1) F[i][j] = mod - F[i][j];
        }
    }
    // for (int i = 1; i <= n; i++, puts(""))
    //     for (auto t : F[i]) cout << t << ' ';
    vector<int> G = solve(2, n), tmp(num[1], 0);
    for (int i = 0; i < num[1]; i++) 
        tmp[i] = (LL)F[1][i + 1] * frac[i + 1] % mod * inv[i] % mod;
    int res = 0; tmp = mul(tmp, G);
    for (int i = 0; i < tmp.size(); i++) res = (res + (LL)tmp[i] * frac[i]) % mod;
    if (num[1] != 1) {
        tmp = vector<int>(num[1], 0);
        for (int i = 0; i + 1 < num[1]; i++)
            tmp[i] = (LL)F[1][i + 2] * frac[i + 2] % mod * inv[i] % mod;
        tmp = mul(tmp, G);
        for (int i = 0; i < tmp.size(); i++) res = (res - (LL)tmp[i] * frac[i] % mod + mod) % mod;
    }
    res = (LL)res * m % mod;
    printf("%d\n", res);
    return 0;
}
