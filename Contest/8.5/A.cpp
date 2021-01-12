#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
typedef long long LL;

template<class T> void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

struct edge {
    int to, next;
} e[N * 2];
int head[N], ecnt;
void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

LL ans;
struct Trie {
    int trie[N * 61][2], ncnt;
    void clear() { ncnt = 0, ans = 0, trie[0][0] = trie[0][1] = 0; }
    void insert(LL v) {
        int nw = 0;
        for (int i = 60; i >= 0; i--) {
            int c = v >> i & 1;
            if (!trie[nw][c]) trie[nw][c] = ++ncnt, trie[ncnt][0] = trie[ncnt][1] = 0; 
            nw = trie[nw][c];
        }
    }
    LL query(LL v) {
        int nw = 0; LL res = 0;
        for (int i = 60; i >= 0; i--) {
            int c = v >> i & 1;
            if (trie[nw][!c]) res |= 1ll << i, nw = trie[nw][!c];
            else nw = trie[nw][c]; 
        }
        return res;
    }
} T;

LL val[N], res[N]; 
void update(int u) {
    ans = max(ans, T.query(val[u])), T.insert(val[u]);
}
void push(int u, int f) {
    update(u);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) push(e[i].to, u);
}

int ct[N];
void dfs(int u, int f) {
    ct[u]--, res[u] = ans;
    int target = 0;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && ct[e[i].to]) {
            target = e[i].to; break;
        }
    if (!target) return;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && e[i].to != target)
            push(e[i].to, u);
    update(u), dfs(target, u);
}

int fa[N];
int main() {
    int n; read(n);
    for (int i = 2; i <= n; i++) read(fa[i]), adde(fa[i], i);
    for (int i = 1; i <= n; i++) read(val[i]);
    int a = 0, b = 0;
    for (int i = 1; i <= n; i++) {
        LL nw = T.query(val[i]);
        if (nw >= ans) ans = nw, a = i;
        T.insert(val[i]);
    }
    for (int i = 1; i <= n; i++) 
        if ((val[i] ^ val[a]) == ans) b = i;
    for (int p = a; p; p = fa[p]) ct[p]++;
    for (int p = b; p; p = fa[p]) ct[p]++;
    for (int i = 1; i <= n; i++) if (!ct[i]) res[i] = ans;
    T.clear(), dfs(1, 0), T.clear(), dfs(1, 0);
    for (int i = 1; i <= n; i++) printf("%lld ", res[i]);
}