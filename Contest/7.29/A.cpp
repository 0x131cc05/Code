#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

int p[5][N], pos[N], k, nw[5], id[5];

int process(int l, int r, int ct) {
    static int tp[5]; memcpy(tp, nw, sizeof(nw));
    for (int i = l; i <= r; i++) {
        bool flag = false;
        for (int j = 0; j < k; j++) if (p[j][i] == tp[j]) {
            flag = true; break;
        }
        if (!flag) {
            if (ct >= k) return i - 1;
            tp[id[ct]] = p[id[ct]][i], ct++;
        }
    }
    return r;
}

void solve(int l, int r) {
    if (pos[l] >= r) return;
    if (r - l + 1 <= k) {
        for (int i = l; i <= r; i++) pos[i] = max(pos[i], r);
        return;
    } 
    int mid = (l + r) >> 1;
    for (int i = 0; i < k; i++) id[i] = i;
    do {
        memset(nw, -1, sizeof(nw)); int ct = 0, ls = mid; bool fg = false;
        for (int i = mid, ls = mid; i >= l; i--) {
            bool flag = false;
            for (int j = 0; j < k; j++) if (p[j][i] == nw[j]) {
                flag = true; break;
            }
            if (!flag) {
                int wkr = process(mid + 1, r, ct);
                for (int j = i + 1; j <= ls; j++) pos[j] = max(pos[j], wkr);
                if (ct >= k) { fg = true; break; }
                nw[id[ct]] = p[id[ct]][i], ct++, ls = i;
            }
        }
        if (!fg) {
            int wkr = process(mid + 1, r, ct);
            for (int i = l; i <= ls; i++) pos[i] = max(pos[i], wkr);
        }
    } while (next_permutation(id, id + k));
    solve(l, mid), solve(mid + 1, r);
}

int main() {
    // freopen("ex_stars1.in", "r", stdin);
    int n; scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < k; j++) scanf("%d", &p[j][i]);
    solve(1, n); LL res = 0;
    for (int i = 1; i <= n; i++) 
        res += (LL)(pos[i] - i + 2) * (pos[i] - i + 1) / 2;
    printf("%lld\n", res);
}