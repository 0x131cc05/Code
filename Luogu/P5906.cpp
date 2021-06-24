#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

int belong[N], num[N], appear[N], tp[N];

inline int solve(int l, int r) {
    int res = 0;
    for (int i = l; i <= r; i++) {
        if (appear[num[i]]) res = max(res, i - appear[num[i]]);
        else appear[num[i]] = i;
    }
    for (int i = l; i <= r; i++) appear[num[i]] = 0;
    return res;
}

int ans[N];

struct WEN {

int l, r, id;

bool operator < (const WEN &b) {
    return r < b.r;
}

};

vector<WEN> wkr[N]; int val[N], tot = 0;

int main() {
    int n, sz; scanf("%d", &n), sz = ceil(sqrt(n));
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]), belong[i] = (i + sz - 1) / sz, val[++tot] = num[i];
    sort(val + 1, val + tot + 1);
    for (int i = 1; i <= n; i++) num[i] = lower_bound(val + 1, val + tot + 1, num[i]) - val;
    int q; scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int l, r; scanf("%d%d", &l, &r);
        if (belong[l] == belong[r]) ans[i] = solve(l, r);
        else wkr[belong[l]].push_back((WEN){ l, r, i });
    }
    for (int i = 1; i <= belong[n]; i++) if (wkr[i].size()) {
        sort(wkr[i].begin(), wkr[i].end());
        memset(appear, 0, sizeof(appear)), memset(tp, 0, sizeof(tp)); 
        int pos = i * sz, res = 0;
        for (auto t : wkr[i]) {
            int l = t.l, r = t.r;
            while (pos + 1 <= r) {
                int t = num[pos + 1];
                if (tp[t]) res = max(res, pos + 1 - tp[t]); else tp[t] = pos + 1;
                appear[t] = pos + 1, pos++;
            }
            int ls = res;
            for (int j = i * sz; j >= l; j--) {
                if (appear[num[j]]) res = max(res, appear[num[j]] - j);
                else appear[num[j]] = j;
            }
            ans[t.id] = res, res = ls;
            for (int j = i * sz; j >= l; j--) if (appear[num[j]] <= i * sz) 
                appear[num[j]] = 0;
        }
    }
    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
}
