#include <bits/stdc++.h>
using namespace std;

const int N = 3010;

typedef long long LL;

struct WEN {

int x, y;

bool operator < (WEN &b) {
    if (x != b.x) return x < b.x;
    return y < b.y;
}

} p[N];

int nxt[N], lst[N], ans[N], k, R, C, n; set<int> s;

inline int Add(int t) {
    auto hh = s.lower_bound(t);
    int b = *hh, a = *(--hh);
    nxt[a] = t, lst[t] = a, nxt[t] = b, lst[b] = t;
    int cur = t;
    for (int i = 1; i < k; i++) if (lst[cur]) cur = lst[cur];
    int r = cur, ct = 1; LL res = 0;
    while (233) {
        while (nxt[r] <= n && ct < k) r = nxt[r], ct++;
        // cout << "check:" << cur << ' ' << r << ' ' << ct << endl;
        if (ct < k) break;
        res -= ans[cur], ans[cur] = (LL)(p[cur].x - p[lst[cur]].x) * (R - p[r].x + 1), res += ans[cur];
        if (p[t] < p[cur] || nxt[cur] > n) break;
        cur = nxt[cur], ct--;
    }
    s.insert(t);
    return res;
}

vector<int> wkr[N];

int main() {
    scanf("%d%d%d%d", &R, &C, &n, &k);
    for (int i = 1; i <= n; i++) 
        scanf("%d%d", &p[i].x, &p[i].y);
    sort(p + 1, p + n + 1);
    for (int i = 1; i <= n; i++) wkr[p[i].y].push_back(i);
    LL res = 0;
    for (int i = 1; i <= C; i++) {
        memset(lst, 0, sizeof(lst)), memset(nxt, 0, sizeof(nxt)), memset(ans, 0, sizeof(ans)), s.clear(); LL ans = 0;
        s.insert(0), s.insert(n + 1);
        for (int j = i; j <= C; j++) {
            for (auto t : wkr[j]) ans += Add(t);
            res += ans;
            // cout << i << ' ' << j << ' ' << ans << endl;
        }
    }
    printf("%lld\n", res);
    return 0;
}