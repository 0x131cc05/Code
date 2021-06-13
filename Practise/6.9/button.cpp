#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int dp[2][50][N], fuck[2][50][N];

int dis(int x, int y) {
    int ct = 0;
    while (x || y) {
        if (x % 10 != y % 10) ct++;
        x /= 10, y /= 10;
    }
    return ct;
}

int mx = 0;

int DP(int type, int pos, int w) {
    if (w == 0) return fuck[type][w][pos] = pos;
    if (dp[type][w][pos] != -1) return dp[type][w][pos];
    if (type) {
        DP(type, pos, w - 1);
        int nw = pos - 1, r = fuck[type][w - 1][pos], at = r;
        for (int i = r, d = 0; i <= r && i <= N - 10; i++, d++) {
            if (d > 100 && i % 10 != 9 && (at - pos) % 10 != 9) continue;
            int t = dis(nw, i) + 1; 
            if (t > w) continue;
            int l = DP(0, i - 1, w - t);
            if (l <= pos) {
                int p = DP(1, i + 1, w - t);
                if (p >= r) at = i, r = p;
            }
            if (r == N - 10) break;
        }
        fuck[type][w][pos] = at;
        int hh = at - pos;
        return dp[type][w][pos] = r;
    } else {
        DP(type, pos, w - 1);
        int nw = pos + 1, l = fuck[type][w - 1][pos], at = l;
        for (int i = l, d = 0; i >= 1 && i >= l; i--, d++) {
            if (d > 100 && i % 10 != 9 && (pos - at) % 10 != 9) continue;
            int t = dis(nw, i) + 1;
            if (t > w) continue;
            int r = DP(1, i + 1, w - t);
            if (r >= pos) {
                int p = DP(0, i - 1, w - t);
                if (p <= l) at = i, l = p;
            }
            if (l == 1) break;
        }
        fuck[type][w][pos] = at;
        return dp[type][w][pos] = l;
    }
}

int main() {
    // freopen("button.in", "r", stdin), freopen("button.out", "w", stdout);
    memset(dp, -1, sizeof(dp));
    int T; scanf("%d", &T);
    while (T--) {
        int l, r; scanf("%d%d", &l, &r);
        for (int ans = 1; ans < 50; ans++) {
            bool flag = false;
            for (int i = l; i <= r; i++) {
                int w = dis(0, i) + 1;
                if (w <= ans) {
                    int a = DP(0, i - 1, ans - w), b;
                    if (a <= l && (b = DP(1, i + 1, ans - w)) >= r) {
                        flag = true; break;
                    } 
                }
            }
            if (flag) { printf("%d\n", ans); break; }
        }
    }
}

