#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 998244353;

typedef pair<int, int> P;

int dp[2][45][N], st[32][N];

int get(int x, int y) {
    int res = 0;
    while (x || y) 
        res += x % 10 != y % 10, x /= 10, y /= 10;
    return res;
}

vector<int> r[N]; int fuck[N];

int main() {
    for (int i = 1; i <= N - 10; i++) 
        for (int j = 0; j <= 42; j++)
            dp[0][j][i] = dp[1][j][i] = i;
    for (int i = 1; i <= N - 10; i++) {
        for (int s = 1; s < 1 << 5; s++) {
            int tmp = i, nxt = 0;
            for (int j = 0, w = 1; j < 5; j++, w *= 10) {
                int c = tmp % 10; 
                if (!(s & (1 << j))) nxt += w * c;
                tmp /= 10;
            }
            st[s][i] = nxt;
        }
    }
    for (int w = 0; w < 42; w++) {
        for (int i = 1; i <= N - 10; i++) r[i].clear();
        for (int i = 1; i <= N - 10; i++) {
            int l = dp[0][w][i - 1], r = dp[1][w][i + 1];
            if (i == 1) l = 1;
            if (i == N - 10) r = N - 10;
            ::r[l].push_back(i), fuck[i] = r;
        }
        static int mx[32][N]; memset(mx, 0, sizeof(mx));
        for (int s = 1; s < 1 << 5; s++) {
            int nxt = w + __builtin_popcount(s) + 1;
            if (nxt > 42) continue;
            for (int i = 1; i <= N - 10; i++) {
                for (auto t : r[i])
                    mx[s][st[s][t]] = max(mx[s][st[s][t]], fuck[t]);
                dp[1][nxt][i] = max(dp[1][nxt][i], mx[s][st[s][i - 1]]);
            }
        }
        for (int i = 1; i <= N - 10; i++) r[i].clear();
        for (int i = 1; i <= N - 10; i++) {
            int l = dp[0][w][i - 1], r = dp[1][w][i + 1];
            if (i == 1) l = 1;
            if (i == N - 10) r = N - 10;
            ::r[r].push_back(i), fuck[i] = l;
        }
        memset(mx, 0x3f, sizeof(mx));
        for (int s = 1; s < 1 << 5; s++) {
            int nxt = w + __builtin_popcount(s) + 1;
            if (nxt > 42) continue;
            for (int i = N - 10; i >= 1; i--) {
                for (auto t : r[i])
                    mx[s][st[s][t]] = min(mx[s][st[s][t]], fuck[t]);
                if (i != N - 10) dp[0][nxt][i] = min(dp[0][nxt][i], mx[s][st[s][i + 1]]);
            }
        }
    }
    int T; scanf("%d", &T);
    while (T--) {
        int l, r; scanf("%d%d", &l, &r);
        for (int w = 1; w <= 42; w++) {
            bool flag = false;
            for (int i = l; i <= r; i++) {
                int t = get(0, i);
                if (t < w && dp[0][w - t - 1][i - 1] <= l && dp[1][w - t - 1][i + 1] >= r) {
                    flag = true; break;
                }
            }
            if (flag) {
                printf("%d\n", w); break;
            }
        }
    }
}