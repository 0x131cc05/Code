#include <bits/stdc++.h>
using namespace std;

const int N = 40010;

typedef long long LL;

LL count(LL r, int a, int x) {
    return r / a + (r % a >= x);
}

LL count(LL l, LL r, int a, int x) {
    if (l > r) return 0;
    return count(r, a, x) - count(l - 1, a, x);
}

LL dp[3][2][2][N];

LL calc(LL r, int A, int x) {
    memset(dp, 0, sizeof(dp));
    int cur = 0, ls = -1, ls1 = -1;
    dp[0][1][0][0] = 1;
    for (int i = 62; i >= 0; i--) {
        ls1 = ls, ls = cur, cur = (cur + 1) % 3;
        memset(dp[cur], 0, sizeof(dp[cur]));
        int nw = (r >> i) & 1;
        for (int a = 0; a <= 1; a++)
            for (int b = 0; b <= 1; b++) 
                for (int c = 0; c <= 1; c++) {
                    if (a && c > nw) continue;
                    int nxt = a && c == nw;
                    for (int t = 0; t < A; t++) if (dp[ls][a][b][t]) 
                        dp[cur][nxt][b][(t * 2 + c) % A] += dp[ls][a][b][t];
                }
        if (ls1 != -1) {
            int nw1 = (r >> (i + 1)) & 1;
            for (int a = 0; a <= 1; a++)
                for (int c = 0; c <= 1; c++) {
                    if (a && (c > nw1)) continue;
                    int nxt = a && c == nw1;
                    if (nxt && ((c ^ 1) > nw)) continue;
                    nxt = nxt && (c ^ 1) == nw;
                    for (int t = 0; t < A; t++) if (dp[ls1][a][0][t]) 
                        dp[cur][nxt][1][((t * 2 + c) * 2 + (c ^ 1)) % A] += dp[ls1][a][0][t];
                }
        }
    }
    return dp[cur][0][1][x] + dp[cur][1][1][x] - dp[cur][0][0][x] - dp[cur][1][0][x];
} 

int main() {
    // freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
    int a; LL b, n; cin >> a >> b >> n;
    LL l = a + b, r = a * n + b, all = 0;
    if (!((b % a) & 1)) all += count(l, r - 1, a * 2, b % a);
    if (!((b % a + a) & 1)) all += count(l, r - 1, a * 2, b % a + a);
    all += calc(r, a, b % a) - calc(l - 1, a, b % a);
    cout << all << endl;
}