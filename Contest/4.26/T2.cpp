#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

typedef long long LL;

int num[N]; vector<LL> dp[2][N * 4];

inline void check(LL &x, LL y) {
    if (y > x) x = y;
}

void process(int rt, int l, int r) {
    if (l == r) return dp[0][rt] = {0, num[l]}, dp[1][rt] = {0, -num[l]}, void();
    int mid = (l + r) >> 1;
    process(rt << 1, l, mid), process(rt << 1 | 1, mid + 1, r);
    for (int i = 0; i <= 1; i++) {
        dp[i][rt].resize(r - l + 2);
        for (auto &t : dp[i][rt]) t = -1e18;
        dp[i][rt][0] = 0;
        auto &res = dp[i][rt];
        for (int left = 0; left <= 1; left++) 
            for (int right = 0; right <= 1; right++) {
                int s = i ^ left; dp[i][rt][left + right] = max(dp[i][rt][left + right], dp[i][rt << 1][left] + dp[s][rt << 1 | 1][right]);
                int a = left, b = right, L = dp[i][rt << 1].size() - 1, R = dp[s][rt << 1 | 1].size() - 1;
                auto &A = dp[i][rt << 1], &B = dp[s][rt << 1 | 1];
                while (a + 2 <= L || b + 2 <= R) {
                    if (b + 2 > R || (a + 2 <= L && A[a + 2] - A[a] >= B[b + 2] - B[b]))
                        check(res[a + b + 2], A[a + 2] + B[b]), a += 2;
                    else check(res[a + b + 2], A[a] + B[b + 2]), b += 2;
                }
            }
    }
}

template<class T> inline void read(T &x) {
    x = 0; char c = getchar(); int t = 1;
    while (!isdigit(c)) t = c == '-' ? -1 : 1, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    x *= t;
}

int main() {
    int n; read(n);
    for (int i = 1; i <= n; i++) read(num[i]);
    process(1, 1, n);
    for (int i = 1; i <= n; i++) printf("%lld ", dp[0][1][i]);
    return 0;
}