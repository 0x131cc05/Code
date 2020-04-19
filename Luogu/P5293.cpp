#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

const double PI = acos(-1);

typedef long long LL;

struct Num {
    double x, y;
    Num() {}
    Num(double _x, double _y) : x(_x), y(_y) {}
    Num operator+(const Num& rhs) const { return Num(x + rhs.x, y + rhs.y); }
    Num operator-(const Num& rhs) const { return Num(x - rhs.x, y - rhs.y); }
    Num operator*(const Num& rhs) const { return Num(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
    Num Conj(void) { return Num(x, -y); }
    void operator=(const double& rhs) { x = rhs, y = 0; }
} WN[N << 2];

int r[N << 2];

void FFT(Num* f, int n, int flag) {
    static Num x, y;
    for (int i = 1; i < n; ++i)
        if (i < r[i])
            swap(f[i], f[r[i]]);
    for (int mid = 1, l = 0; mid < n; mid <<= 1, ++l) {
        for (int i = 0; i < n; i += (mid << 1)) {
            for (int j = 0; j < mid; ++j) {
                x = f[i + j], y = f[i + j + mid] * (flag == 1 ? WN[(n >> l) * j] : WN[(n >> l) * j].Conj());
                f[i + j] = x + y;
                f[i + j + mid] = x - y;
            }
        }
    }
    if (flag == -1) {
        for (int i = 0; i < n; ++i) f[i].x /= n, f[i].y /= n;
    }
}

int mod;

void MTT(int* f, int* g, int* h, int n, int m, int k = -1) {
    static Num A[N << 2], B[N << 2], C[N << 2], D[N << 2];
    static Num a, b, c, d;
    static LL s1, s2, s3, s4;
    if (!~k) k = n + m;
    int lim = 1, l = -1;
    while (lim <= n + m) lim <<= 1, ++l;
    for (int i = 1; i < lim; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l);
    for (int i = 0; i < lim; ++i) WN[i] = Num(cos(PI * i / lim), sin(PI * i / lim));
    for (int i = 0; i <= n; ++i) A[i] = Num(f[i] & 32767, f[i] >> 15);
    for (int i = 0; i <= m; ++i) B[i] = Num(g[i] & 32767, g[i] >> 15);
    for (int i = n + 1; i < lim; ++i) A[i] = 0;
    for (int i = m + 1; i < lim; ++i) B[i] = 0;
    FFT(A, lim, 1), FFT(B, lim, 1);
    for (int i = 0, j; i < lim; ++i) {
        j = (lim - i) & (lim - 1);
        a = (A[i] + A[j].Conj()) * Num(0.5, 0);
        b = (A[i] - A[j].Conj()) * Num(0, -0.5);
        c = (B[i] + B[j].Conj()) * Num(0.5, 0);
        d = (B[i] - B[j].Conj()) * Num(0, -0.5);
        C[i] = a * c + a * d * Num(0, 1);
        D[i] = b * c + b * d * Num(0, 1);
    }
    FFT(C, lim, -1), FFT(D, lim, -1);
    for (int i = 0; i <= k; ++i) {
        s1 = ((LL)(C[i].x + 0.5)) % mod;
        s2 = ((LL)(C[i].y + 0.5)) % mod;
        s3 = ((LL)(D[i].x + 0.5)) % mod;
        s4 = ((LL)(D[i].y + 0.5)) % mod;
        h[i] = (s1 + ((s2 + s3) << 15) + (s4 << 30)) % mod;
    }
}

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline int GetG() {
    vector<int> tmp;
    for (int i = 2; i <= (mod - 1) / i; i++) if ((mod - 1) % i == 0) {
        tmp.push_back(i);
        if (i != (mod - 1) / i) tmp.push_back((mod - 1) / i);
    }
    for (int i = 2; ; i++) {
        bool flag = true;
        for (auto t : tmp) if (Pow(i, t) == 1) {
            flag = false; break;
        }
        if (flag) return i;
    }
}

int n;

struct Matrix {

int A[3][3];

Matrix() { memset(A, 0, sizeof(A)); }

int* operator [] (int i) { return A[i]; }

Matrix operator * (Matrix &b) {
    Matrix res;
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                res[i][j] = (res[i][j] + (LL)A[i][k] * b[k][j]) % mod;
    return res;
}

Matrix operator * (int x) {
    Matrix res;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) res[i][j] = (LL)A[i][j] * x % mod;
    return res;
}

Matrix operator + (Matrix &b) {
    Matrix res;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) res[i][j] = (A[i][j] + b[i][j]) % mod;
    return res;
}

} E, W;

inline Matrix Pow(Matrix x, int y) {
    Matrix res = E;
    for (; y; y >>= 1, x = x * x) if (y & 1) res = res * x;
    return res;
}

int k;

inline int C2(int n) {
    return (LL)n * (n - 1) / 2 % k;
}

int A[N << 2], B[N << 2], H[N << 2];

int main() {
//    freopen("fuck.out", "w", stdout);
    int l, x, y; cin >> n >> k >> l >> x >> y >> mod;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) 
            cin >>  W[i][j];
    for (int i = 0; i < n; i++) E[i][i] = 1;
    int Wk = Pow(GetG(), (mod - 1) / k);
    for (int i = 0, w = 1; i < k; i++, w = (LL)w * Wk % mod) {
        Matrix base = Pow(W * w + E, l);
        A[i] = (LL)base[x - 1][y - 1] * Pow(Wk, C2(i)) % mod;
    }
    for (int i = 0; i <= k * 2; i++) 
        B[k * 2 - i] = Pow(Wk, k - C2(i));
//     for (int i = 0; i <= 2 * k; i++) cout << A[i] << ' ';
//     cout << endl;
//     for (int i = 0; i <= 2 * k; i++) cout << B[i] << ' ';
//     cout << endl;
    MTT(A, B, H, k, k * 2); 
    for (int i = 0, inv = Pow(k, mod - 2); i < k; i++) {
        int t = (LL)Pow(Wk, C2(i)) * inv % mod * H[2 * k - i] % mod;
        printf("%d\n", t);
    }
    return 0;
}
