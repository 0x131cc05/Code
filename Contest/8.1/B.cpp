#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int k, n, frac[16], inv[16];

int A(int n, int r) {
    assert(r <= n && r >= 0);
    return (LL)frac[n] * inv[n - r] % mod;
}

int solve(int mn, vector<int> t) {
    if (n < mn) return A(k, n); 
    int res = A(k, mn);
    for (int i = 0, l = mn + 1; i < t.size(); i++) {
        int r = l + t[i] - 1, tmp = floor((n - r) / (double)k);
        int w = ((i + 1) == t.size()) ? frac[r - l + 1] : A(k - mn - (l - mn - 1), r - l + 1);
        if (tmp >= 0) res = (LL)res * w % mod * Pow(frac[r - l + 1], tmp) % mod;
        if (l + (tmp + 1) * k <= n) {
            int remain = n - l - (tmp + 1) * k + 1;
            if (tmp < 0) res = (LL)res * ((i + 1) == t.size() ? A(r - l + 1, remain) : A(k - mn - (l - mn - 1), remain)) % mod;
            else res = (LL)res * A(r - l + 1, remain) % mod;
        }
        l = r + 1;
    }
    return res;
}

vector<int> tp;

int res = 0;

void dfs(int nw) {
    if (nw == k) {
        int w = 0, tmp = tp.back(); 
        for (int i = 1; i <= tmp; i++)  
            w = (w + solve(i, tp)) % mod;
        if (tp.size() & 1) res = (res + w) % mod;
        else res = (res + mod - w) % mod;
        return;
    } 
    for (int i = 1; i <= k - nw; i++)
        tp.push_back(i), dfs(nw + i), tp.pop_back();
}

int main() {
    int T; scanf("%d", &T), frac[0] = inv[0] = 1;
    for (int i = 1; i <= 15; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    while (T--) {
        scanf("%d%d", &n, &k), res = 0;
        dfs(0), printf("%d\n", res);
    }
}
