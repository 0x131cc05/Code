#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int fa[N], ch[2][N], sum[N], L[N], R[N], val[N], rev[N]; multiset<int> s[N];

inline int isroot(int u) { return (u != ch[0][fa[u]] && u != ch[1][fa[u]]) || !u; }
inline int child(int u) { return u == ch[1][fa[u]]; }
inline void connect(int u, int f, int son) { fa[u] = f, ch[son][f] = u; }

inline void pushup(int u) {
    sum[u] = sum[ch[0][u]] + sum[ch[1][u]] + val[u]; int t = 0;
    if (s[u].size()) t = max(t, *s[u].rbegin());
    L[u] = max(L[ch[0][u]], sum[ch[0][u]] + val[u] + max(t, L[ch[1][u]]));
    R[u] = max(R[ch[1][u]], sum[ch[1][u]] + val[u] + max(t, R[ch[0][u]]));
}

inline void Rev(int u) {
    swap(L[u], R[u]), swap(ch[0][u], ch[1][u]), rev[u] ^= 1;
}

inline void pushdown(int u) {
    if (rev[u]) Rev(ch[0][u]), Rev(ch[1][u]), rev[u] = 0;
}

inline void rotate(int u) {
    int f = fa[u], ff = fa[f], tmp = child(u), tmp1 = child(f);
    if (!isroot(f)) connect(u, ff, tmp1);
    fa[u] = ff, connect(ch[tmp ^ 1][u], f, tmp), connect(f, u, tmp ^ 1), pushup(f), pushup(u);
}

int stk[N], top;

inline void splay(int u) {
    stk[top = 1] = u; int t = u;
    while (!isroot(t)) stk[++top] = t = fa[t];
    while (top) pushdown(stk[top--]);
    for (int f; !isroot(u); rotate(u))
        if (!isroot(f = fa[u]))
            rotate(child(u) ^ child(f) ? u : f);
    pushup(u);
}

inline void access(int u) {
    for (int ls = 0; u; u = fa[ls = u]) {
        splay(u); 
        if (ch[1][u]) s[u].insert(L[ch[1][u]]);
        if (ls) s[u].erase(s[u].find(L[ls]));
        ch[1][u] = ls, pushup(u);
    }
}

inline void makeroot(int u) {
    access(u), splay(u), Rev(u);
}

int p[N];

int main() {
//    freopen("T1.in", "r", stdin), freopen("T1.out", "w", stdout);
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 2; i <= n; i++) scanf("%d", &p[i]);
    L[0] = R[0] = -1e9;
    for (int i = 1; i <= n; i++) 
        scanf("%d", &val[i]), L[i] = R[i] = sum[i] = val[i];
    for (int i = n; i >= 2; i--) 
        s[p[i]].insert(L[i]), L[p[i]] = R[p[i]] = max(L[p[i]], val[p[i]] + L[i]), fa[i] = p[i];
    for (int i = 1; i <= q; i++) {
        int op, a, b; scanf("%d%d", &op, &a);
        if (op == 1) makeroot(a), printf("%d\n", L[a]); 
        else scanf("%d", &b), makeroot(a), val[a] = b, pushup(a);
    }
    return 0;
}
