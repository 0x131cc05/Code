#include <bits/stdc++.h>
using namespace std;

const int N = 510;
const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int res[N];

int len, mx, frac[N * N], inv[N * N], inv1[N];

int C(int n, int r) {
    if (r < 0 || n < r) return 0;
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

void merge(int a[], int b[]) {
    static int c[N]; 
    for (int i = 0; i <= mx; i++) c[i] = 0;
    for (int i = 0; i <= mx; i++)
        for (int j = 0; j <= mx - i; j++) c[i + j] = (c[i + j] + (LL)a[i] * b[j]) % mod;
    for (int i = 0; i <= mx; i++) a[i] = c[i];
}

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

void solve(LL n, LL lim) {
    if (lim <= 500) {
        for (int j = 0; j <= mx; j++) res[j] = 0;
        for (int i = 1; i <= lim; i++) {
            int remain = n - i * len;
            for (int j = 0; j <= mx; j++) 
                Inc(res[j], C(remain, j));
        }
        return;
    }
    auto process = [&](int a[], int t) {
        for (int j = 0, cur = 1; j <= mx; j++, cur = (LL)cur * (t - j + 1) % mod * inv1[j] % mod) 
            a[j] = cur < 0 ? cur + mod : cur;
    };
    if (lim & 1) {
        solve(n - len, lim - 1);
        int t = (n - len) % mod;
        static int tmp[N];
        process(tmp, t);
        for (int i = 0; i <= mx; i++) Inc(res[i], tmp[i]);
        return;
    }
    solve(n - len * (lim / 2), lim / 2);
    static int tmp[N];
    int t = len * ((lim / 2) % mod) % mod;
    process(tmp, t);
    merge(tmp, res);
    for (int i = 0; i <= mx; i++)
        Inc(res[i], tmp[i]);
}

int main() {
    LL n; int m; cin >> n >> m, frac[0] = inv[0] = 1;
    for (int i = 1; i <= 500 * 500; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 1; i <= m; i++) inv1[i] = Pow(i, mod - 2);
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        int w = C(m, i);
        if (!(i & 1)) w = mod - w;
        if (i == m) {
            if (n % m == 0) ans = (ans + w) % mod;
            continue;
        }
        len = i, mx = m - i - 1;
        // cout << (n - 1) / i << endl;
        solve(n - 1, (n - 1) / i);
        ans = (ans + (LL)w * res[mx]) % mod;
    }
    printf("%d\n", ans);
}
