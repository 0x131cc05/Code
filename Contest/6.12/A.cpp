#include <bits/stdc++.h>
using namespace std;

const int N = 50010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N * 6];

inline void GetR(int len, int l) {
    for (int i = 1; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
}

inline int Sub(int a, int b) {
    a -= b; return a < 0 ? a + mod : a;
}

inline void Inc(int &a, int b) {
    a += b, a -= a >= mod ? mod : 0;
}

inline void NTT(vector<int> &a, int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0; i < len; i += mid)
            for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod)
                t = (LL)a[j + (mid >> 1)] * w % mod, a[j + (mid >> 1)] = Sub(a[j], t), Inc(a[j], t);
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

inline vector<int> mul(vector<int> a, vector<int> b) {
    int n = a.size() + b.size() - 2, len = 1, l = 0;
    while (len <= n) len <<= 1, l++;
    GetR(len, l), a.resize(len), b.resize(len);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = (LL)a[i] * b[i] % mod;
    NTT(a, len, 0);
    return a;
}

int wn1, wn2;

inline vector<int> bluestein(vector<int> a, int n) {
    int len = 1, l = 0;
    while (len <= n * 3) len <<= 1, l++;
    GetR(len, l), a.resize(len);
    for (int i = 0; i < n; i++) a[i] = (LL)a[i] * Pow(wn1, (LL)i * (i - 1) / 2 % (mod - 1)) % mod;
    vector<int> b(len, 0);
    for (int i = 0; i < n * 2 - 1; i++) b[2 * n - i] = Pow(wn2, (LL)i * (i - 1) / 2 % (mod - 1));
    b = mul(a, b);
    for (int i = 0; i < n; i++) a[i] = (LL)Pow(wn1, (LL)i * (i - 1) / 2 % (mod - 1)) * b[2 * n - i] % mod;
    return a.resize(n), a;
}

int ct[N], val[N];

typedef pair<int, int> P;

int main() {
    int n, m, x, e = 1; scanf("%d%d%d", &n, &m, &x); int tmp = x;
    while (x != 1) e++, x = (LL)x * tmp % mod;
    for (int i = 1, a; i <= n; i++) scanf("%d", &a), ct[a % e]++;
    wn1 = tmp, wn2 = Pow(tmp, mod - 2);
    for (int i = 0; i < e; i++) val[i] = 1;
    for (int i = 0; i < e; i++) if (ct[i]) {
        int t = Pow(wn1, i);
        for (int j = 0, w = 1; j < e; j++, w = (LL)w * t % mod) 
            val[j] = (LL)val[j] * Pow(1 + w, ct[i]) % mod;
    }
    vector<int> wkr;
    for (int i = 0; i < e; i++) wkr.push_back(val[i]);
    for (int i = 0; i < e; i++) wkr[i] = Pow(wkr[i], m);
    wkr = bluestein(wkr, e);
    vector<P> ans; int inv = Pow(e, mod - 2);
    for (int i = 0; i < e; i++) if (wkr[i]) {
        ans.push_back(P(Pow(tmp, i), (LL)wkr[i] * inv % mod));
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}
