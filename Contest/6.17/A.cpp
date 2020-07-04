#include <bits/stdc++.h>
using namespace std;

const int N = 10010;
const int SZ = 200;

int trie[N][26], ncnt, fa[N];

inline int insert(char s[], int n) {
    int nw = 0;
    for (int i = n; i >= 1; i--) {
        int c = s[i] - 'a';
        if (!trie[nw][c]) nw = trie[nw][c] = ++ncnt;
        else nw = trie[nw][c];
    }
    return nw;
}

int res = 0, dep[N], A[N], B[N], pos[N];

inline void insert(int u, int type) {
    u = pos[u];
    while (u) {
        res -= min(A[u], B[u]);
        type ? A[u]++ : B[u]++;
        res += min(A[u], B[u]);
        u = fa[u];
    }
}

inline void del(int u, int type) {
    u = pos[u];
    while (u) {
        res -= min(A[u], B[u]);
        type ? A[u]-- : B[u]--;
        res += min(A[u], B[u]);
        u = fa[u];
    }
}

char s[N]; int bel[N];

struct tcurts {

int l1, r1, l2, r2, id;

bool operator < (const tcurts &b) {
    if (bel[l1] != bel[b.l1]) return bel[l1] < bel[b.l1];
    if (bel[r1] != bel[b.r1]) return bel[r1] < bel[b.r1];
    if (bel[l2] != bel[b.l2]) return bel[l2] < bel[b.l2];
    return r2 < b.r2;
}

} q[N * 50];

int len[N], ans[N * 50];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1); int t = strlen(s + 1);
        pos[i] = insert(s, t), len[i] = t;
    }
    for (int i = 1; i <= ncnt; i++)
        for (int j = 0; j < 26; j++) if (trie[i][j]) fa[trie[i][j]] = i;
    for (int i = 1; i <= m; i++) scanf("%d%d%d%d", &q[i].l1, &q[i].r1, &q[i].l2, &q[i].r2), q[i].id = i;
    for (int i = 1, nw = 1; i <= n; i++, nw++) {
        int j = i, sz = len[i]; 
        while (j < n && sz + len[j + 1] <= SZ) j++, sz += len[j];
        for (int t = i; t <= j; t++) bel[t] = nw;
        i = j;
    }
    sort(q + 1, q + m + 1);
    int l1 = 1, r1 = 0, l2 = 1, r2 = 0;
    for (int i = 1; i <= m; i++) {
        while (l1 > q[i].l1) insert(--l1, 1);
        while (l1 < q[i].l1) del(l1++, 1);
        while (r1 < q[i].r1) insert(++r1, 1);
        while (r1 > q[i].r1) del(r1--, 1);
        while (l2 > q[i].l2) insert(--l2, 0);
        while (l2 < q[i].l2) del(l2++, 0);
        while (r2 < q[i].r2) insert(++r2, 0);
        while (r2 > q[i].r2) del(r2--, 0);
        ans[q[i].id] = res;
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}

