#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res  = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int l[N], r[N], fa[N], ch[2][N], sz[N], rev[N];

int child(int u) { return u == ch[1][fa[u]]; }
void connect(int u, int f, int son) { fa[u] = f, ch[son][f] = u; }
void tag(int u) { 
    if (!u) return;
    swap(ch[0][u], ch[1][u]), swap(l[u], r[u]), rev[u] ^= 1; 
}
int len(int u) { return abs(l[u] - r[u]) + 1; }

void pushdown(int u) { if (rev[u]) tag(ch[0][u]), tag(ch[1][u]), rev[u] = 0; }
void pushup(int u) { sz[u] = len(u) + sz[ch[0][u]] + sz[ch[1][u]]; }

void rotate(int u) {
    int f = fa[u], ff = fa[f], tmp = child(u), tmp1 = child(f); 
    pushdown(f), pushdown(u);
    connect(ch[tmp ^ 1][u], f, tmp), connect(f, u, tmp ^ 1), connect(u, ff, tmp1);
    pushup(f), pushup(u);
} 

void splay(int u, int t = 0) {
    for (int f; fa[u] != t; rotate(u)) 
        if (fa[f = fa[u]] != t) rotate(child(u) ^ child(f) ? u : f);
}

int p, tmp;

void find(int u, int x) { // <= x
    if (!u) return;
    pushdown(u);
    if (x <= sz[ch[0][u]]) return find(ch[0][u], x), void();
    int hh = sz[u] - sz[ch[1][u]];
    if (x > hh) find(ch[1][u], x - hh);
    else p = u, tmp = x - sz[ch[0][u]];
}

int ncnt;

void split(int pos) { // pos - 1, pos
    p = 0, tmp = 0;
    find(ch[0][0], pos);
    splay(p);
    assert(tmp);
    if (tmp == 1) return;
    int a = tmp - 1, b = len(p) - (tmp - 1);
    int t = ch[1][p];
    assert(t);
    while (233) {
        pushdown(t);
        if (ch[0][t]) t = ch[0][t];
        else break;
    }
    splay(t, p);
    int step = l[p] < r[p] ? 1 : -1;
    int mid = l[p] + a * step, q = r[p]; 
    r[p] = mid - step;
    ncnt++, l[ncnt] = mid, r[ncnt] = q;
    connect(ncnt, t, 0), pushup(ncnt), pushup(t), pushup(p);
}

int split(int L, int R) {
    find(ch[0][0], L - 1), splay(p); int hh = p;
    assert(p);
    find(ch[0][0], R + 1);
    splay(p, hh);
    assert(p);
    return ch[0][p];
}

void update0(int l, int r) {
    l++, r++, split(l), split(r + 1);
    int nw = split(l, r);
    fa[nw] = ch[0][fa[nw]] = 0, pushup(ch[1][ch[0][0]]), pushup(ch[0][0]);
    find(ch[0][0], 2), splay(p), rotate(ch[0][p]);
    connect(nw, p, 0), pushup(p), pushup(ch[0][0]);
}

vector<int> sa;

int res = 1;

void print(int u) {
    if (!u) return;
    pushdown(u);
    print(ch[0][u]);
    if (l[u] && r[u]) {
        if (l[u] == r[u]) sa.push_back(l[u]);
        else {
            int t = len(u); res = (LL)res * Pow(2, t - 2) % mod;
            sa.push_back(l[u]), sa.push_back(r[u]);
        }
    }
    print(ch[1][u]);
}

void update1(int l, int r) {
    l++, r++, split(l), split(r + 1);
    int nw = split(l, r); tag(nw);
}

void init(int n) {
    ncnt = 3; l[2] = 1, r[2] = n;
    ch[0][0] = 3, ch[0][3] = 2, ch[0][2] = 1, fa[1] = 2, fa[2] = 3;
    pushup(1), pushup(2), pushup(3);
}

int A[N * 2], B[N * 2];

int main() {
    freopen("sa.in", "r", stdin), freopen("sa.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m), init(n);
    for (int i = 1; i <= m; i++) {
        int op, a, b; scanf("%d%d%d", &op, &a, &b);
        if (op == 0) update0(a, b);
        else update1(a, b);
    }
    print(ch[0][0]);
    vector<int> val = sa;
    sort(val.begin(), val.end()), val.resize(unique(val.begin(), val.end()) - val.begin());
    for (auto &t : sa) t = lower_bound(val.begin(), val.end(), t) - val.begin() + 1;
    int all = sa.size();
    for (int i = 1; i <= all; i++) A[i] = sa[i - 1];
    for (int i = 1; i <= all; i++) B[A[i]] = i;
    for (int i = 1; i < all; i++) {
        if (B[A[i] + 1] < B[A[i + 1] + 1])
            res = res * 2 % mod;
    }
    printf("%d\n", res);
}