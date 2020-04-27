#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

int sum[N * 50], ls[N * 50], rs[N * 50], ncnt;

inline void pushup(int rt) {
    sum[rt] = sum[ls[rt]] + sum[rs[rt]];
}

void update(int &rt, int l, int r, int x) {
    if (!rt) rt = ++ncnt;
    if (l == r) return sum[rt]++, void();
    int mid = (l + r) >> 1;
    if (x <= mid) update(ls[rt], l, mid, x);
    else update(rs[rt], mid + 1, r, x);
    pushup(rt);
}

int query(int rt, int l, int r, int start, int end) {
    if (!rt) return 0;
    if (start <= l && r <= end) return sum[rt];
    int mid = (l + r) >> 1, res = 0;
    if (start <= mid) res += query(ls[rt], l, mid, start, end);
    if (end > mid) res += query(rs[rt], mid + 1, r, start, end);
    return res; 
}

int merge(int x, int y, int l, int r) {
    if (!x || !y) return x | y;
    int mid = (l + r) >> 1, nw = ++ncnt; sum[nw] = sum[x];
    if (l == r) return sum[nw] += sum[y], nw;
    ls[nw] = merge(ls[x], ls[y], l, mid), rs[nw] = merge(rs[x], rs[y], mid + 1, r);
    return pushup(nw), nw;
}

struct edge {
    int to, next;
} e[N * 4];

int head[N * 2], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){to, head[from]}, head[from] = ecnt;
    e[++ecnt] = (edge){from, head[to]}, head[to] = ecnt;
}

int last, tot, ch[N * 2][26], link[N * 2], len[N * 2];

inline void insert(char c) {
    int nw = ++tot, p = last; len[nw] = len[last] + 1, last = nw;
    while (p != -1 && !ch[p][c - 'a']) ch[p][c - 'a'] = nw, p = link[p];
    if (p == -1) return;
    int t = ch[p][c - 'a'];
    if (len[t] == len[p] + 1) return link[nw] = t, void();
    int clone = ++tot; len[clone] = len[p] + 1, memcpy(ch[clone], ch[t], sizeof(ch[t])), link[clone] = link[t];
    while (p != -1 && ch[p][c - 'a'] == t) ch[p][c - 'a'] = clone, p = link[p];
    link[t] = link[nw] = clone;
}

int appear[N * 2], RT[N * 2], n;

void dfs(int u, int f) {
    if (appear[u]) update(RT[u], 1, n, appear[u]);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u), RT[u] = merge(RT[u], RT[e[i].to], 1, n);
            if (!appear[u]) appear[u] = appear[e[i].to];
        }
            
}

int dp[N * 2], stk[N * 2], top, pos[N * 2];

inline bool check(int ancestor, int u) {
    if (!ancestor) return true;
    return query(RT[ancestor], 1, n, appear[u] - len[u] + len[ancestor], appear[u]) >= 2;
}

void process(int u, int f) {
    pos[u] = pos[f], stk[++top] = u, dp[u] = max(dp[u], 1);
    while (pos[u] < top && check(stk[pos[u] + 1], u)) pos[u]++; 
    for (int i = head[u]; i; i = e[i].next) 
        if (e[i].to != f) 
            process(e[i].to, u), dp[u] = max(dp[u], dp[e[i].to]);
    top--; if (u) dp[stk[pos[u]]] = max(dp[stk[pos[u]]], dp[u] + 1);
}

char s[N];

int main() {
    scanf("%d%s", &n, s + 1), link[0] = -1;
    for (int i = 1; i <= n; i++) insert(s[i]), appear[last] = i;
    for (int i = 1; i <= tot; i++) adde(link[i], i);
    dfs(0, 0), process(0, 0), printf("%d\n", dp[0] - 1);
    return 0;
}