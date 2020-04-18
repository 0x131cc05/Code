#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef pair<int, int> P;

int x[N], y[N], id[N];

int main() {
    int n, k; scanf("%d%d", &n, &k);
    if (n <= k) return puts("-1"), 0;
    for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]), id[i] = i;
    sort(id + 1, id + n + 1, [](int a, int b) {
        if (x[a] != x[b]) return x[a] < x[b];
        return y[a] < y[b];
    });
    static P stk[N]; int top = 0;
    for (int i = 1; i <= k + 1; i++)
        for (int j = n - k; j <= n; j++) 
            stk[++top] = P(x[id[i]] + x[id[j]], y[id[i]] + y[id[j]]);
    sort(stk + 1, stk + top + 1), top = unique(stk + 1, stk + top + 1) - stk - 1;
    int res = 0;
    for (int i = 1; i <= top; i++) {
        int remain = 0, l = 1, r = n, X = stk[i].first, Y = stk[i].second;
        while (l <= r) {
            if (l == r) {
                if (x[id[l]] * 2 != X || y[id[l]] * 2 != Y) remain++;
                break; 
            } 
            int A = x[id[l]] + x[id[r]], B = y[id[l]] + y[id[r]];
            if (A == X && B == Y) l++, r--;
            else {
                remain++;
                if (A == X) {
                    if (B > Y) r--; else l++;
                } else {
                    if (A > X) r--; else l++;
                }
            }
            if (remain > k) break;
        }
        if (remain <= k) res++;
    }
    printf("%d\n", res);
    return 0;
}
