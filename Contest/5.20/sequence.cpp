#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
const int mod = 1e9 + 7;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int y[N], flag[N], prime[N], tot;

inline void sieve(int n, int k) {
    y[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!flag[i]) y[i] = Pow(i, k);
        for (int j = 1; j <= tot && i * prime[j] <= n; j++) {
            flag[i * prime[j]] = 1, y[i * prime[j]] = (LL)y[i] * y[prime[j]] % mod;
            if (i % prime[j] == 0) break;
        }
    }
}

int frac[N], inv[N], k;

inline void pre() {
    sieve(k + 1, k), frac[0] = inv[0] = 1;
    for (int i = 1; i <= k + 1; i++) y[i] = (y[i - 1] + y[i]) % mod;
    for (int i = 1; i <= k + 1; i++) frac[i] = (LL)frac[i - 1] * i % mod;
    inv[k + 1] = Pow(frac[k + 1], mod - 2);
    for (int i = k; i >= 1; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % mod;
}

inline int Lerp(int n) {
    if (n <= k + 1) return y[n];
    static int pre[N], suf[N]; pre[0] = n, suf[k + 1] = n - (k + 1);
    for (int i = 1; i <= k + 1; i++) pre[i] = (LL)pre[i - 1] * (n - i) % mod;
    for (int i = k; i >= 0; i--) suf[i] = (LL)suf[i + 1] * (n - i) % mod;
    int res = 0;
    for (int i = 0; i <= k + 1; i++) {
        int tp = y[i];
        if (i) tp = (LL)tp * pre[i - 1] % mod;
        if (i != k + 1) tp = (LL)tp * suf[i + 1] % mod;
        tp = (LL)tp * inv[i] % mod * inv[k + 1 - i] % mod;
        if ((k + 1 - i) & 1) tp = mod - tp;
        res = (res + tp) % mod;
    }
    return res;
}

int tmp[N], p, q, ls[N];

inline bool fill(int pos, int x, int lim, int lst = 0) {
    tmp[pos] = x; int sum = x;
    for (int i = lst; i > pos; i--) sum += (tmp[i] = ls[i]);
    if (sum > lim) return false;
    for (int i = pos - 1; i >= 1; i--) {
        LL fuck = ((LL)tmp[i + 1] * p + q - 1) / q;
        if (fuck > lim || (sum += fuck) > lim) return false;
        tmp[i] = fuck;
    }
    return true;
}

int main() {
//    freopen("sequence.in", "r", stdin), freopen("sequence.out", "w", stdout);
    int T; scanf("%d", &T);
    while (T--) {
        int n; scanf("%d%d%d%d", &n, &k, &p, &q);
        if (p <= q) { pre(), printf("%d\n", Lerp(n)); continue; }
        if ((double)p / q <= 1.00001 + 1e-8) {
            int len = 1;
            while ((len + 1) * (len + 2) / 2 <= n) len++;
            n = n - len * (len + 1) / 2; int res = 0;
            for (int i = 1; i <= len; i++) {
                int nw = len - i + 1;
                if (i <= n) nw++;
                res = (res + (LL)nw * Pow(i, k)) % mod;
            }
            printf("%d\n", res);
        } else {
            int l = 1, r = sqrt(n * 2 + 0.5), mid, len;
            while (l <= r) {
                mid = (l + r) >> 1;
                if (fill(mid, 1, n)) len = mid, l = mid + 1;
                else r = mid - 1;
            }
            fill(len, 1, n); int pos = len;
            while (pos) {
                for (int i = 1; i <= pos; i++) ls[i] = tmp[i];
                l = 1, r = pos; int ans = -1;
                while (l <= r) {
                    mid = (l + r) >> 1;
                    if (fill(mid, ls[mid] + 1, n, pos)) ans = mid, l = mid + 1;
                    else r = mid - 1;
                }
                if (ans == -1) break;
                l = 1, r = n; int diff = 1;
                while (l <= r) {
                    mid = (l + r) >> 1;
                    if (fill(ans, ls[ans] + mid, n, pos)) diff = mid, l = mid + 1;
                    else r = mid - 1;
                }
                fill(ans, ls[ans] + diff, n, pos);
                for (int i = pos; i > ans; i--) n -= ls[i];
                pos = ans;
            }
            int res = 0; 
            for (int i = 1; i <= len; i++) 
                res = (res + (LL)ls[i] * Pow(i, k)) % mod;
            printf("%d\n", res);
        }
    }
}
