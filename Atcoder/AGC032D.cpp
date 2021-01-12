#include <bits/stdc++.h>
using namespace std;

const int N = 5010;

typedef long long LL;

int num[N]; LL dp[N];

int main() {
    int n, A, B; scanf("%d%d%d", &n, &A, &B);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    memset(dp, 0x3f, sizeof(dp)), dp[0] = 0, num[n + 1] = n + 1, n++;
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1, l = 0, r = 0, mx = 0; j >= 0; j--) {
            if (num[j] < num[i] && num[j] > mx) mx = num[j];
            if (mx <= num[j] && num[j] < num[i]) 
                dp[i] = min(dp[i], dp[j] + (LL)l * B + (LL)r * A);
            if (num[j] < num[i]) l++;
            else r++;
        }
    }
    printf("%lld\n", dp[n]);
}
