#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int inv2 = (mod + 1) / 2;
const int N = 200010;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int frac[N], inv[N], pw[N], pre[510][N], pre1[N], n;

int C(int n, int r) {
    if (r < 0 || r > n) return 0;
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int get(int l, int r, int k) {
    l = max(0, l);
    if (l > r) return 0;
    if (k <= 500) {
        int t = pre[k][r] + mod;
        if (l) t -= pre[k][l - 1];
        return (LL)t * pw[k + 1] % mod;
    }
    int res = 0;
    for (int i = l; i <= r; i++) 
        res = (res + (LL)C(i, n - k) * pw[i + k + 1]) % mod;
    return res;
}

int get1(int l, int r) {
    l = max(0, l);
    if (l > r) return 0;
    if (l == 0) return pre1[r];
    return (pre1[r] - pre1[l - 1] + mod) % mod;
}

int num[N];

int main() {
    int q; scanf("%d%d", &n, &q), frac[0] = inv[0] = pw[0] = 1;
    for (int i = 1; i <= 2 * n; i++) 
        frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2), pw[i] = (LL)pw[i - 1] * inv2 % mod;
    for (int t = 0; t <= min(n, 500); t++) {
        for (int i = n - t; i <= n * 2; i++) pre[t][i] = (pre[t][i - 1] + (LL)C(i, n - t) * pw[i]) % mod;
    }
    for (int i = n - 1; i <= n * 2; i++) pre1[i] = (pre1[i - 1] + (LL)C(i, n - 1) * pw[i]) % mod;
    for (int t = 1; t <= q; t++) {
        int k; scanf("%d", &k);
        for (int i = 1; i <= k; i++) scanf("%d", &num[i]);
        int ct = 0, res = (get(num[k] - k, n * 2 - 2 - k, k + 1) + (LL)C(num[k] - k, num[k] - n) * pw[num[k] + 1]) % mod;
        num[k + 1] = 2 * n, num[0] = -1;
        for (int i = k + 1; i >= 1; i--) {
            int l = num[i - 1] + 2, r = num[i], ct = k + 1 - i;
            if (l > r) continue;
            res = (res + (LL)get1(l - 2 - (k - ct), r - 2 - (k - ct)) * pw[2 + k - ct]) % mod;
        }
        res = (LL)res * 4 % mod;
        printf("%d\n", res);
    }
}