#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
typedef pair<int, int> P;
 
const int N = 510;
 
struct WEN {
    LL l, r, k, b;
};
 
double inter(WEN a, WEN b) {
    if (a.k == b.k) return 1e18;
    return (double)(b.b - a.b) / (a.k - b.k);
}
 
vector<WEN> wkr[N];
 
int n, m; vector<int> v[N];
 
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1, a; j <= m; j++)
            scanf("%d", &a), v[i].push_back(a);
        sort(v[i].begin(), v[i].end());
        int lst = 1, ct = m; LL sum = 0;
        for (auto t : v[i]) {
            if (lst < t) wkr[i].push_back((WEN){ lst, t, ct, sum });
            ct--, sum += t, lst = t;
        }
        wkr[i].push_back((WEN){ lst, (LL)1e10, 0, sum });
        // for (auto t : wkr[i]) cout << t.l << ' ' << t.r << ' ' << t.k << ' ' << t.b << endl;
    }
    for (int i = 1; i <= n; i++) {
        vector<int> pos(n + 1); int res = n;
        for (auto t : wkr[i]) {
            int base = 0, remain = 0; vector<P> fuck;
            for (int j = 1; j <= n; j++) if (i != j) {
                LL l = 0, r = (int)wkr[j].size() - 1, mid, p0 = -1, p1 = -1, k = t.k, b = t.b;
                while (l <= r) {
                    mid = (l + r) >> 1;
                    auto tmp = wkr[j][mid];
                    if (tmp.k < k) r = mid - 1;
                    else {
                        if (tmp.r * k + b >= tmp.b + tmp.r * tmp.k) l = mid + 1;
                        else p0 = mid, r = mid - 1;
                    }
                }
                if (p0 == -1) { base++; continue; }
                l = p0 + 1, r = (int)wkr[j].size() - 1;
                while (l <= r) {
                    mid = (l + r) >> 1;
                    auto tmp = wkr[j][mid];
                    if (tmp.l * k + b < tmp.b + tmp.l * tmp.k) p1 = mid, l = mid + 1;
                    else r = mid - 1;
                }
                LL L = ceil(inter(t, wkr[j][p0]) + 1e-5), R = floor(p1 == -1 ? 1e18 : inter(t, wkr[j][p1]) - 1e-5);
                L = max(L, t.l), R = min(R, t.r);
                if (R > 2e10) R = 2e10;
                if (L > R) base++;
                else {
                    remain++;
                    fuck.push_back(P(L, 1)), fuck.push_back(P(R + 1, -1));
                }
            }
            sort(fuck.begin(), fuck.end());
            for (int i = 0, tp = 0; i < fuck.size(); ) {
                int j = i;
                while (j < fuck.size() && fuck[j].first == fuck[i].first) tp += fuck[j].second, j++;
                res = min(res, base + remain - tp + 1), i = j;
            }
        }
        printf("%d\n", res);
    }
}