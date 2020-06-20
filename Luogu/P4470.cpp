#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;

typedef long long LL;

struct SA {

int x[N], y[N], sa[N], height[N], rk[N], m, c[N];

inline void sort(int len) {
    for (int i = 1; i <= m; i++) c[i] = 0;
    for (int i = 1; i <= len; i++) c[x[i]]++;
    for (int i = 1; i <= m; i++) c[i] += c[i - 1];
    for (int i = len; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
}

inline void build(char s[], int len) {
    for (int i = 1; i <= len; i++) x[i] = s[i], y[i] = i;
    m = 127, sort(len);
    for (int k = 1, num = 0; k < len; k <<= 1, num = 0) {
        for (int i = len; i >= len - k + 1; i--) y[++num] = i;
        for (int i = 1; i <= len; i++) if (sa[i] > k) y[++num] = sa[i] - k;
        sort(len);
        for (int i = 1; i <= len; i++) y[i] = x[i];
        num = x[sa[1]] = 1;
        for (int i = 2; i <= len; i++)
            x[sa[i]] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? num : ++num;
        m = num; if (m == len) break;
    }
    for (int i = 1; i <= len; i++) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= len; i++) if (rk[i] != 1) {
        if (k) k--;
        int at = sa[rk[i] - 1];
        while (at + k <= len && i + k <= len && s[at + k] == s[i + k]) k++;
        height[rk[i]] = k;
    }
}

} fuck;

int link[N], ch[N][26], len[N], appear[N], last, ncnt;

inline int insert(char c) {
    int nw = ++ncnt, p = last; len[nw] = len[last] + 1, last = nw;
    while (p != -1 && !ch[p][c - 'a']) ch[p][c - 'a'] = nw, p = link[p];
    if (p == -1) return last;
    int q = ch[p][c - 'a'];
    if (len[q] == len[p] + 1) return link[nw] = q, last;
    int clone = ++ncnt; 
    memcpy(ch[clone], ch[q], sizeof(ch[q])), len[clone] = len[p] + 1, link[clone] = link[q], link[q] = link[nw] = clone;
    while (p != -1 && ch[p][c - 'a'] == q) ch[p][c - 'a'] = clone, p = link[p];
    return last; 
}

int ls[N * 50], rs[N * 50], mx[N * 50], tot;

void insert(int &rt, int l, int r, int x) {
    if (!rt) rt = ++tot;
    mx[rt] = max(mx[rt], x);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) insert(ls[rt], l, mid, x);
    else insert(rs[rt], mid + 1, r, x);
}

int query(int rt, int l, int r, int start, int end) {
    if (!rt) return -1;
    if (start <= l && r <= end) return mx[rt];
    int mid = (l + r) >> 1;
    if (end <= mid) return query(ls[rt], l, mid, start, end);
    if (start > mid) return query(rs[rt], mid + 1, r, start, end);
    int res = max(mx[ls[rt]], query(rs[rt], mid + 1, r, start, end));    
    return res >= start ? res : -1;
}

int merge(int x, int y, int l, int r) {
    if (!x || !y) return x + y;
    int nw = ++tot; mx[nw] = max(mx[x], mx[y]);
    if (l == r) return nw;
    int mid = (l + r) >> 1;
    ls[nw] = merge(ls[x], ls[y], l, mid), rs[nw] = merge(rs[x], rs[y], mid + 1, r);
    return nw;
}

int rt[N], n;

inline LL solve(char t[], int l, int r) {
    int len = strlen(t + 1); static char tmp[N];
    for (int i = 1; i <= len; i++) tmp[i] = t[len - i + 1];
    fuck.build(tmp, len);
    int ct = 0, pos = 0; LL res = 0;
    for (int i = 1; i <= len; i++) {
        int hh = 0;
        while (pos && ((!ch[pos][t[i] - 'a']) || (ch[pos][t[i] - 'a'] && ((hh = query(rt[ch[pos][t[i] - 'a']], 1, n, l + ::len[link[ch[pos][t[i] - 'a']]], r)) == -1)))) 
            pos = link[pos], ct = ::len[pos];
        if (ch[pos][t[i] - 'a'] && query(rt[ch[pos][t[i] - 'a']], 1, n, l + ::len[link[ch[pos][t[i] - 'a']]], r) != -1) {
            pos = ch[pos][t[i] - 'a'], ct++;
            int lst = query(rt[pos], 1, n, l + ::len[link[pos]], r), mx = min(ct, lst - l + 1), mn = 1 + fuck.height[fuck.rk[len - i + 1]];
            res += max(0, mx - mn + 1);
        }
    }
    LL all = 0;
    for (int i = 1; i <= len; i++) all += (len - i + 1) - fuck.height[fuck.rk[i]];
    return all - res;
}

char s[N], t[N]; vector<int> G[N];

void dfs(int u) {
    for (auto v : G[u]) dfs(v), rt[u] = merge(rt[u], rt[v], 1, n);
}

int main() { 
    freopen("name.in", "r", stdin), freopen("name.out", "w", stdout);
    link[0] = -1, scanf("%s", s + 1), n = strlen(s + 1);
    for (int i = 1; i <= n; i++) appear[insert(s[i])] = i;
    for (int i = 1; i <= ncnt; i++) if (appear[i]) insert(rt[i], 1, n, appear[i]);
    for (int i = 1; i <= ncnt; i++) G[link[i]].push_back(i);
    dfs(0);
    int q; scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%s%d%d", t + 1, &l, &r);
        printf("%lld\n", solve(t, l, r));
    }
    return 0;
}
