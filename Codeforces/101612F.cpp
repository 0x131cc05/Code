#include <bits/stdc++.h>
using namespace std;

const int N = 21;

typedef long long LL;

struct edge {
    int to, next;
} e[N * N];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
}

int dfn[N], low[N], dfsn, stk[N], vis[N], top, scc[N], tot;

void tarjan(int u) {
    dfn[u] = low[u] = ++dfsn, stk[++top] = u, vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (!dfn[e[i].to]) tarjan(e[i].to), low[u] = min(low[u], low[e[i].to]);
        else if (vis[e[i].to]) low[u] = min(low[u], dfn[e[i].to]);
    if (low[u] >= dfn[u]) {
        tot++;
        while (vis[u]) scc[stk[top]] = tot, vis[stk[top--]] = 0;
    }
}

int go[N][N], id[127]; LL dp[1 << 20]; 
vector<int> G[N];

char s[N * 10]; 

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    freopen("fygon20.in", "r", stdin), freopen("fygon20.out", "w", stdout);
    int n; scanf("%d\n", &n);
    for (int i = 1; i < n; i++) {
        char c; bool flag = true; int fuck = 0;
        while ((c = getchar()) != '\n') {
            if (c == ' ' && flag) continue;
            flag = false, s[++fuck] = c;
        }
        char nw = s[5], lft = s[16], rgt = s[19]; id[nw] = i;
        if (id[lft]) adde(id[nw], id[lft]);
        if (id[rgt]) adde(id[rgt], id[nw]);
    }
    for (int i = 1; i < n; i++) if (!dfn[i]) tarjan(i);
    for (int i = 1; i < n; i++)
        for (int j = head[i]; j; j = e[j].next)
            if (scc[i] != scc[e[j].to]) G[scc[i]].push_back(scc[e[j].to]);
    for (int i = 1; i <= tot; i++) {
        go[i][i] = 1;
        for (int j = tot; j >= 1; j--)
            for (auto v : G[j]) go[j][i] |= go[v][i]; 
    }
    dp[0] = 1;
    for (int s = 0; s < 1 << tot; s++) if (dp[s])
        for (int i = 1; i <= tot; i++) if (!(s & (1 << i - 1))) {
            bool flag = true;
            for (int j = 1; j <= tot; j++) if (s & (1 << j - 1)) {
                if (go[j][i]) {
                    flag = false; break;
                }
            }
            if (flag) dp[s | (1 << i - 1)] += dp[s];
        }
    LL t = 1, all = dp[(1 << tot) - 1];
    for (int i = 1; i <= tot; i++) t *= i;
    LL g = gcd(t, all);
    printf("%d %lld/%lld", tot, all / g, t / g);   
}