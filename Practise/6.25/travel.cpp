#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

vector<int> G[N];

int val[N]; LL in[N], out[N];

LL mid;

bool dfs(int u) {
    if (!G[u].size()) {
        in[u] = out[u] = val[u];
        return true;
    }
    if ((!dfs(G[u][0])) || (!dfs(G[u][1]))) return false;
    LL A[4], B[4]; int id[4];
    for (int t = 0; t < 4; t++) {
        id[t] = t;
        int a = t & 1, b = t >> 1;
        A[t] = (a ? in[G[u][0]] : out[G[u][0]]), B[t] = (b ? in[G[u][1]] : out[G[u][1]]);
    }
    sort(id, id + 4, [&](int a, int b) {
        return A[a] + B[a] > A[b] + B[b];
    });
    bool flag = false;
    for (int i = 0; i < 4; i++) if (A[id[i]] + B[id[i]] <= mid) {
        flag = true; int t = id[i];
        int a = t & 1, b = t >> 1;
        in[u] = a ? out[G[u][0]] : in[G[u][0]];
        out[u] = b ? out[G[u][1]] : in[G[u][1]];
        break;
    }
    in[u] += val[u], out[u] += val[u];
    return flag;
}

int main() {
    int n; scanf("%d", &n);
    LL sum = 0;
    for (int i = 2; i <= n; i++) {
        int f; scanf("%d%d", &f, &val[i]);
        G[f].push_back(i), sum += val[i];
    }
    LL l = 0, r = sum, res = -1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (dfs(1)) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%lld\n", res);
}

