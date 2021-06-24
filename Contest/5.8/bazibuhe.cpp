#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef long long LL;

#define int LL

int a[N], n, m;

inline int calc(int l, int r, int d) {
    int t = (r - l) / d + 1;
    return (l + r) * t / 2;
}

inline bool check(int turn, int mid) {
    int last = m;
    int remain = last - turn * n, hh = 0;
    for (int i = n - 1, t = mid; i >= 1; i--) {
        t -= turn;
        if (t > a[i]) hh += t - a[i], t = a[i];
    }
    return remain >= hh;
}

inline LL solve(int turn) {
    int l = calc(n, n * turn, n), r = min(calc(m - n * (turn - 1), m, n), a[n]), mid, ans = -1;
    if (l > r) return 0;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (check(turn, mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    if (ans == -1) return 0;
    int res = ans, tp = ans, mn = calc(1, n * (turn - 1) + 1, n), flag = true;
    for (int i = n - 1; i >= 1; i--) {
        tp -= turn, tp = min(tp, a[i]), res += tp;
        if (tp < mn + (i - 1) * turn) {
            flag = false; break;
        }
    }
    if (!flag) return 0;
    return res;
}

signed main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    int l = 1, r = m / n, mid, ans = 0;
    while (l <= r) {
        mid = (l + r) >> 1;
        LL L = solve(mid), R = solve(mid + 1);
        if (L < R) ans = max(ans, R), l = mid + 2;
        else ans = max(ans, L), r = mid - 1;
    } 
    printf("%lld\n", ans);
}


