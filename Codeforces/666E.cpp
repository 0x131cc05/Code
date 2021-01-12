#include <bits/stdc++.h>
using namespace std;

const int N = 600010;

typedef pair<int, int> P;

int link[N * 2] = {-1}, ch[N * 2][26], len[N * 2], ncnt, last;

inline int insert(char c) {
    if (ch[last][c - 'a'] && len[ch[last][c - 'a']] == len[last] + 1) return last = ch[last][c - 'a'];
    int nw = ++ncnt, p = last; len[nw] = len[p] + 1;
    while (~p && !ch[p][c - 'a']) ch[p][c - 'a'] = nw, p = link[p];
    if (p == -1) return last = nw;
    int q = ch[p][c - 'a'];
    if (len[q] == len[p] + 1) return link[nw] = q, last = nw;
    int clone = p == last ? nw : ++ncnt; memcpy(ch[clone], ch[q], sizeof(ch[q])), len[clone] = len[p] + 1;
    link[clone] = link[q], link[q] = clone;
    if (clone != nw) link[nw] = clone;
    while (~p && ch[p][c - 'a'] == q) ch[p][c - 'a'] = clone, p = link[p];
    return last = nw;
}

struct edge {
    int to, next;
} e[N * 4];

int head[N * 2], ecnt;

inline void adde(int from, int to) {
//    cout << "adde: " << from << ' ' << to << endl;
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int fa[N * 2][20];

void dfs(int u, int f) {
    fa[u][0] = f;
    for (int i = 1; i <= 19; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) 
            dfs(e[i].to, u);
}

inline int jump(int u, int l) {
    for (int i = 19; i >= 0; i--)
        if (len[fa[u][i]] >= l) u = fa[u][i];
    return u;
}

int ls[N * 16], rs[N * 16], tot, n;

struct WEN { int val, pos; } wkr[N * 16];

inline WEN merge(WEN a, WEN b) {
    return a.val >= b.val ? a : b;
}

queue<int> buff;

inline int apply() {
    int t;
    if (buff.size()) t = buff.front(), buff.pop();
    else t = ++tot;
    return wkr[t] = (WEN){ 0, 0 }, ls[t] = rs[t] = 0, t;
}

void insert(int &rt, int l, int r, int x) {
    if (!rt) rt = apply();
//    if (l == 1 && r == n) cout << "insert: " << rt << ' ' << x << endl;
    if (l == r) return wkr[rt] = (WEN){ wkr[rt].val + 1, l }, void();
    int mid = (l + r) >> 1;
    if (x <= mid) insert(ls[rt], l, mid, x);
    else insert(rs[rt], mid + 1, r, x);
    wkr[rt] = merge(wkr[ls[rt]], wkr[rs[rt]]);
}

WEN query(int rt, int l, int r, int start, int end) {
    if (!rt) return (WEN){ 0, 0 };
    if (start <= l && r <= end) return wkr[rt];
    int mid = (l + r) >> 1;
    if (end <= mid) return query(ls[rt], l, mid, start, end);
    if (start > mid) return query(rs[rt], mid + 1, r, start, end);
    return merge(query(ls[rt], l, mid, start, end), query(rs[rt], mid + 1, r, start, end));
}

void merge(int &x, int y, int l, int r) {
    if (!x || !y) return x |= y, void();
    buff.push(y);
    if (l == r) return wkr[x] = (WEN){ wkr[x].val + wkr[y].val, l }, void();
    int mid = (l + r) >> 1;
    merge(ls[x], ls[y], l, mid), merge(rs[x], rs[y], mid + 1, r), wkr[x] = merge(wkr[ls[x]], wkr[rs[x]]);
}

vector<P> q[N * 2], appear[N * 2]; int RT[N * 2], L[N], R[N]; WEN ans[N];

void dfs1(int u, int f) {
    sort(q[u].rbegin(), q[u].rend()), sort(appear[u].rbegin(), appear[u].rend());
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) 
            dfs1(e[i].to, u), merge(RT[u], RT[e[i].to], 1, n);
    int cur = 0;
//    cout << "dfs: " << u << endl;
//    for (auto t : appear[u]) printf("(%d, %d) ", t.first, t.second);
//    cout << endl;
    for (auto t : q[u]) {
        while (cur < appear[u].size() && appear[u][cur].first >= t.first) 
            insert(RT[u], 1, n, appear[u][cur].second), cur++;
        ans[t.second] = query(RT[u], 1, n, L[t.second], R[t.second]);
    }
    while (cur < appear[u].size()) 
        insert(RT[u], 1, n, appear[u][cur].second), cur++;
}

char s[N];

int zjk[N];

int main() {
    scanf("%s", s + 1); int n = strlen(s + 1);
    for (int i = 1; i <= n; i++) 
        zjk[i] = insert(s[i]);
    int m; scanf("%d", &m), ::n = m + 1; 
    for (int i = 1; i <= m; i++) {
        last = 0, scanf("%s", s + 1), n = strlen(s + 1);
        for (int j = 1; j <= n; j++)
            appear[insert(s[j])].push_back(P(j, i));
    }
    for (int i = ncnt; i >= 1; i--) adde(link[i], i);
    dfs(0, 0);
    int t; scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        int l, r; scanf("%d%d%d%d", &L[i], &R[i], &l, &r);
        int p = jump(zjk[r], r - l + 1);
//        cout << "at: " << p << endl;
        q[p].push_back(P(r - l + 1, i));
    }
    dfs1(0, 0);
    for (int i = 1; i <= t; i++) {
        if (ans[i].val == 0) printf("%d %d\n", L[i], 0);
        else printf("%d %d\n", ans[i].pos, ans[i].val);
    }
}
