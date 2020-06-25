#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 998244353;

typedef long long LL;

int num[N], n;

inline LL count(LL x) {
    LL ls = 0, tot = 0;
    for (int i = 1; i <= n; i++) {
        ls = max(ls, 0ll) + num[i];
        if (ls > x) tot += ls - x, ls = x;
    }
    return tot;
}

inline LL calc(LL l, LL r) {
    LL A = r + l, B = r - l + 1;
    if (A % 2 == 0) A /= 2;
    else B /= 2;
    return (A % mod) * (B % mod) % mod;
}

int main() {
    scanf("%d", &n); LL wkr = 0, ans = -1e18;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &num[i]);
        wkr = max(0ll, wkr) + num[i];
        ans = max(ans, wkr);
    }
    LL k, tp = 1; scanf("%lld", &k); int res = 0;
    while (tp <= k) {
        LL nxt = min(k, count(ans - 1) - 1);
        if (tp > nxt) { tp = nxt + 1, ans--; continue; }
        LL l = 0, r = k - tp, mid, pos = 0;
        while (l <= r) {
            mid = (l + r) >> 1;
            LL hh = count(ans - mid);
            LL hh1 = count(ans - mid - 1);
            if (hh1 > k + 1) r = mid - 1;
            else {
                if (hh1 - hh == nxt - tp + 1) l = mid + 1, pos = mid;
                else r = mid - 1;
            }
        }
        LL step = nxt - tp + 1; nxt = min(k, count(ans - pos - 1) - 1);
        res = (res + calc(ans - pos, ans) * (step % mod)) % mod;
        tp = nxt + 1, ans = ans - pos - 1;
    }
    printf("%d\n", (res + mod) % mod);
}
