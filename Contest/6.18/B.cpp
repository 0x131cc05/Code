#include <bits/stdc++.h>
using namespace std;

const int N = 800010;

typedef long long LL;

int ch[N][26], link[N] = {-1}, len[N], last, ncnt;

inline int insert(char c) {
    int nw = ++ncnt, p = last; len[nw] = len[last] + 1, last = nw;
    while (~p && !ch[p][c - 'a']) ch[p][c - 'a'] = nw, p = link[p];
    if (!~p) return nw; 
    int q = ch[p][c - 'a'];
    if (len[q] == len[p] + 1) return link[nw] = q, nw;
    int clone = ++ncnt; memcpy(ch[clone], ch[q], sizeof(ch[q]));
    link[clone] = link[q], len[clone] = len[p] + 1, link[q] = link[nw] = clone;
    while (~p && ch[p][c - 'a'] == q) ch[p][c - 'a'] = clone, p = link[p];
    return nw; 
}

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int fa[N][19]; LL sum[N], k[N], b[N];

void dfs(int u, int f) {
    sum[u] = len[u] - len[max(0, link[u])], fa[u][0] = f;
    for (int i = 1; i <= 18; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u), sum[u] += sum[e[i].to];
    k[u] = -1, b[u] = sum[u] + len[max(0, link[u])] + 1;
}

inline void DP() {
    static int ind[N]; memset(ind, 0, sizeof(ind));
    for (int i = 1; i <= ncnt; i++) 
        for (int j = 0; j < 26; j++) if (ch[i][j]) ind[ch[i][j]]++;
    queue<int> q; vector<int> wkr;
    for (int i = 1; i <= ncnt; i++) if (!ind[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop(), wkr.push_back(u);
        for (int i = 0; i < 26; i++) if (ch[u][i] && !--ind[ch[u][i]]) q.push(ch[u][i]); 
    }
    for (int i = wkr.size() - 1; i >= 0; i--) {
        int u = wkr[i];
        for (int j = 0; j < 26; j++) if (ch[u][j]) {
            k[u] += k[ch[u][j]];
            b[u] += b[ch[u][j]] + k[ch[u][j]];
        }
    }
}

int pos[N];

inline int jump(int u, int l) {
    for (int i = 18; i >= 0; i--)
        if (len[fa[u][i]] >= l) u = fa[u][i];
    return u; 
}

char s[N];

int main() {
    int n, q; scanf("%d%d%s", &n, &q, s + 1);
    for (int i = 1; i <= n; i++) pos[i] = insert(s[i]);
    for (int i = 1; i <= ncnt; i++) adde(link[i], i);
    dfs(0, 0), DP();
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        int u = jump(pos[r], r - l + 1);
        printf("%lld\n", k[u] * (r - l + 1) + b[u]);
    }
}
