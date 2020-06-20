#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int perfix[N], F[N], G[N], sum[N];

int count1(int u, int f, int x) {
    if (u > x) return 0;
    int res = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) res += count1(e[i].to, u, x);
    return res;
}

void dfs(int u, int f) {
    perfix[u] = max(u, perfix[f]);
    if (perfix[u] > perfix[f]) {
        for (int i = head[u]; i; i = e[i].next)
            if (e[i].to != f) {
                F[e[i].to] = count1(e[i].to, u, u);
                G[e[i].to] = count1(e[i].to, u, perfix[f]), sum[u] += G[e[i].to];
            }
    }
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u); 
}

int ans[N];

void Just_DOIT(int u, int f) {
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            ans[e[i].to] = ans[u];
            if (u > perfix[f]) ans[e[i].to] = ans[e[i].to] - G[e[i].to] + F[e[i].to];
            if (e[i].to > perfix[u]) ans[e[i].to] += sum[e[i].to] + 1;
            Just_DOIT(e[i].to, u); 
        }
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++)
        scanf("%d%d", &a, &b), adde(a, b);
    dfs(1, 0), Just_DOIT(1, 0);
    for (int i = 2; i <= n; i++) printf("%d ", ans[i]);
}