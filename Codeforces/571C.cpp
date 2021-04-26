#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef pair<int, int> P;

int fa[N], ans[N], ct[N], vis[N], bl[2][N];

vector<int> p[N];

int main() {
    int n, m; scanf("%d%d", &n, &m), memset(ans, -1, sizeof(ans));
    for (int i = 1; i <= n; i++) {
        int k; scanf("%d", &k), ct[i] = k;
        for (int j = 1, a; j <= k; j++) 
            scanf("%d", &a), p[i].push_back(a), bl[a < 0][abs(a)] = i;
    }
    priority_queue<P> q; 
    for (int i = 1; i <= n; i++) q.push(P(-ct[i], i));
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue; vis[u] = 1;
        if (!ct[u]) return puts("NO"), 0;
        for (auto t : p[u]) if (ans[abs(t)] == -1) {
            int cur = t < 0; t = abs(t);
            ans[t] = cur; int nxt = bl[cur ^ 1][t];
            if (nxt && !vis[nxt]) ct[nxt]--, q.push(P(-ct[nxt], nxt)); 
            break;
        }
    }
    puts("YES");
    for (int i = 1; i <= m; i++) if (ans[i] == 1) putchar('0');
    else putchar('1');
}