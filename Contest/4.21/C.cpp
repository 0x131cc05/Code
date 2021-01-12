#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;

struct data {

int a, p, v;

bool operator < (const data &b) const {
    return v > b.v;
}

} p[N];

int dp[2][2][2][N * 4], remain[N];

int main() {
    int n, tot = 0; scanf("%d", &n);
    for (int i = 1; i <= n; i++) 
        scanf("%d%d%d", &p[i].a, &p[i].p, &p[i].v), tot += p[i].a;
    sort(p + 1, p + n + 1); int cur = 0, s = 0;
    memset(dp, -0x3f, sizeof(dp)), dp[0][0][0][0] = 0;
    for (int i = 1; i <= n; i++) {
        cur ^= 1;
        for (int j = 0; j <= s; j++)
            dp[cur][0][0][j] = dp[cur][0][1][j] = dp[cur][1][0][j] = dp[cur][1][1][j] = -1e9;
        int h = max(p[i].a / (2 * p[i].p) - 1, 0); remain[p[i].p] += h;
        for (int j = 0; j < 2 * p[i].p && j <= p[i].a; j++) {
            auto process = [&](int x) { // 给第一堆分配 x
                int tmp = p[i].p;
                assert(x >= 0 && x <= p[i].a);
                auto check = [&](int x) -> bool { return x % (2 * tmp) == 2 * tmp - 1; };
                bool t1 = check(x), t2 = check(p[i].a - x);
                int val = x / (2 * tmp) * p[i].v + (p[i].a - x) / (2 * tmp) * p[i].v;
                for (int a = 0; a <= 1; a++)
                    for (int b = 0; b <= 1; b++)
                        for (int l = 0; l <= s; l++) if (dp[cur ^ 1][a][b][l] >= 0) {
                            int ta = a, tb = b, v = dp[cur ^ 1][a][b][l] + val;
                            if (t1) { ta ^= 1; if (ta) v += p[i].v; }
                            if (t2) { tb ^= 1; if (!tb) v += p[i].v; }
                            dp[cur][ta][tb][l + x] = max(dp[cur][ta][tb][l + x], v);
                        }
            };
            process(j);
            if (j <= p[i].a % (2 * p[i].p) && j + 2 * p[i].p <= p[i].a) 
                process(j + 2 * p[i].p); 
        }
        s += 4 * p[i].p;
    }
    bitset<500000> g; g[0] = 1;
    for (int i = 1; i <= N - 10; i++) if (remain[i]) {
        vector<int> tmp; int s = 0;
        for (int t = 1; s + t <= remain[i]; t *= 2) 
            tmp.push_back(t), s += t;
        if (s != remain[i]) tmp.push_back(remain[i] - s);
        for (auto t : tmp) 
            g |= g << t * i;
    }
    int res = 0;
    for (int a = 0; a <= 1; a++)
        for (int b = 0; b <= 1; b++)
            for (int i = 0; i * 2 <= tot / 2; i++) if (g[i] && tot / 2 - i * 2 >= 0) 
                res = max(res, dp[cur][a][b][tot / 2 - i * 2]);
    printf("%d\n", res);
    return 0;
}