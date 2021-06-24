#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

int num[N], n, m, ans = 1e9;

inline bool check(int mid) {
    int res = 0;
    for (int i = 1; i <= mid; i++) res = max(res, num[i] + num[mid * 2 - i + 1]);
    for (int i = 1; i <= n - mid; i++) {
        int t = num[mid * 2 + i] + num[n * 2 - i + 1];
        if (t < m) return false;
        res = max(res, t - m);
    }
    ans = min(ans, res);
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n * 2; i++) scanf("%d", &num[i]);
    sort(num + 1, num + n * 2 + 1);
    int l = 0, r = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid - 1;
        else l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}