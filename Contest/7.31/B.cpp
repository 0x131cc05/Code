#include <bits/stdc++.h>
using namespace std;

const int N = 300010;

typedef long long LL;

int tree[N], n, num[N], x; LL dp[N];

void upd(int x, int y) { for (; x <= n; x += x & -x) tree[x] += y; }
int qry(int x) { int res = 0; for (; x; x -= x & -x) res += tree[x]; return res; }
int qry(int l, int r) { return qry(r) - qry(l - 1); }

LL move(int L, int R) {
    static int l = 1, r = 0; static LL res = 0;
    while (l > L) l--, res += qry(1, num[l]), upd(num[l], 1);
    while (r < R) r++, res += qry(num[r], n), upd(num[r], 1);
    while (l < L) upd(num[l], -1), res -= qry(1, num[l]), l++;
    while (r > R) upd(num[r], -1), res -= qry(num[r], n), r--;
    return res;
}

void CDQ(int l, int r, int tl, int tr) {
    if (l > r) return;
    int pos = l, mid = (l + r) >> 1; LL res = 1e18;
    for (int i = tl; i <= tr; i++) {
        LL t = move(i + 1, mid) + x + dp[i];
        if (t < res) res = t, pos = i;
    }
    dp[mid] = min(dp[mid], res), CDQ(l, mid - 1, tl, pos), CDQ(mid + 1, r, pos, tr);
}

void CDQ(int l, int r) {
    if (l >= r) return;
    int mid = (l + r) >> 1;
    CDQ(l, mid), CDQ(mid + 1, r, l, mid), CDQ(mid + 1, r);
}

int val[N];

int main() {
    freopen("T2.in", "r", stdin);
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]), val[i] = num[i];
    sort(val + 1, val + n + 1);
    for (int i = 1; i <= n; i++) num[i] = lower_bound(val + 1, val + n + 1, num[i]) - val;
    memset(dp, 0x3f, sizeof(dp)), dp[0] = 0, CDQ(0, n), printf("%lld\n", dp[n]);
}
