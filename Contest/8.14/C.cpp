#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef long long LL;

LL pre[N]; int n, k, lst[N];

namespace sol1 {
    __int128 dp[N], mid;
    
    bool inter(int a, int b, __int128 pr) {
        return (__int128)(dp[a] +(__int128) pre[a] * pre[a] - dp[b] - (__int128)pre[b] * pre[b]) >= (__int128)pr * (2 * pre[a] - 2 * pre[b]);
    }
    
    bool inter2(int a, int b, int c, int d) {
        return (dp[a] + (__int128)pre[a] * pre[a] - dp[b] - (__int128)pre[b] * pre[b]) * (2 * pre[c] - 2 * pre[d]) >= (__int128)(dp[c] + (__int128)pre[c] * pre[c] - dp[d] - (__int128)pre[d] * pre[d]) * (2 * pre[a] - 2 * pre[b]) ;
    }
    
    int solve() {
    	dp[0] = 0;
        static int q[N], layer[N]; int head = 1, tail = 1; q[1] = layer[0] = 0;
        for (int i = 1; i <= n; i++) {
            while (head + 1 <= tail && inter(q[head], q[head + 1],pre[i])) head++;
            lst[i] = q[head], dp[i] = dp[q[head]] + (pre[i] - pre[q[head]]) * (pre[i] - pre[q[head]]) + mid, layer[i] = layer[q[head]] + 1;
            if (pre[i] == pre[i - 1]) continue;
            while (head + 1 <= tail && inter2(q[tail - 1], q[tail], q[tail - 1], i)) tail--;
            q[++tail] = i;
        }
        return layer[n];
    }
    
    int main() {
        LL l = 0, r = 1e18;
        for (int i = 1; i <= 100; i++) {
            mid = (l + r) / 2;
            if (solve() <= k) r = mid;
            else l = mid; 
        }
        mid = r, solve(); 
    }
}

namespace sol2 {
    double dp[N], mid;

    double inter(int a, int b) {
        return (dp[a] + pre[a] * pre[a] - dp[b] - pre[b] * pre[b]) / (2 * pre[a] - 2 * pre[b]);
    }
    
    int solve() {
        static int q[N], layer[N]; int head = 1, tail = 1; q[1] = layer[0] = 0;
        for (int i = 1; i <= n; i++) {
            while (head + 1 <= tail && inter(q[head], q[head + 1]) <= pre[i] + 1e-7) head++;
            lst[i] = q[head], dp[i] = dp[q[head]] + (pre[i] - pre[q[head]]) * (pre[i] - pre[q[head]]) + mid, layer[i] = layer[q[head]] + 1;
            if (pre[i] == pre[i - 1]) continue;
            while (head + 1 <= tail && inter(q[tail - 1], q[tail]) >= inter(q[tail - 1], i) - 1e-7) tail--;
            q[++tail] = i;
        }
        return layer[n];
    }
    
    int main() {
        double l = -1e18, r = 1e18;
        for (int i = 1; i <= 100; i++) {
            mid = (l + r) / 2;
            if (solve() <= k) r = mid;
            else l = mid; 
        }
        mid = r, solve(); 
        
    }
}

bool check(int l1, int r1, int l2, int r2) {
    LL t = pre[r2] - pre[l2 - 1] - pre[r1] + pre[l1 - 1];
    if (t < 0) t = -t;
    LL mx = 0;
    for (int i = l1; i <= r2; i++) mx = max(mx, pre[i] - pre[i - 1]);
    return t <= mx;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%lld", &pre[i]), pre[i] += pre[i - 1];
    if (n < 200000) sol2::main();
    else sol1::main();
    vector<int> res;
    for (int p = lst[n]; p; p = lst[p]) res.push_back(p);
    reverse(res.begin(), res.end()); res.push_back(n);
    for (int i = 1; i <= n; i++) if (pre[i] == pre[i - 1] && res.size() < k) 
        res.push_back(i);
    sort(res.begin(), res.end());
    for (int i = 0, ls = 1; i + 1 < res.size(); i++) {
        if (!check(ls, res[i], res[i] + 1, res[i + 1])) {
            puts("No Solution"); return 0;
        }
        ls = res[i] + 1;
    }
    for (auto t : res) if (t != n) printf("%d ", t);
}


