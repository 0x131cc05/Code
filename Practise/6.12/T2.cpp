#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int INF = 0X3F3F3F3F;
const int MAXN = 1E6+10;
int dp[MAXN], pre[MAXN], arr[MAXN];
int main()
{
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    while (q--) {
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        memset(dp, 0, sizeof(dp));
        memset(pre, 0 ,sizeof(pre));
        int tmp; int len = r - l + 1;
        for(int i = 1; i <= k; i++)
        {
            tmp = -INF;
            for(int j = i; j <= len; j++)
            {
                dp[j] = max(dp[j-1], pre[j-1])+arr[l + j - 1];
                pre[j-1] = tmp;
                tmp = max(tmp, dp[j]);
            }
        }
        printf("%d\n", tmp);
    }
    return 0;
}
