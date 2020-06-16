#include <bits/stdc++.h>
using namespace std;

const int N = 300010;

typedef long long LL;

int num[N], n; LL ans = 1e18;

inline LL solve(int a, int b) {
    static int tmp[6];
    tmp[0] = a, tmp[1] = b;
    for (int i = 2; i < 6; i++) tmp[i] = tmp[i - 1] - tmp[i - 2];
    LL res = 0;
    for (int i = 1; i <= n; i++) 
        res += abs((LL)num[i] - tmp[(i - 1) % 6]);
    ans = min(ans, res);
    return res;
}

inline LL solve(int a) {
    int l = -1e9, r = 1e9; LL t = 1e18;
    while (l <= r) {
        int mid = (l + r) >> 1, mid1 = mid + 1;
        LL A = solve(a, mid), B = solve(a, mid1);
        t = min(t, min(A, B));
        if (A == B) break;
        if (A < B) r = mid - 1;
        else l = mid1 + 1;
    }
    return t;
}

int main() {
//    freopen("lsj.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    int l1 = -1e9, r1 = 1e9;
    while (l1 <= r1) {
        int mid = (l1 + r1) >> 1, mid1 = mid + 1;
        LL A = solve(mid), B = solve(mid1);
        if (A == B) break;
        if (A < B) r1 = mid - 1;
        else l1 = mid1 + 1;
    }
    printf("%lld\n", ans);
}
