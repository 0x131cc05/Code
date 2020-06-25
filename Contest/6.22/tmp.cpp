#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 998244353;

typedef long long LL;

int num[N], n;

inline bool check(LL x, int t) {
    LL ls = 0, tot = 0;
    for (int i = 1; i <= n; i++) {
        ls = max(ls, 0ll) + num[i];
        if (ls > x) tot += ls - x, ls = x;
        if (tot > t) return false;
    }
    return true;
}

int main() {
    scanf("%d", &n); LL wkr = 0, ans = -1e18;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &num[i]);
        wkr = max(0ll, wkr) + num[i];
        ans = max(ans, wkr);
    }
    int k; scanf("%d", &k); int res = 0;
    for (int i = 1; i <= k; i++) {
        if (check(ans - 1, i)) ans--;
        res = (res + ans) % mod;
    }
    printf("%d\n", (res + mod) % mod);
}
