#include <bits/stdc++.h>
using namespace std;

const int N = 40010;
const int mod = 1e9 + 7;

typedef long long LL;

int Pow(int x, int y, int mod = ::mod) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int frac[N], inv[N];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod; 
}

const int m1 = 998244353, m2 = 1004535809, m3 = 469762049;
const LL _fuck = (LL)m1 * m2;
const int inv1 = Pow(m1, m2 - 2, m2), inv2 = Pow(_fuck % m3, m3 - 2, m3);
struct mint {
    int A, B, C;
    mint(int A, int B, int C): A(A), B(B), C(C) { }
    mint(int x = 0): A(x), B(x), C(x) { }
    mint reduce() { return mint(A + (A >> 31 & m1), B + (B >> 31 & m2), C + (C >> 31 & m3)); }
    mint operator + (const mint &b) const { return mint(A + b.A - m1, B + b.B - m2, C + b.C - m3).reduce(); }
    mint operator - (const mint &b) const { return mint(A - b.A, B - b.B, C - b.C).reduce(); }
    mint operator * (const mint &b) const { return mint((LL)A * b.A % m1, (LL)B * b.B % m2, (LL)C * b.C % m3); }
    int eval() {
        LL x = (LL)(B - A + m2) % m2 * inv1 % m2 * m1 + A;
		return ((LL)(C - x % m3 + m3) % m3 * inv2 % m3 * (_fuck % mod) % mod + x) % mod;
    }
};

mint w[2][N << 2]; int _all;

void init(int n) {
    int &len = _all = 1;     
    while (len <= n * 2) len <<= 1;
    w[0][0] = w[1][0] = 1;
    w[1][1] = mint(Pow(3, (m1 - 1) / len, m1), Pow(3, (m2 - 1) / len, m2), Pow(3, (m3 - 1) / len, m3));
    w[0][1] = mint(Pow(w[1][1].A, m1 - 2, m1), Pow(w[1][1].B, m2 - 2, m2), Pow(w[1][1].C, m3 - 2, m3));
    for (int i = 2; i < len; i++) 
        w[0][i] = w[0][i - 1] * w[0][1], w[1][i] = w[1][i - 1] * w[1][1];
}

int r[N << 2];

void getR(int len, int l) {
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
}

void NTT(vector<mint> &a, int type) {
    int len = a.size();
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2, step = 1; mid <= len; mid <<= 1, step++) 
        for (int i = 0; i < len; i += mid) {
            int cur = 0, tmp = _all >> step;
            for (int j = i; j < i + (mid >> 1); j++, cur += tmp) {
                mint t = a[j + (mid >> 1)] * w[type][cur];
                a[j + (mid >> 1)] = a[j] - t, a[j] = a[j] + t;
            } 
        }
    if (!type) {
        mint inv(Pow(len, m1 - 2, m1), Pow(len, m2 - 2, m2), Pow(len, m3 - 2, m3));
        for (int i = 0; i < len; i++) a[i] = a[i] * inv;
    }
}

int k;

vector<int> Mul(vector<int> A, vector<int> B) {
    vector<mint> A1, B1;
    for (auto t : A) A1.push_back(t);
    for (auto t : B) B1.push_back(t);
    int len = 1, l = 0;
    while (len <= k * 2) len <<= 1, l++;
    getR(len, l), A1.resize(len), B1.resize(len);
    NTT(A1, 1), NTT(B1, 1);
    for (int i = 0; i < len; i++) A1[i] = A1[i] * B1[i];
    NTT(A1, 0);
    int inv = Pow(len, mod - 2);
    vector<int> res;
    for (int i = 0; i <= k; i++) 
        res.push_back(A1[i].eval());
    return res;
}

