#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
const int mod = 998244353;

typedef long long LL;

LL num[N]; int stk[N], top, ans[N];

inline LL Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline bool check(int a, int b, int c) {
    LL x1 = b - a, x2 = c - a, y1 = num[b] - num[a], y2 = num[c] - num[a];
    return (LL)x1 * y2 - (LL)y1 * x2 >= 0;
}

inline int calc(int len) {
    return (LL)len * (len + 1) / 2 % mod;
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &num[i]);
    for (int i = 1; i <= n; i++) {
        while (top >= 2 && check(stk[top - 1], stk[top], i)) top--;
        int l = stk[top], r = i, step = (LL)(num[r] - num[l]) % mod * Pow(r - l, mod - 2) % mod;
        ans[i] = (ans[l] + (LL)calc(r - l) * step + (LL)(r - l) * num[l]) % mod;
        ans[i] = (ans[i] + mod) % mod, stk[++top] = i;
        printf("%d ", (LL)ans[i] * Pow(i, mod - 2) % mod);
    }
}
