#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef pair<int, int> P;
typedef long long LL;

vector<P> G[N];

int head[N], ecnt, d[N];

void adde(int from, int to, int w) {
    G[from].push_back(P(to, w)), G[to].push_back(P(from, w)), d[from]++, d[to]++;
}

struct tcurts {
    priority_queue<LL> A, B; LL tot;
    void push(LL x) { A.push(x), tot += x; }
    void erase(LL x) { B.push(x), tot -= x; }
    int size() { return A.size() - B.size(); }
    LL all() { return tot; }
    LL top() {
        while (B.size() && A.top() == B.top())
            A.pop(), B.pop();
        return A.top();
    }
    void pop() { LL t = top(); tot -= t; B.push(t);}
} q[N];

int lim, vis[N];

LL dp[2][N]; // 1 means choose

void dfs(int u, int f) {
    vis[u] = lim;
    for (auto t : G[u]) if (t.first != f) {
        if (d[t.first] <= lim) break;
        dfs(t.first, u);
    }
    LL base = 0; int remain = d[u] - lim;
    while (q[u].size() > remain) q[u].pop();
    vector<LL> tmp, del;
    for (auto t : G[u]) if (t.first != f) {
        int v = t.first;
        if (d[t.first] <= lim) break;
        LL delta = dp[1][v] - dp[0][v] + t.second;
        if (delta <= 0) base += dp[1][v] + t.second;
        else base += dp[0][v], q[u].push(delta), tmp.push_back(delta);
    }
    while (q[u].size() && q[u].size() > remain)
        del.push_back(q[u].top()), q[u].pop();
    dp[0][u] = base + q[u].all();
    if (remain && q[u].size() == remain)
        del.push_back(q[u].top()), q[u].pop();
    dp[1][u] = base + q[u].all();
    for (auto t : del) q[u].push(t);
    for (auto t : tmp) q[u].erase(t);
}

void merge(int u) {
    for (auto t : G[u]) {
        if (d[t.first] <= lim) break;
        q[t.first].push(t.second);
    }
}

int id[N];

vector<LL> minimum_closure_costs(int n, vector<int> U, vector<int> V, vector<int> W) {
    vector<LL> fuck;
    LL ans = 0;
    for (int i = 0; i + 1 < n; i++) 
        adde(U[i] + 1, V[i] + 1, W[i]), ans += W[i];
    fuck.push_back(ans);
    for (int i = 1; i <= n; i++) id[i] = i;
    for (int i = 1; i <= n; i++) {
        sort(G[i].begin(), G[i].end(), [&](P a, P b) {
            return d[a.first] > d[b.first];
        });
    }
    sort(id + 1, id + n + 1, [&](int a, int b) {
        return d[a] < d[b];
    });
    int cur = 1;
    for (lim = 1; lim < n; lim++) {
        while (cur <= n && d[id[cur]] == lim) merge(id[cur++]);
        ans = 0;
        for (int i = cur; i <= n; i++) {
            if (vis[id[i]] == lim) continue;
            dfs(id[i], 0), ans += dp[0][id[i]];
        }
        fuck.push_back(ans);
    }
    return fuck;
}

int main() {
    vector<int> U, V, W;
    int n; scanf("%d", &n);
    for (int i = 1, a, b, c; i < n; i++) scanf("%d%d%d", &a, &b, &c), U.push_back(a - 1), V.push_back(b - 1), W.push_back(c);
    auto res = minimum_closure_costs(n, U, V, W);
    for (auto t : res) printf("%lld ", t);
    puts("");
}
