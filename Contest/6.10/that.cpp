#include <bits/stdc++.h>
using namespace std;

const int N = 40010;
const int M = 10000010;
const int P = 131;
const int mod = 1e9 + 7;

typedef long long LL;

int ch[N][26], link[N], len[N], ncnt, last;

inline void clr(int u) {
    memset(ch[u], 0, sizeof(ch[u])), link[u] = len[u] = 0;
}

inline void init() {
    ncnt = 0, clr(0), link[0] = -1, len[0] = 0, last = 0;
}

inline int insert(char c) {
    int cur = ++ncnt, p = last; clr(ncnt), len[cur] = len[last] + 1;
    while (~p && !ch[p][c - 'a']) ch[p][c - 'a'] = cur, p = link[p];
    if (p == -1) return link[cur] = 0, last = cur;
    int q = ch[p][c - 'a'];
    if (len[q] == len[p] + 1) return link[cur] = q, last = cur;
    int clone = ++ncnt; clr(ncnt);
    link[clone] = link[q], link[q] = link[cur] = clone, memcpy(ch[clone], ch[q], sizeof(ch[q])), len[clone] = len[p] + 1;
    while (~p && ch[p][c - 'a'] == q) ch[p][c - 'a'] = clone, p = link[p];
    return last = cur;
}

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
//    cout << "adde: " << from << ' ' << to << endl;
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int ls[M], rs[M], ct[M], sum[M], tot, n;

inline void clr1(int u) {
    ls[u] = rs[u] = ct[u] = sum[u] = 0;
}

void update(int &rt, int l, int r, int pos, int delta) {
    if (!rt) rt = ++tot, clr1(rt);
//    if (l == 1 && r == n) cout << "update: " << rt << ' ' << pos << ' ' << delta << endl;
    ct[rt] += delta, sum[rt] += pos * delta;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) update(ls[rt], l, mid, pos, delta);
    else update(rs[rt], mid + 1, r, pos, delta);
}

int st, ed, type;

int query(int rt, int l, int r) {
    if (!rt) return 0;
    if (st <= l && r <= ed) {
        if (type) return sum[rt];
        return ct[rt];
    }
    int mid = (l + r) >> 1, res = 0;
    if (st <= mid) res += query(ls[rt], l, mid);
    if (ed > mid) res += query(rs[rt], mid + 1, r);
    return res;
}

inline int query(int rt, int l, int r, int start, int end, int type) {
    ::st = start, ::ed = end, ::type = type;
    return query(rt, l, r);
}

set<int> endpos[N];

int RT[N], RT1[N];

inline void insert(int u, int t) {
//    cout << "insert: " << u << ' ' << RT1[u] << ' ' << t << endl;
    int A = -1, B = -1, l = 0, r = 0;
    auto pos = endpos[RT1[u]].upper_bound(t);
    if (pos != endpos[RT1[u]].end()) r = *pos, B = r - t;
    if (pos != endpos[RT1[u]].begin()) pos--, l = *pos, A = t - l;
//    cout << A << ' ' << B << ' ' << l << ' ' << r << endl;
    if (l && r) update(RT[u], 1, n, r - l, -1);
    if (~A) update(RT[u], 1, n, A, 1);
    if (~B) update(RT[u], 1, n, B, 1);
}

inline void merge(int u, int v) {
    for (auto t : endpos[v]) 
        if (t <= n) insert(u, t), endpos[RT1[u]].insert(t);
    endpos[v].clear();
}

int appear[N], ans[N], k, wkr[N];

void dfs(int u, int f) {
    int v = 0, mx = 0; RT1[u] = u, RT[u] = 0, endpos[u].clear();
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u);
            if (endpos[RT1[e[i].to]].size() >= mx) 
                mx = endpos[RT1[e[i].to]].size(), v = e[i].to;
        }
//    cout << "process: " << u << ' ' << f << endl;
//    cout << u << ' ' << len[u] << ' ' << appear[u] << endl;
    if (v) RT[u] = RT[v], RT1[u] = RT1[v];
    endpos[RT1[u]].insert(n + 1);
    if (appear[u]) insert(u, appear[u]), endpos[RT1[u]].insert(appear[u]);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && e[i].to != v) 
            merge(u, RT1[e[i].to]);
//    for (auto t : endpos[RT1[u]]) cout << t << ' ';
//    cout << endl;
    int l = len[f] + 1, r = len[u], tp = -1, res = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int fuck = query(RT[u], 1, n, 1, mid, 1) + query(RT[u], 1, n, mid + 1, n, 0) * mid;
//        cout << "check: " << mid << ' ' << fuck << endl;
        if (fuck >= k) tp = fuck, res = mid, r = mid - 1;
        else l = mid + 1;
    }
    wkr[u] = *endpos[RT1[u]].begin();
    if (tp == k) ans[u] = res;
}

int pw[N], hsh[N];

inline void gethash(char s[], int n) {
    pw[0] = 1;
    for (int i = 1; i <= n; i++) 
        hsh[i] = ((LL)hsh[i - 1] * P + s[i] - 'a') % mod, pw[i] = (LL)pw[i - 1] * P % mod;
}

inline int get(int l, int r) {
    return (hsh[r] - (LL)hsh[l - 1] * pw[r - l + 1] % mod + mod) % mod;
}

inline int LCP(int a, int b) {
    int l = 0, r = min(n - a + 1, n - b + 1), mid, res = 0;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (get(a, a + mid - 1) == get(b, b + mid - 1)) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    return res;
}

char s[N];

int main() {
    freopen("that.in", "r", stdin), freopen("that.out", "w", stdout);
    int T; scanf("%d", &T);
    while (T--) {
        for (int i = 0; i <= ncnt; i++) endpos[i].clear();
        init(), tot = 0, memset(head, 0, sizeof(head)), memset(appear, 0, sizeof(appear)), memset(ans, 0, sizeof(ans)), ecnt = 0;
        scanf("%s%d", s + 1, &k), n = strlen(s + 1); gethash(s, n);
        for (int i = n; i >= 1; i--) appear[insert(s[i])] = i;
        for (int i = 1; i <= ncnt; i++) adde(link[i], i);
        for (int i = head[0]; i; i = e[i].next)
            dfs(e[i].to, 0);
        int mn = 1e9;
        for (int i = 1; i <= ncnt; i++) if (ans[i]) mn = min(mn, ans[i]);
        if (mn > n) { puts("NOTFOUND!"); continue; }
        int pos = 0;
        for (int i = 1; i <= ncnt; i++) if (ans[i] && ans[i] == mn) {
            if (!pos) pos = wkr[i];
            else {
                int nw = wkr[i], t = LCP(pos, nw);
                if (pos + t - 1 != n && nw + t - 1 != n) {
                    if (s[pos + t] > s[nw + t]) pos = nw; 
                }
            }
        }
        for (int i = 1; i <= mn; i++) putchar(s[pos + i - 1]);
        puts("");
    }
}
