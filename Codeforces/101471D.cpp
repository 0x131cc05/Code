#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

typedef pair<int, int> P;
typedef long long LL;

P A[N], B[N];

LL calc(int a, int b) {
    return (LL)(B[b].first - A[a].first) * (B[b].second - A[a].second);
}

LL res = 0;

void solve(int l, int r, int l1, int r1) {
    if (l1 > r1 || l > r) return;
    int mid = (l1 + r1) >> 1, pos = l - 1; LL tmp = -1e18;
    for (int i = l; i <= r; i++) if (A[i].first <= B[mid].first) {
        LL hh = calc(i, mid);
        if (hh > tmp) tmp = hh, pos = i;
    }
    res = max(res, tmp);
    solve(l, pos, l1, mid - 1), solve(max(pos, l), r, mid + 1, r1);
}

int main() {
    int m, n; scanf("%d%d", &m, &n);
    for (int i = 1, a, b; i <= m; i++) scanf("%d%d", &a, &b), A[i] = P(b, a);
    for (int i = 1, a, b; i <= n; i++) scanf("%d%d", &a, &b), B[i] = P(b, a);
    sort(A + 1, A + m + 1), sort(B + 1, B + n + 1, [](P a, P b) {
        return a.first != b.first ? a.first > b.first : a.second > b.second;
    });
    int ct1 = 0, ct2 = 0;
    for (int i = 1; i <= m; i++) if (A[i].second < A[ct1].second || !ct1) 
        A[++ct1] = A[i];
    for (int i = 1; i <= n; i++) if (B[i].second > B[ct2].second) 
        B[++ct2] = B[i];
    reverse(B + 1, B + ct2 + 1);
    solve(1, ct1, 1, ct2), printf("%lld\n", res);
}