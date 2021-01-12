#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

int fa[N], appear[N];

LL t[N], a[N]; int d[N]; // 每个点的权值以及度数

multiset<LL> s[N]; // 每个点的所有儿子(不考虑这个点的影响)

inline LL Affection(int u) { // u 对其邻居的影响
    return t[u] / (d[u] + 1);
}

inline LL Self(int u) { // u 对自己的影响
    return t[u] - d[u] * (t[u] / (d[u] + 1));
}

inline void Erase(int target, LL x) {
    s[target].erase(s[target].find(x));
}

inline void Push(int target, LL x) {
    s[target].insert(x);
}

inline void Delete(int u) {
    if (!appear[u] || !s[u].size()) return;
    appear[u] = 0, Erase(0, *s[u].begin() + Affection(u)), Erase(0, *s[u].rbegin() + Affection(u));
}

inline void Insert(int u) {
    if (appear[u] || !s[u].size()) return;
    appear[u] = 1, Push(0, *s[u].begin() + Affection(u)), Push(0, *s[u].rbegin() + Affection(u));
}

/**
 * a[fa[u]], s[fa[u]] 更新 u 的贡献
 * s[fa[fa[u]]] 更新 a[fa[u]]
 * 更新 fa[u] 的度数, 更新 fa[u] 对自己以及 a[fa[fa[u]]] 的贡献 
 * s[fa[fa[fa[u]]]] 更新 a[fa[fa[u]]]
 */
inline void process(int u, int diff) {
    int f = fa[u], ff = fa[f], fff = fa[ff];
    Delete(f), Delete(ff), Delete(fff);
    Erase(ff, a[f]), Erase(fff, a[ff]);
    if (diff == -1) Erase(f, a[u]);
    a[f] += diff * Affection(u);
    a[ff] -= Affection(f), a[f] -= Self(f), d[f] += diff;
    a[ff] += Affection(f), a[f] += Self(f);
    Push(fff, a[ff]), Push(ff, a[f]);
    if (diff == 1) Push(f, a[u]);
    Insert(f), Insert(ff), Insert(fff);        
}

int main() {
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%lld", &t[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &fa[i]), d[i]++, d[fa[i]]++;
    for (int i = 1; i <= n; i++) a[i] += Self(i), a[fa[i]] += Affection(i);
    for (int i = 1; i <= n; i++) Push(fa[i], a[i]);
    for (int i = 1; i <= n; i++) Insert(i);
    while (q--) {
        int op, A, B; scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &A, &B);
            process(A, -1), fa[A] = B, process(A, 1);
        } else if (op == 2) {
            scanf("%d", &A);
            printf("%lld\n", a[A] + Affection(fa[A]));
        } else printf("%lld %lld\n", *s[0].begin(), *s[0].rbegin());
    }
    return 0;
}
