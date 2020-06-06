#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

int d[19][N], fa[19][N], vis[N], sz[N], dep[N];

int getsz(int u) {
    sz[u] = 1, vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) sz[u] += getsz(e[i].to);
    return vis[u] = 0, sz[u]; 
}

int getrt(int u, int tot) {
    vis[u] = 1;
    for (int i = head[u], tmp; i; i = e[i].next)
        if (!vis[e[i].to] && (tmp = getrt(e[i].to, tot))) 
            return vis[u] = 0, tmp;
    return vis[u] = 0, sz[u] >= (tot >> 1) ? u : 0;
}

void dfs(int u, int layer, int t, int dis) {
    fa[layer][u] = t, d[layer][u] = dis, vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) dfs(e[i].to, layer, t, dis + e[i].w);
    vis[u] = 0;
}

void divide(int layer, int u) {
    u = getrt(u, getsz(u)), dep[u] = layer, dfs(u, layer, u, 0), vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) divide(layer + 1, e[i].to);
}

struct WEN {

priority_queue<int> A, B;

void push(int x) { if (x != -1e9) A.push(x); }

void erase(int x) { if (x != -1e9) B.push(x); }

int top() {
    if (!size()) return -1e9;
    while (B.size() && A.top() == B.top()) A.pop(), B.pop();
    return A.top();
}

int second() {
    if (size() < 2) return -1e9;
    int t1 = top(); erase(t1); int ans = top(); push(t1);
    return ans;
}

int size() { return A.size() - B.size(); }

} A[N], B[N], wkr;

int col[N];

inline void check(int u, int type) {
    if (A[u].size() < 2) return;
    int t1 = A[u].top(), t2 = A[u].second();
    type ? wkr.push(t1 + t2) : wkr.erase(t1 + t2);
}

int tot;

inline void flip(int u) {
    tot -= col[u];
    int type = col[u] ^= 1, t = dep[u];
    tot += col[u];
    for (int i = t; i >= 1; i--) {
        int dis = d[i][u], f = fa[i][u], ls = fa[i + 1][u];
        check(f, 0);
        if (type) {
            if (ls) {
                int fuck = B[ls].top() >= dis;
                if (!fuck) A[f].erase(B[ls].top());
                B[ls].push(dis);
                if (!fuck) A[f].push(B[ls].top());
            } else A[f].push(0);
        } else {
            if (ls) {
                int fuck = B[ls].top() > dis;
                if (!fuck) A[f].erase(B[ls].top());
                B[ls].erase(dis);
                if (!fuck) A[f].push(B[ls].top());
            }
            else A[f].erase(0);
        }
        check(f, 1);
    }
}

template<class T> inline void read(T &x) {
    x = 0; char c = getchar(); int f = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (f) x = -x;
}

char s[10];

int main() {
    int n; read(n);
    for (int i = 1, a, b, c; i < n; i++) 
        read(a), read(b), read(c), adde(a, b, c);
    divide(1, 1), tot = n;
    for (int i = 1; i <= n; i++) {
        col[i] = 1;
        for (int j = dep[i] - 1; j >= 1; j--) 
            B[fa[j + 1][i]].push(d[j][i]);
    }
    for (int i = 1; i <= n; i++) {
        if (dep[i] > 1) A[fa[dep[i] - 1][i]].push(B[i].top());
        A[i].push(0);
    }
    for (int i = 1; i <= n; i++) check(i, 1);
    int q; read(q);
    while (q--) {
        int a; scanf("%s", s + 1);
        if (s[1] == 'A') {
            if (tot == 1) puts("0");
            else if (wkr.size()) printf("%d\n", max(0, wkr.top()));
            else puts("They have disappeared.");
        } else read(a), flip(a);
    }
    return 0;
}
