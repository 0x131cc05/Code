#include <bits/stdc++.h>
using namespace std;

const int N = 50010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

int a[N], b[N];

int res = 0;

void dfs(int u, int f, int d) {
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) a[u] -= b[e[i].to] * a[e[i].to];
    if (d & 1) res ^= a[u];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u, b[e[i].to] ? d + 1 : 1);
}

template<class T> void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
    freopen("meal.in", "r", stdin), freopen("meal.out", "w", stdout);
    int T; read(T);
    while (T--) {
        int n; read(n);
        for (int i = 1; i <= n; i++) read(a[i]);
        for (int i = 1; i <= n; i++) read(b[i]);
        ecnt = 0;
        for (int i = 1; i <= n; i++) head[i] = 0;
        for (int i = 1; i < n; i++) {
            int a, b; read(a), read(b), adde(a, b);
        }
        res = 0, dfs(1, 0, 1);
        puts(res ? "YES" : "NO");
    }
}