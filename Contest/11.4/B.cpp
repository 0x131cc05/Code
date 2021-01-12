#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

int x[N], w[N], ans[N], n, l, t;

int main() {
    scanf("%d%d%d", &n, &l, &t);
    for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &w[i]);
    bool flag = true;
    for (int i = 2; i <= n; i++) if (w[i] != w[1]) {
        flag = false; break;
    }
    if (flag) {
        for (int i = 1; i <= n; i++) {
            int p = w[i] == 1 ? (x[i] + t) % l : (x[i] - t) % l;
            printf("%d\n", (p + l) % l);
        }
    } else {
        int base = 0; vector<int> A, B;
        for (int i = 1; i <= n; i++) if (w[i] == 2) {
            base = i; break;
        }
        for (int i = 1; i <= n; i++) {
            if (w[i] == 1) A.push_back(x[i] < x[base] ? x[i] : x[i] - l);
            else B.push_back(x[i] < x[base] ? x[i] + l : x[i]); 
        }
        sort(A.rbegin(), A.rend()), sort(B.begin(), B.end());
        LL step = 0, res = (x[base] - t % l + l) % l, dir = 1;
        for (int i = 20; i >= 0; i--) {
            LL nxt = step | (1ll << i);
            LL a = (nxt - 1) / 2, b = nxt / 2; 
            LL period1 = a / A.size(), period2 = b / B.size();
            int up = A[a % A.size()], down = B[b % B.size()];
            LL fuck1 = up - (LL)period1 * l, fuck2 = down + (LL)period2 * l;
            if (fuck2 - fuck1 <= t * 2) {
                step = nxt;
                if (a >= b) res = (fuck1 + t) % l, dir = fuck2 - fuck1 == t * 2 ? 2 : 1;
                else res = (fuck2 - t) % l, dir = 1;
            }
        }
        res = (res + l) % l;
        vector<int> tmp;
        for (int i = 1; i <= n; i++) {
            if (w[i] == 1) tmp.push_back((x[i] + t) % l);
            else tmp.push_back((x[i] - t % l + l) % l);
        }
        sort(tmp.begin(), tmp.end());
        for (int i = 0, ct = 0; i < tmp.size(); i++) if (tmp[i] == res) {
            if (++ct < dir) continue;
            for (int j = 0; j < tmp.size(); j++) {
                ans[(base + j - 1) % n + 1] = tmp[(i + j) % tmp.size()];
            }
            break;
        }
        for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    }
}
