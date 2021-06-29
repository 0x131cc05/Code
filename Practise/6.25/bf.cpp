#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

vector<int> G[N];

int val[N], tp[N];

LL res;

bool flag;

LL dfs(int u, LL tot) {
    if (!G[u].size()) {
        if (flag) res = max(res, tot);
        flag = true;
        return val[u];
    }
    LL tmp = dfs(G[u][tp[u]], tot + val[G[u][tp[u]]]);
    return dfs(G[u][tp[u] ^ 1], tmp + val[G[u][tp[u] ^ 1]]) + val[u];
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        int f; scanf("%d%d", &f, &val[i]);
        G[f].push_back(i);
    }
    vector<int> hh;
    for (int i = 1; i <= n; i++) if (G[i].size()) hh.push_back(i);
    int tot = hh.size();
    LL ans = 1e18;
    for (int s = 0; s < 1 << tot; s++) {
        res = 0, flag = false;
        for (int i = 0; i < tot; i++)
            tp[hh[i]] = (s >> i) & 1;
        dfs(1, 0), ans = min(ans, res);
    }
    printf("%lld\n", ans);
}