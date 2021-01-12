#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;

int link[N] = {-1}, ch[N][26], len[N], sz[N], ncnt;

int extend(int f, char c) {
    if (ch[f][c - 'A'] && len[ch[f][c - 'A']] == len[f] + 1) return ch[f][c - 'A'];
    int nw = ++ncnt, p = f; len[nw] = len[p] + 1;
    while (~p && !ch[p][c - 'A']) ch[p][c - 'A'] = nw, p = link[p];
    if (p == -1) return nw;
    int q = ch[p][c - 'A'];
    if (len[q] == len[p] + 1) return link[nw] = q, nw;
    int clone = p == f ? nw : ++ncnt; memcpy(ch[clone], ch[q], sizeof(ch[q])), len[clone] = len[p] + 1;
    link[clone] = link[q], link[q] = clone;
    if (clone != nw) link[nw] = clone;
    while (~p && ch[p][c - 'A'] == q) ch[p][c - 'A'] = clone, p = link[p];
    return nw;
}

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

void dfs(int u, int f) {
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u), sz[u] += sz[e[i].to];
}

int at[N]; char fuck[N]; vector<int> G[N];

int main() {
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 1, p; i <= n; i++) {
        static char s[5]; scanf("%s%d", s + 1, &p);
        G[p].push_back(i), fuck[i] = s[1];
    }
    queue<int> h; h.push(0);
    while (!h.empty()) {
        int u = h.front(); h.pop();
        for (auto v : G[u]) {
            at[v] = extend(at[u], fuck[v]), h.push(v);
            sz[at[v]]++;
        }
    }
    for (int i = 1; i <= ncnt; i++) 
        if (~link[i]) adde(link[i], i);
    dfs(0, 0);
    while (q--) {
        static char s[N]; scanf("%s", s + 1);
        int l = strlen(s + 1), nw = 0, flag = 1;
        for (int i = l; i >= 1; i--) {
            if (!ch[nw][s[i] - 'A']) { flag = 0; break; }
            nw = ch[nw][s[i] - 'A'];
        }
        printf("%d\n", flag ? sz[nw] : 0);
    }
}