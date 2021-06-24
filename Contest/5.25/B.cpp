#include <bits/stdc++.h>
using namespace std;

const int N = 300010;

int fa[N], ch[2][N];

inline void connect(int u, int f, int son) {fa[u] = f, ch[son][f] = u;}

inline bool child(int u) {return u == ch[1][fa[u]];}

inline bool isroot(int u) {return (u != ch[0][fa[u]] && u != ch[1][fa[u]]) || !u;}

inline void rotate(int u) {
    int f = fa[u], ff = fa[f], tmp = child(u), tmp1 = child(f);
    if (!isroot(f)) connect(u, ff, tmp1);
    fa[u] = ff, connect(ch[tmp ^ 1][u], f, tmp), connect(f, u, tmp ^ 1);
}

inline void splay(int u) {
    for (int f;!isroot(u);rotate(u))
        if (!isroot(f = fa[u])) 
            rotate(child(u) ^ child(f) ? u : f);
}

inline int access(int u) {
    int ls = 0;
    for (; u; u = fa[ls = u]) 
        splay(u), ch[1][u] = ls;
    return ls;
}

inline void link(int u, int f) {splay(u), fa[u] = f;}

inline void cut(int u) {
    access(u), splay(u), ch[0][u] = fa[ch[0][u]] = 0;
}

inline int findroot(int u) {
    access(u), splay(u);
    while (ch[0][u]) u = ch[0][u];
    return u;
}

int val[N], F[N];

int main() {
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
    while (q--) {
        int op, a, b; scanf("%d%d%d", &op, &a, &b);
        if (op == 0) {
            val[a] = b;
            if (F[a]) cut(a);
            F[a] = 0;
        } else if (op == 1) {
            cut(a), link(a, F[a] = b);
        } else {
            long long res = 0;
            for (int i = a; i <= b; i++) res += val[findroot(i)];
            printf("%lld\n", res);
        }
    }
}

