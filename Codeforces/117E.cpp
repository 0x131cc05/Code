#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

struct tcurts {
    
struct node {
    int l, r, A, B, rev;
} T[N << 2];

void pushdown(int rt) {
    if (!T[rt].rev) return;
    swap(T[rt << 1].A, T[rt << 1].B), swap(T[rt << 1 | 1].A, T[rt << 1 | 1].B);
    T[rt << 1].rev ^= 1, T[rt << 1 | 1].rev ^= 1, T[rt].rev = 0;
}

void pushup(int rt) {
    T[rt].A = T[rt << 1].A + T[rt << 1 | 1].A, T[rt].B = T[rt << 1].B + T[rt << 1 | 1].B;
}

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return T[rt].A = 1, T[rt].B = 0, void();
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r), pushup(rt);
}

void update(int rt, int start, int end) {
    if (start > end) return;
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) return T[rt].rev ^= 1, swap(T[rt].A, T[rt].B), void();
    pushdown(rt);
    if (start <= mid) update(rt << 1, start, end);
    if (end > mid) update(rt << 1 | 1, start, end);
    pushup(rt);
}

int get() { return T[1].B; }

} T1, T2;

vector<int> p; int cir[N], n;

bool dfs(int u, int f, int tar) {
    if (u == tar) { p.push_back(u), cir[u] = 1; return true; }
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && dfs(e[i].to, u, tar)) 
            return p.push_back(u), cir[u] = 1, true;
    return false;
}

int all;

bool check(int i, int j) {
    bool tag = false;
    if (i > j) swap(i, j), tag = true;
    int A = j - i, B = all - (j - i);
    if (A != B) return A > B;
    int nxt1 = tag ? p[j - 1] : p[i + 1], nxt2 = tag ? p[(j + 1) % all] : p[i ? i - 1 : all - 1];
    return nxt1 > nxt2;
}

int belong[N], sz[N], son[N], fa[N];

void dfs1(int u, int f, int rt) {
    belong[u] = rt, sz[u] = 1, fa[u] = f;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && !cir[e[i].to]) {
            dfs1(e[i].to, u, rt), sz[u] += sz[e[i].to];
            if (sz[e[i].to] > sz[son[u]]) son[u] = e[i].to;
        }
}

int id[N], top[N], dfsn, dep[N];

void dfs2(int u, int f, int t) {
    top[u] = t, id[u] = ++dfsn, dep[u] = dep[f] + 1;
    if (son[u]) dfs2(son[u], u, t);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && e[i].to != son[u] && !cir[e[i].to]) dfs2(e[i].to, u, e[i].to);
}

void update1(int a, int b) { // same tree
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        T1.update(1, id[top[a]], id[a]), a = fa[top[a]];
    }
    if (dep[a] > dep[b]) swap(a, b);
    T1.update(1, id[a] + 1, id[b]); 
}

void update2(int a, int b) { // unique tree
    int A = belong[a], B = belong[b], A1 = min(A, B), B1 = max(A, B);
    update1(a, p[A]), update1(b, p[B]);
    if (check(A, B)) T2.update(1, 1, A1), T2.update(1, B1 + 1, all);
    else T2.update(1, A1 + 1, B1);
}

int F[N];

int find(int x) {
    return x == F[x] ? x : F[x] = find(F[x]);
}

int main() {
    int q, p1, p2; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) F[i] = i; 
    for (int i = 1; i <= n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        if (find(a) != find(b)) F[find(a)] = find(b), adde(a, b);
        else p1 = a, p2 = b;
    }
    T1.build(1, 1, n), dfs(p1, 0, p2), all = p.size(), T2.build(1, 1, all);
    for (int i = 0; i < p.size(); i++) 
        dfs1(p[i], 0, i), dfs2(p[i], 0, p[i]);
    while (q--) {
        int a, b; scanf("%d%d", &a, &b);
        if (belong[a] == belong[b]) update1(a, b);
        else update2(a, b);
        int t = T1.get() + T2.get() - (T2.get() == all);
        printf("%d\n", n - t);
    }
}