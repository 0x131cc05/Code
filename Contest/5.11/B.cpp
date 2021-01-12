#include <bits/stdc++.h>
using namespace std;

const int N = 150010;

typedef long long LL;

vector<int> G[N], G1[N];

int A[N], B[N];

int main() {
    int n, m, a, b; scanf("%d%d%d%d", &n, &m, &a, &b);
    for (int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        G[a].push_back(b), G[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) G1[i] = G[i];
    memset(A, -1, sizeof(A)), A[1] = 0; queue<int> q; q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : G[u]) if (A[v] == -1) 
            A[v] = A[u] + 1, q.push(v);
    }
    memset(B, -1, sizeof(B)), B[1] = 0, q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop(); static int vis[N];
        for (auto v : G1[u]) vis[v] = 1;
        for (auto v : G1[u]) {
            vector<int> tmp;
            for (auto t : G[v]) {
                if (!vis[t] && !~B[t]) B[t] = B[u] + 1, q.push(t);
                else if (!~B[t]) tmp.push_back(t);
            }
            G[v] = tmp;
        }
        for (auto v : G1[u]) vis[v] = 0;
    }
    for (int i = 2; i <= n; i++) {
        LL t1 = (LL)A[i] * a, t2 = (LL)(A[i] % 2) * a + (LL)(A[i] / 2) * b, t3 = B[i] == -1 ? 1e18 : (LL)B[i] * b;
        printf("%lld ", min(t1, min(t2, t3)));
    }
    
}
