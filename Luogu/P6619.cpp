#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;

typedef long long LL;

LL A[N], B[N]; int n;

inline void updateA(int x, int y) {
    for (; x <= n; x += x & -x) A[x] += y;
}

inline void updateB(int x, int y) {
    for (; x <= n; x += x & -x) B[x] += y;
}

int val[N], t[N], x[N], y[N], tot, type[N]; LL wkr;

inline LL queryA(int x) {
    LL res = 0;
    for (; x; x -= x & -x) res += A[x];
    return res; 
}

inline LL queryB(int x) {
    LL res = 0;
    for (; x; x -= x & -x) res += B[x];
    return res;
}

int main() {
    int q; scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int op; scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d%d", &t[i], &x[i], &y[i]), type[i] = 1;
            val[++tot] = t[i] == 1 ? x[i] + 1 : x[i];
        }
        else {
            int k; scanf("%d", &k), type[i] = 0;
            t[i] = t[k], x[i] = x[k], y[i] = -y[k];
        }
    }
    sort(val + 1, val + tot + 1), tot = unique(val + 1, val + tot + 1) - val - 1, n = tot; 
    for (int i = 1; i <= q; i++) {
        x[i] = lower_bound(val + 1, val + tot + 1, x[i] + (t[i] == 1)) - val;
        if (t[i] == 0) updateA(x[i], y[i]);
        else updateB(x[i], y[i]), wkr += y[i];
        int nw = 0; LL tmp = 0;
        for (int i = 20; i >= 0; i--) if (nw + (1 << i) <= n) {
            int nxt = nw | 1 << i; LL v = tmp + A[nxt] + B[nxt] - wkr;
            if (v <= 0) tmp += A[nxt] + B[nxt], nw = nxt;
        }
        LL a = queryA(nw), b = nw < n ? wkr - queryB(nw + 1) : 0;
        if (max(a, b) == 0) puts("Peace");
        else {
            if (b >= a) {
                LL fuck = wkr - b; int ans = 0; tmp = 0;
                for (int i = 20; i >= 0; i--) if (ans + (1 << i) <= n) {
                    int nxt = ans | 1 << i; LL v = tmp + B[nxt];
                    if (v <= fuck) tmp += B[nxt], ans = nxt;
                }
                printf("%d %lld\n", val[ans + 1] - 1, b * 2);
            }
            else printf("%d %lld\n", val[nw + 1] - 1, a * 2);
        }
    }
}
