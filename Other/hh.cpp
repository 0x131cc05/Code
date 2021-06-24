#include <bits/stdc++.h>
using namespace std;

const int N = 48010;

typedef long long LL;

int mod;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int f[N], g[N], frac[N], inv[N], tmp[N];

int main() {
    int T; scanf("%d%d", &T, &mod); int n = 20;
    f[0] = 1, frac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 1; i < n; i++) {
        int lim = n / i;
        for (int j = 0; j <= n; j++) g[j] = f[j];
        if (i == 1) f[i]++;
        tmp[0] = f[i];
        for (int j = 1; j <= lim; j++) tmp[j] = (LL)tmp[j - 1] * (f[i] + j) % mod;
        for (int j = n; j > i; j--) {
            int lim = j / i;
            for (int k = 1; k <= lim; k++)
                f[j] = (f[j] + (LL)g[j - k * i] * tmp[k - 1] % mod * inv[k]) % mod;
        }
    }
    for (int i = 1; i <= n; i++) cout << f[i] << ' ';
    cout << endl;
    while (T--) {
        int n; scanf("%d", &n); printf("%d\n", f[n + 1]);
    }
}
