#include <bits/stdc++.h>
using namespace std;

const int N = 600010;

int fa[N], ch[2][N], A[N], B[N], tp[N], rev[N];

bool isroot(int u) { return (!u) || (ch[0][fa[u]] != u && ch[1][fa[u]] != u); }
bool child(int u) { return u == ch[1][fa[u]]; }
void connect(int u, int f, int son) { fa[u] = f, ch[son][f] = u; }

void pushup(int u) {
    A[u] = A[ch[0][u]] + A[ch[1][u]], B[u] = B[ch[0][u]] + B[ch[1][u]];
    tp[u] ? B[u]++ : A[u]++; // tp = 1 means right son
}

void Rev(int u) {
    swap(ch[0][u], ch[1][u]), rev[u] ^= 1;
}

void pushdown(int u) {
    if (!rev[u]) return;
    Rev(ch[0][u]), Rev(ch[1][u]), rev[u] = 0;
}

void rotate(int u) {
    int f = fa[u], ff = fa[f], tmp = child(u), tmp1 = child(f);
    if (!isroot(f)) ch[tmp1][ff] = u;
    fa[u] = ff, connect(ch[tmp ^ 1][u], f, tmp), connect(f, u, tmp ^ 1), pushup(f), pushup(u); 
}

int st[N];

void splay(int u) {
    int now = u, top = 0; st[++top] = u;
    while (!isroot(now)) st[++top] = now = fa[now];
    while (top) pushdown(st[top--]);
    for (int f; !isroot(u); rotate(u)) 
        if (!isroot(f = fa[u])) rotate(child(u) ^ child(f) ? u : f);
    pushup(u);
}

int access(int u) {
    int ls = 0;
    for (; u; u = fa[ls = u]) 
        splay(u), ch[1][u] = ls, pushup(u);
    return ls;
}

void makeroot(int u) {
    access(u), splay(u), Rev(u);
}

int rt;

int LCA(int u, int v) {
    return makeroot(rt), access(u), access(v);
}

void split(int u, int v) {
    makeroot(u), access(v), splay(v);
}

void link(int u, int v) {
    if (!v) { rt = u; return; }
    makeroot(u), fa[u] = v;
}

void cut(int u) {
    if (!u || u == rt) return;
    makeroot(rt), access(u), splay(u), fa[ch[0][u]] = 0, ch[0][u] = 0;
}

int answer(int u, int v) {
    if (u == v) return 1;
    int lca = LCA(u, v);
    split(u, v), splay(lca);
    return A[ch[0][lca]] + B[ch[1][lca]];
}

typedef pair<int, int> P;

set<P> L[N], R[N];

int id(int l, int r) {
    return L[l].lower_bound(P(r, 0)) -> second;
}

int fa1[N], ch1[2][N];

void build(int rt, int l, int r) {
    auto pos = L[l].lower_bound(P(r, 0));
    if (pos == L[l].begin()) return;
    pos--; int mid = pos -> first;
    int ls = id(l, mid), rs = id(mid + 1, r);
    A[ls] = 1, B[rs] = 1, tp[rs] = 1, fa[ls] = fa[rs] = rt;
    fa1[ls] = fa1[rs] = rt, ch1[0][rt] = ls, ch1[1][rt] = rs;
    build(ls, l, mid), build(rs, mid + 1, r);
}

bool Child(int u) { return u == ch1[1][fa1[u]]; }
void Connect(int u, int f, int son) {
    fa1[u] = f, ch1[son][f] = u;
}

void modify(int u, int t) {
    if (t == tp[u]) return;
    tp[u] = t, splay(u);
}

int tl[N], tr[N];

void push(int u) {
    L[tl[u]].erase(P(tr[u], u)), R[tr[u]].erase(P(tl[u], u));
    tl[u] = tl[ch1[0][u]], tr[u] = tr[ch1[1][u]];
    L[tl[u]].insert(P(tr[u], u)), R[tr[u]].insert(P(tl[u], u));
}

void Rotate(int u) {
    if (u == rt) return;
    int f = fa1[u], ff = fa1[f], tmp = Child(u), tmp1 = Child(f); cut(f);
    int wkr = ch1[tmp ^ 1][u];
    if (wkr) cut(wkr);
    modify(wkr, tmp), modify(f, tmp ^ 1), modify(u, tmp1);
    Connect(wkr, f, tmp), Connect(f, u, tmp ^ 1), Connect(u, ff, tmp1), link(u, ff);
    push(f), push(u);
    if (wkr) link(wkr, f);
}

int main() {
    freopen("c2.in", "r", stdin), freopen("c.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n * 2 - 1; i++) 
        scanf("%d%d", &tl[i], &tr[i]), L[tl[i]].insert(P(tr[i], i)), R[tr[i]].insert(P(tl[i], i));
    build(rt = id(1, n), 1, n);
    while (m--) {
        int op, a, b; scanf("%d%d", &op, &a);
        if (op == 1) Rotate(a);
        else {
            scanf("%d", &b);
            int u = (--L[a].upper_bound(P(b + 1, 0))) -> second;
            int v = R[b].lower_bound(P(a, 0)) -> second;
            printf("%d\n", answer(u, v));
        }
    }
}   
