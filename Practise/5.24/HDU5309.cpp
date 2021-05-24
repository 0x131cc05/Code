#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int N = 500010;

typedef long long LL;

int n, m, k;

LL pre[N];

bool dp[N]; int lst[N], fuck;

bool DP(int mid) {
    for (int i = 1; i <= n; i++) dp[i] = lst[i] = 0;
    LL mn = 1e18;
    for (int i = n; i >= 1; i--) {
        if (pre[n] + i * k + m > 0) dp[i] = 1;
        else break;
    }
    mn = 1e18;
    int pos = -1;
    for (int i = n; i >= 1; i--) {
        if (pos != -1 && pre[pos] + i * k + m <= 0) pos = -1;
        if (pos != -1 && !dp[i]) dp[i] = 1, lst[i] = pos;
        if (i + mid - 1 <= n && dp[i + mid - 1]) pos = i + mid - 1;
    }
    bool flag = false;
    for (int i = 1; i <= n; i++) 
        if (dp[i] && m + pre[i] > 0) {
            fuck = i, flag = true;
            break;
        }
    return flag;
}

int main() {
    while (~scanf("%d%d%d", &n, &m, &k)) {
        for (int i = 1; i <= n; i++) 
            scanf("%lld", &pre[i]), pre[i] = -pre[i], pre[i] += pre[i - 1];
        for (int i = 2; i <= n; i++) pre[i] = min(pre[i], pre[i - 1]);
        int l = 1, r = n, mid, res = -1, p;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (DP(mid)) res = mid, l = mid + 1, p = fuck;
            else r = mid - 1;
        }
        if (res == n) puts("Poor JRY!");
        else if (res == -1) puts("Poor Hero!");
        else {
            printf("%d\n", res), DP(res);
            vector<int> res;
            while (p) {
                res.push_back(p), p = lst[p];
            }
            printf("%d\n", res.size());
            for (int i = 0; i < res.size(); i++) {
                printf("%d", res[i]);
                if (i + 1 != res.size()) putchar(' ');
            }
            puts("");
        }
    }
}

 