#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef pair<int, int> P;

int trie[2][N * 20], ncnt; vector<P> appear[N * 20];

int insert(char s[], int len) {
    int nw = 0;
    for (int i = 0; i < len; i++) {
        int c = s[i] - '0';
        nw = trie[c][nw] ? trie[c][nw] : trie[c][nw] = ++ncnt;
    }
    return nw;
}

struct node {
    int lc, rc, ct, tag, ls, rs;
} T[N * 64];

int tot;

void pushup(int rt) {
    int ls = T[rt].ls, rs = T[rt].rs;
    T[rt].lc = T[ls].lc, T[rt].rc = T[rs].rc;
    T[rt].ct = T[ls].ct + T[rs].ct - (T[ls].rc == T[rs].lc);
}

void pushdown(int rt) {
    if (T[rt].tag == -1) return;
    int ls = T[rt].ls, rs = T[rt].rs;
    T[ls].lc = T[ls].rc = T[rs].lc = T[rs].rc = T[rt].tag, T[ls].ct = T[rs].ct = 1;
    T[ls].tag = T[rt].tag, T[rs].tag = T[rt].tag, T[rt].tag = -1;
}

void build(int &rt, int l, int r) {
    rt = ++tot, T[rt].lc = T[rt].rc = T[rt].tag = -1, T[rt].ct = 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(T[rt].ls, l, mid), build(T[rt].rs, mid + 1, r);
}

void update(int rt, int l, int r, int start, int end, int x) {
    if (start <= l && r <= end) return T[rt].lc = T[rt].rc = T[rt].tag = x, T[rt].ct = 1, void();
    int ls = ++tot, rs = ++tot; 
    T[ls] = T[T[rt].ls], T[rs] = T[T[rt].rs], T[rt].ls = ls, T[rt].rs = rs;
    pushdown(rt);
    int mid = (l + r) >> 1;
    if (start <= mid) update(T[rt].ls, l, mid, start, end, x);
    if (end > mid) update(T[rt].rs, mid + 1, r, start, end, x);
    pushup(rt);
}

int lst, res;

void query(int rt, int l, int r, int start, int end) {
    if ((start <= l && r <= end) || T[rt].tag != -1) return res += T[rt].ct - (T[rt].lc == lst), lst = T[rt].rc, void(); 
    int mid = (l + r) >> 1;
    if (start <= mid) query(T[rt].ls, l, mid, start, end);
    if (end > mid) query(T[rt].rs, mid + 1, r, start, end);
}

int rt[N * 20], n, L[N], R[N], ans[N]; vector<int> qry[N * 20];

void dfs(int u, int f) {
    if (u) {
        rt[u] = rt[f];
        for (auto t : appear[u]) {
            int nw = ++tot; T[nw] = T[rt[u]], rt[u] = nw;
            update(nw, 1, n, t.first, t.second, u);
        }
    }
    for (auto t : qry[u]) lst = -2, res = 0, query(rt[u], 1, n, L[t], R[t]), ans[t] = res - 1;
    if (trie[0][u]) dfs(trie[0][u], u);
    if (trie[1][u]) dfs(trie[1][u], u);
}

int tmp[N * 20], wkr; char s[N];

int main() {
    int q; scanf("%d%d", &n, &q); set<int> stk;
    for (int i = 1; i <= n; i++) {
        static char hh[10]; scanf("%s%s", hh, s); 
        int len = strlen(s), u = insert(s, len);
        if (hh[0] == 'A') tmp[u] = i, stk.insert(u);
        else stk.erase(u), appear[u].push_back(P(tmp[u], i - 1));
    }
    for (auto t : stk) appear[t].push_back(P(tmp[t], n));
    build(rt[0], 1, n);
    for (int i = 1; i <= q; i++) 
        scanf("%s%d%d", s, &L[i], &R[i]), qry[insert(s, strlen(s))].push_back(i);
    dfs(0, 0);
    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
}