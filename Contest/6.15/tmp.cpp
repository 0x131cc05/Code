#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;
const int WEN = 1e9;

typedef long long LL;

LL dp[N]; int l[N], r[N], c[N], n, pos[110]; deque<int> q[110];

inline LL calc(int pos) {
    return dp[pos] - (LL)pos * WEN;
}

int main() {
    int m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) 
        scanf("%d%d%d", &l[i], &r[i], &c[i]);
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) if (j >= r[i]) { 
            while (pos[i] <= j - l[i]) {
                while (q[i].size() > 0 && calc(q[i].back()) >= calc(pos[i])) 
                    q[i].pop_back();
                q[i].push_back(pos[i]), pos[i]++;
            }
            while (q[i].size() && q[i].front() < j - r[i]) q[i].pop_front();
            if (q[i].size())
                dp[j] = max(dp[j], calc(q[i].front()) + (LL)j * WEN - c[i]);
        }
    }
    printf("%lld\n", dp[m]);
}
