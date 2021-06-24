#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N << 2];

void NTT(vector<int> &a, int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0; i < len; i += mid)
            for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod) {
                t = (LL)w * a[j + (mid >> 1)] % mod;
                a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
            }
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

vector<int> mul(vector<int> a, vector<int> b) {
    if (!a.size() || !b.size()) return {};
    int len = 1, l = 0, n = (int)a.size() + b.size() - 2;
    while (len <= n) len <<= 1, l++;
    a.resize(len), b.resize(len);
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = (LL)a[i] * b[i] % mod;
    NTT(a, len, 0);
    a.resize(n + 1);
    return a;
}

int frac[N], inv[N];

vector<int> work1(vector<int> a, int n) { 
    int m = (int)a.size() - 1; vector<int> b(m + 1);
    if (n >= 0) for (int i = 0; i <= m; i++) 
        b[i] = (LL)frac[n + i] * inv[i] % mod * inv[n] % mod;
    else b[0] = 1;
    a = mul(a, b), a.resize(m + 1); 
    return a;
}

vector<int> work2(vector<int> a, int m) {
    if (!a.size()) return a.resize(m + 1), a;
    vector<int> b(a.size() + m + 1); int n = a.size();
    for (int i = 0; i < b.size(); i++) b[i] = frac[i];
    for (int i = 0; i < n; i++) a[i] = (LL)a[i] * inv[i] % mod;
    reverse(a.begin(), a.end()); 
    a = mul(a, b), b.resize(m + 1);
    for (int i = 0; i <= m; i++) b[i] = (LL)a[i + n - 1] * inv[i] % mod;
    return b;
}

vector<int> add(vector<int> a, vector<int> b) {
    assert(a.size() == b.size());
    vector<int> c;
    for (int i = 0; i < a.size(); i++)
        c.push_back((a[i] + b[i]) % mod);
    return c;
}

int num[N];
 
vector<int> solve(int l, int r, vector<int> &rgt) {
    if (l == r) {
        int all = 0;
        for (auto v : rgt) all = (all + v) % mod;
        return {all};
    }
    int mid = (l + r) >> 1;
    int up = num[r] - num[mid];
    auto tmp = rgt; tmp.resize(up);
    auto A = solve(mid + 1, r, tmp);
    vector<int> tmp1;
    for (int i = num[mid] - num[l - 1] - 1; i >= 0; i--) 
        tmp1.push_back(rgt[(int)rgt.size() - 1 - i]);
    auto L = add(work1(tmp1, r - mid - 1), work2(A, num[mid] - num[l - 1] - 1));
    reverse(tmp1.begin(), tmp1.end());
    auto hh = work2(tmp1, r - mid - 1);
    reverse(hh.begin(), hh.end());
    reverse(A.begin(), A.end());
    auto hh1 = work1(A, num[mid] - num[l - 1] - 1);
    reverse(hh1.begin(), hh1.end());
    auto D = add(hh1, hh);
    auto wkr = solve(l, mid, L);
    wkr.insert(wkr.end(), D.begin(), D.end());
    return wkr;
}

int main() {
    // freopen("sequence.in", "r", stdin), freopen("sequence.out", "w", stdout);
    frac[0] = inv[0] = 1;
    for (int i = 1; i <= N - 10; i++) frac[i] = (LL)frac[i - 1] * i % mod;
    inv[N - 10] = Pow(frac[N - 10], mod - 2);
    for (int i = N - 11; i >= 1; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % mod;
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) 
        scanf("%d", &num[i]), num[i]--;
    num[n + 1] = num[n], num[0] = -1;
    vector<int> base(num[n + 1] + 1); base[0] = 1;
    auto res = solve(1, n + 1, base);
    for (auto t : res) printf("%d ", t);
}