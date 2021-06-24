#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;
const int WEN = 1e9;

typedef long long LL;

LL dp[N]; int q[N];

inline LL calc(int pos) {
    return dp[pos] - (LL)pos * WEN;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int l, r, c; scanf("%d%d%d", &l, &r, &c); int head = 1, tail = 0;
        for (int j = r, pos = 0; j <= m; j++) {
            while (pos <= j - l) {
                while (head <= tail && calc(q[tail]) >= calc(pos)) tail--;
                q[++tail] = pos, pos++;
            }
            while (head <= tail && q[head] < j - r) head++;
            if (head <= tail) dp[j] = max(dp[j], calc(q[head]) + (LL)j * WEN - c);
        }
    }
    printf("%lld\n", dp[m]);
}
