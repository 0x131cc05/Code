#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 100010;

struct WEN {

int val, pos, type;

bool operator < (const WEN &b) {
    return val < b.val;
}

} num[N * 2];

LL pre[N * 2]; int pos[2][N]; 

int main() {
    int n, tp = 0; scanf("%d", &n); LL A = 0, B = 0;
    for (int i = 1; i <= n; i++) {
        int a, b; scanf("%d%d", &a, &b), A += a, B += b;
        num[++tp] = (WEN){ a, i, 0 }, num[++tp] = (WEN){ b, i, 1 };
    }
    sort(num + 1, num + tp + 1);
    for (int i = 1; i <= tp; i++) {
        pre[i] = pre[i - 1] + num[i].val;
        pos[num[i].type][num[i].pos] = i;
    }
    LL res = 1e18;
    for (int i = 1; i <= n; i++) {
        int a = pos[0][i], b = pos[1][i];
        if (a > b) swap(a, b);
        if (b <= n) { res = pre[n]; break; }
        if (a < n) res = min(res, pre[n - 1] + num[b].val);
        else res = min(res, pre[n - 2] + num[a].val + num[b].val);
    }
    printf("%lld\n", min(res, min(A, B)));
}
