#include <bits/stdc++.h>
using namespace std;

const int N = 400010;

typedef long long LL;

int tot;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

LL val[N], tree1[N], tree2[N];

void upd(LL v[], int x, int y) {
    for (; x <= tot; x += x & -x) v[x] += y;
}

LL que(LL v[], int x) {
    LL res = 0;
    for (; x; x -= x & -x) res += v[x];
    return res;
}

void upd(int l, int r) {
    upd(tree2, r + 1, -1), upd(tree2, l, 1);
    upd(tree1, l, -val[l - 1]), upd(tree1, r + 1, val[r]);
}

LL que(int r) {
    return que(tree2, r) * val[r] + que(tree1, r);
}

LL que(int l, int r) {
    return que(r) - que(l - 1);
}

int dfn[N], dfsn, dep[N], top[N], fa[19][N], son[N], sz[N];

void dfs1(int u, int f) {
    dep[u] = dep[f] + 1, sz[u] = 1, fa[0][u] = f;
    for (int i = 1; i < 19; i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs1(e[i].to, u), sz[u] += sz[e[i].to];
            if (sz[e[i].to] > sz[son[u]]) son[u] = e[i].to;
        }
}

int LCA(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 18; i >= 0; i--) if (dep[fa[i][a]] >= dep[b]) a = fa[i][a];
    if (a == b) return a;
    for (int i = 18; i >= 0; i--) if (fa[i][a] != fa[i][b]) a = fa[i][a], b = fa[i][b];
    return fa[0][a];
}

int len[N];

void dfs2(int u, int t) {
    dfn[u] = ++dfsn, top[u] = t, val[dfsn] = len[u];
    if (son[u]) dfs2(son[u], t);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != fa[0][u] && e[i].to != son[u]) dfs2(e[i].to, e[i].to);
}

void update(int u) {
    while (top[u] != 2) 
        upd(dfn[top[u]], dfn[u]), u = fa[0][top[u]];
    upd(dfn[2], dfn[u]);
}

LL query(int u) {
    LL res = 0;
    while (top[u] != 2) 
        res += que(dfn[top[u]], dfn[u]), u = fa[0][top[u]];
    return res + que(dfn[2], dfn[u]);
}

struct PT {
    int fail[N], len[N], ncnt, last, ch[N][26], s[N];

    int newnode(int l) {
        return len[++ncnt] = l, ncnt;
    }

    int getfail(int x, int pos) {
        while (s[pos - len[x] - 1] != s[pos]) x = fail[x];
        return x;
    }

    void init() {
        fail[0] = 1, len[1] = -1, last = len[0] = 0, ncnt = 1;
    }

    void extend(int c, int pos) {
        int p = getfail(last, pos);
        if (!ch[p][c]) {
            int now = newnode(len[p] + 2);
            fail[now] = ch[getfail(fail[p], pos)][c];
            ch[p][c] = now;
        } 
        last = ch[p][c];
    }
} T1, T2;

struct tcurts {
    int op, a, b, c, d;
} wkr[N];

vector<int> L, R, S;

int s[N];

int pos1[N], fuck[N];

int jmp[19][N];

int find(int u, int l) {
    for (int i = 18; i >= 0; i--)
        if (len[jmp[i][u]] > l) u = jmp[i][u];
    u = jmp[0][u];
    return u;
}

int main() {
    int n, q; scanf("%d%d", &n, &q), S.resize(n);
    for (int i = 0; i < n; i++) scanf("%d", &S[i]);
    for (int i = 1; i <= q; i++) {
        static char tmp[15]; scanf("%s", tmp + 1);
        if (tmp[1] == 'a') {
            scanf("%d", &wkr[i].a); int tp = tmp[4] == 'r';
            if (tp) R.push_back(wkr[i].a);
            else L.push_back(wkr[i].a);
            wkr[i].op = tp;
        } else {
            scanf("%d%d%d%d", &wkr[i].a, &wkr[i].b, &wkr[i].c, &wkr[i].d);
            wkr[i].op = 2 + (tmp[6] == 'r');
        }
    }
    int all = 0;
    for (int i = (int)L.size() - 1; i >= 0; i--) s[++all] = L[i];
    for (int i = 0; i < n; i++) s[++all] = S[i];
    for (int i = 0; i < R.size(); i++) s[++all] = R[i];
    T1.init(), T2.init();
    for (int i = 1; i <= all; i++)
        T1.s[i] = T2.s[all - i + 1] = s[i];
    for (int i = 1; i <= all; i++) 
        T1.extend(s[i], i), pos1[i] = T1.last + 1;
    for (int i = 1; i <= all; i--)
        T2.extend(s[all - i + 1], i), fuck[all - i + 1] = T2.len[T2.last];
    for (int i = 1; i <= T1.ncnt; i++) {
        len[i + 1] = max(0, T1.len[i]);
        int f = T1.fail[i];
        if (f != -1) adde(i + 1, f + 1), jmp[0][i + 1] = f + 1;
    }
    dfs1(2, 0), tot = dfsn, dfs2(2, 2);
    for (int t = 1; t < 19; t++)
        for (int i = 1; i <= tot; i++)
            jmp[t][i] = jmp[t - 1][jmp[t - 1][i]];
    for (int i = 1; i <= tot; i++) val[i] += val[i - 1];
    int offset = L.size();
    for (int i = 1; i <= q; i++) {
        if (wkr[i].op <= 1) {
            if (wkr[i].op == 0) offset--;
            n++;
        } else {
            int A = 0, B = 0;
            int a = wkr[i].a + offset, b = wkr[i].b + offset, c = wkr[i].c + offset, d = wkr[i].d + offset;
            if (wkr[i].op == 2) {
                A = find(pos1[b], b - a + 1);
                B = find(pos1[d], d - c + 1);
            } else {
                A = find(pos1[a + fuck[a] - 1], b - a + 1);
                B = find(pos1[c + fuck[c] - 1], d - c + 1);
            }
            LL res = query(A) + query(B) - query(LCA(A, B));
            printf("%lld\n", res);
        }
    }
}