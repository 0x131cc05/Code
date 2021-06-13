#include <bits/stdc++.h>
using namespace std;

const int N = 10010;
const int mod = 998244353;

typedef long long LL;

int num[N], dp[2][2][N];

void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int query(int l, int r, int x) {
    if (x < 0) return 0;
    int res = 0; bool flag = false;
    for (int i = 29; i >= 0; i--) {
        dp[0][0][l - 1] = 1, dp[1][0][l - 1] = 0;
        dp[0][1][l - 1] = 0, dp[1][1][l - 1] = 0;
        int all = 0;
        for (int j = l; j <= r; j++) {
            int c = (num[j] >> i) & 1; all ^= c;
            for (int t = 0; t <= 1; t++)
                for (int v = 0; v <= 1; v++)
                    dp[t][v][j] = 0;
            for (int t = 0; t <= 1; t++) 
                for (int v = 0; v <= 1; v++)
                    for (int nw = 0; nw <= c; nw++) if (dp[t][v][j - 1]) {
                        int w = 1;
                        if (nw == c || (nw != c && t)) 
                            w = (nw != c) ? (1 << i) : (num[j] & ((1 << i) - 1)) + 1;
                        while (w >= mod) w -= mod;
                        Inc(dp[t | (nw != c)][v ^ nw][j], (LL)w * dp[t][v][j - 1] % mod); 
                    }
        }
        int w1 = 1 << i, w2 = (x & ((1 << i) - 1)) + 1;
        if (flag) res = (res + (LL)(dp[1][0][r] + dp[1][1][r]) * w1) % mod;
        else {
            int c = (x >> i) & 1;
            if (c) res = (res + (LL)dp[1][0][r] * w1) % mod;
            res = (res + (LL)dp[1][c][r] * w2) % mod;
            if (all < c) flag = true;
            if (all > c) break;
        }   
    }
    int all = 0;
    for (int i = l; i <= r; i++) 
        all ^= num[i];
    if (all <= x) res++;
    return res;
} 

int main() {
    freopen("xor2.in", "r", stdin), freopen("xor.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    // cout << query(1, 3, 0) << endl;
    for (int i = 1; i <= m; i++) {
        int op, a, b, l, r; scanf("%d%d%d", &op, &a, &b);
        if (op == 1) num[a] = b;
        else {
            scanf("%d%d", &l, &r);
            printf("%d\n", (query(a, b, r) - query(a, b, l - 1) + mod) % mod);
        }
    }
}