#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;
const int mod = 1e9 + 7;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int frac[N], inv[N];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

void FUCK() {
    puts("0"), exit(0);
}

struct wen {
    LL x, y, w, k;
    bool operator < (const wen &b) const {
        return w < b.w;
    }
} wkr[N];

int n, l;

int solve() {
    LL mn = 0, mx = l;
    for (int i = 1; i <= n; i++) {
        LL delta = wkr[i].x - wkr[i - 1].x, period = wkr[i].k - wkr[i - 1].k, zjk = wkr[i].w - wkr[i - 1].w;
        if (period == 0) {
            if (delta < 0 || delta > zjk) FUCK();
        } else if (period > 0) {
            mn = max(mn, (delta - zjk + period - 1) / period);
            mx = min(mx, delta / period);
        } else {
            period = -period;
            mn = max(mn, (-delta + period - 1) / period);
            mx = min(mx, (-delta + zjk) / period);
        }
        // cout << "fuck: " << mn << ' ' << mx << ' ' << period << endl;
        if (mn > mx) FUCK();
    }  
    int res = 0;
    for (int i = mn; i <= mx; i++) {
        int t = 1;
        for (int j = 1; j <= n; j++) 
            t = (LL)t * C(wkr[j].w - wkr[j - 1].w, wkr[j].x - wkr[j].k * i - wkr[j - 1].x + wkr[j - 1].k * i) % mod;
        res = (res + t) % mod;
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &l), frac[0] = inv[0] = 1;
    for (int i = 1; i <= l; i++) frac[i] = (LL)frac[i - 1] * i % mod;
    inv[l] = Pow(frac[l], mod - 2);
    for (int i = l - 1; i >= 1; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % mod;
    for (int i = 1; i <= n; i++) {
        LL t, x, y; scanf("%lld%lld%lld", &t, &x, &y);
        if ((t + x + y) & 1) FUCK();
        wkr[i] = (wen){ (t + x + y) / 2, (t - x + y) / 2, t % l, t / l };
        // cout << wkr[i].x << ' ' << wkr[i].y << endl;
    }
    wkr[++n] = (wen){ 0, 0, l, -1 }; // 在周期结束时必须走了当前枚举的那么多步
    sort(wkr + 1, wkr + n + 1);
    int a = solve();
    for (int i = 1; i <= n; i++) swap(wkr[i].x, wkr[i].y);
    printf("%d\n", (LL)a * solve() % mod);
}