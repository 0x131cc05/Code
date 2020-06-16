#include <bits/stdc++.h>
using namespace std;

<<<<<<< HEAD
const int N = 35010;

int l[N], r[N], n;

priority_queue<int, vector<int>, greater<int>> R; 
priority_queue<int> L;

inline int solve() {
    while (L.size()) L.pop(); while (R.size()) R.pop();
    int diff0 = 0, diff1 = 0; // 向左平移
    L.push(0), R.push(0); int ans = 0; // 最低点的值
    for (int i = 1; i <= n; i++) {
        diff0 += l[i], diff1 += l[i], diff0 += r[i] - l[i];
        int A = L.top() - diff0, B = R.top() - diff1;
        if (A <= 0 && 0 <= B)  // f(x) = f'(x) + |x|
            L.push(0 + diff0), R.push(0 + diff1);
        else if (0 < A) 
            ans += A, L.push(0 + diff0), L.push(0 + diff0), L.pop(), R.push(A + diff1); 
        else ans -= B, R.push(0 + diff1), R.push(0 + diff1), R.pop(), L.push(B + diff0);
    }
    if (L.top() - diff0 >= 0) {
        int tp = 0, ls = L.top() - diff0;
        while (L.size()) {
            int p = L.top() - diff0; L.pop();
            if (ls <= 0) break;
            ans += (ls - max(p, 0)) * tp, tp++, ls = p;
        }
    } else {
        int tp = 0, ls = R.top() - diff1;
        while (R.size()) {
            int p = R.top() - diff1; R.pop();
            if (ls >= 0) break;
            ans += (min(0, p) - ls) * tp, tp++, ls = p;
        }
    }
    return ans;
}

inline int solve(int x) {
    l[1] -= x, r[1] -= x, l[n] += x, r[n] += x;
    int res = solve();
    l[1] += x, r[1] += x, l[n] -= x, r[n] -= x;
    return res + abs(x);
}

int main() {
    scanf("%d", &n); int up = 0;
    for (int i = 1, x; i <= n; i++) 
        scanf("%d%d%d", &x, &l[i], &r[i]), l[i] -= x, r[i] -= x, up += x;
    int l = -up, r = up, mid, res = 1e9;
    while (l <= r) {
        mid = (l + r) >> 1;
        int A = solve(mid), B = solve(mid + 1);
        res = min(res, min(A, B));
        if (A < B) r = mid - 1;
        else l = mid + 2;
    }
    printf("%d\n", res);
}
=======
const int N = 510;

int dp[N][N * 2], l[N], r[N], a[N];

inline int Abs(int x) {
    return x > 0 ? x : -x;
}

int stk[N];

int main() {
    int n, t = 0, res = 1e9; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i], &l[i], &r[i]), t = max(t, a[i]);
        a[i + n] = a[i], l[i + n] = l[i], r[i + n] = r[i];
    }
    for (int i = 1; i <= n; i++) {
        memset(dp, 0x3f, sizeof(dp));
        for (int j = l[i]; j <= r[i]; j++) 
            dp[1][j - a[i] + N] = 0;
        for (int j = i + 1; j < i + n; j++)
            for (int ls = -t; ls <= t; ls++) if (dp[j - i][ls + N] >= 0) {
                int L = max(l[j], -t - ls + a[j]), R = min(r[j], t + a[j] - ls);
                for (int k = L; k <= R; k++) 
                    dp[j - i + 1][k - a[j] + ls + N] = min(dp[j - i + 1][k - a[j] + ls + N], dp[j - i][ls + N] + Abs(ls));
            }
                
        res = min(res, dp[n][N]);
    }
    printf("%d\n", res);
}
>>>>>>> 5217ca211b9029c9894ce8e9b14ae336cce8a73e
