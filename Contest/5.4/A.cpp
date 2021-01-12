#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

typedef long long LL;

int x[N], y[N], sa[N], rk[N], height[N], c[N], m, n;

inline void sort() {
    for (int i = 1; i <= m; i++) c[i] = 0;
    for (int i = 1; i <= n; i++) c[x[i]]++;
    for (int i = 1; i <= m; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
}

inline void SA(int s[]) {
    for (int i = 1; i <= n; i++) x[i] = s[i], y[i] = i;
    m = n, sort();
    for (int k = 1, num = 0; k < n; k <<= 1, num = 0) {
        for (int i = n; i >= n - k + 1; i--) y[++num] = i;
        for (int i = 1; i <= n; i++) if (sa[i] > k) y[++num] = sa[i] - k;
        sort(), memcpy(y, x, sizeof(x)), num = x[sa[1]] = 1;
        for (int i = 2; i <= n; i++)
            x[sa[i]] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? num : ++num;
        m = num; if (num == n) break;
    }
}

inline void build(int num[]) {
    for (int i = 1; i <= n; i++) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i++) if (rk[i] != 1) {
        if (k) k--; int at = sa[rk[i] - 1];
        while (at + k <= n && i + k <= n && num[i + k] == num[at + k]) k++;
        height[rk[i]] = k;
    }
}

LL pre[N]; int val[N], top; vector<LL> fuck[N];

int sum[N * 30], ls[N * 30], rs[N * 30], ncnt;

void update(int &rt, LL l, LL r, LL x) {
    if (!rt) rt = ++ncnt;
    sum[rt]++;
    if (l == r) return;
    LL mid = (l + r) >> 1;
    if (x <= mid) update(ls[rt], l, mid, x);
    else update(rs[rt], mid + 1, r, x);
}

int query(int rt, LL l, LL r, LL start, LL end) {
    if (!rt) return 0;
    if (start <= l && r <= end) return sum[rt];
    LL mid = (l + r) >> 1; int res = 0;
    if (start <= mid) res += query(ls[rt], l, mid, start, end);
    if (end > mid) res += query(rs[rt], mid + 1, r, start, end);
    return res;
}

int num[N];

int main() {
    LL L, R, down = 1e18, up = -1e18; scanf("%d%lld%lld", &n, &L, &R);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &num[i]), pre[i] = pre[i - 1] + num[i];
        val[++top] = num[i], down = min(down, pre[i]), up = max(up, pre[i]);
    }
    sort(val + 1, val + top + 1), top = unique(val + 1, val + top + 1) - val - 1;
    for (int i = 1; i <= n; i++) num[i] = lower_bound(val + 1, val + top + 1, num[i]) - val;
    SA(num), build(num);
    for (int i = 1; i <= n; i++) 
        fuck[i + height[rk[i]]].push_back(pre[i - 1]);
    int rt = 0; LL res = 0;
    for (int i = n; i >= 1; i--) {
        update(rt, down, up, pre[i]); 
        for (auto t : fuck[i]) res += query(rt, down, up, L + t, R + t);
    }
    printf("%lld\n", res);
}
