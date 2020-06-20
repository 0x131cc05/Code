#include <bits/stdc++.h>
using namespace std;

const int N = 610;
const int mod = 1e9 + 7;

typedef long long LL;

struct WEN {

int x, type;

bool operator < (const WEN &b) {
    if (x != b.x) return x > b.x;
    return type < b.type;     
}

};

// ÓÃaÆ¥Åäb

vector<WEN> tmp;

int dp[2][N][N];

inline void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

int main() {
    freopen("ds.in", "r", stdin), freopen("ds.out", "w", stdout);
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        tmp.push_back((WEN){ a, 0 }), tmp.push_back((WEN){ b, 1 });
    }
    sort(tmp.begin(), tmp.end());
    dp[0][0][0] = 1; int t = tmp.size();
    for (int i = 1; i <= t; i++) {
        int type = tmp[i - 1].type;
        for (int j = 0; j < i; j++) if (dp[0][i - 1][j] || dp[1][i - 1][j]) {
            if (type == 0) {
                if (j) Inc(dp[0][i][j - 1], (LL)dp[0][i - 1][j] * j % mod), Inc(dp[1][i][j - 1], (LL)dp[1][i - 1][j] * j % mod);
                Inc(dp[0][i][j], dp[0][i - 1][j]);
            } else {
                Inc(dp[0][i][j + 1], dp[0][i - 1][j]), Inc(dp[1][i][j + 1], dp[1][i - 1][j]);
                Inc(dp[1][i][j], dp[1][i - 1][j]), Inc(dp[1][i][j], dp[0][i - 1][j]);
            }   
        }
    }
    printf("%d\n", (dp[0][t][0] + dp[1][t][0]) % mod);
} 
