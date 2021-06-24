#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

typedef pair<int, int> P;

struct edge {
    int to, next;
} e[N * 30];

int head[N * 7], ecnt;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
}

int trie[N * 7][2], ncnt = 2, id[N * 7] = { 0, 2 }, fa[N * 7];

int insert(int n, char s[]) {
    int nw = 1;
    for (int i = 1; i <= n; i++) {
        int c = s[i] - '0';
        if (trie[nw][c]) nw = trie[nw][c];
        else {
            trie[nw][c] = ++ncnt, fa[ncnt] = nw, id[trie[nw][c]] = ++ncnt;
            adde(nw, trie[nw][c]), adde(id[trie[nw][c]], id[nw]), nw = trie[nw][c];
        }
    }
    return nw;
}

int dfn[N * 7], low[N * 7], dfsn, scc[N * 7], stk[N * 7], vis[N * 7], top, tot;

void tarjan(int u) {
    dfn[u] = low[u] = ++dfsn, stk[++top] = u, vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (!dfn[e[i].to]) tarjan(e[i].to), low[u] = min(low[u], low[e[i].to]);
        else if (vis[e[i].to]) low[u] = min(low[u], dfn[e[i].to]);
    if (low[u] >= dfn[u]) {
        tot++;
        while (vis[u]) scc[stk[top]] = tot, vis[stk[top--]] = 0;
    }
}

char s[N]; int p[N][2], pos[N], st[N], fuck[N]; char all[N]; 

vector<P> tmp[N * 7];

int main() {
    freopen("binary.in", "r", stdin), freopen("binary.out", "w", stdout);
    int n, cur = 0; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1); int len = strlen(s + 1), pos = 0;
        st[i] = cur + 1, fuck[i] = len;
        for (int j = 1; j <= len; j++) all[++cur] = s[j];
        for (int j = 1; j <= len; j++) if (s[j] == '?') {
            pos = j; break;
        }
        p[i][0] = ++ncnt, p[i][1] = ++ncnt, ::pos[i] = pos;
        if (!pos) adde(p[i][1], p[i][0]), tmp[insert(len, s)].push_back(P(i, 0));
        else {
            s[pos] = '0'; int A = insert(len, s);
            s[pos] = '1'; int B = insert(len, s);
            tmp[A].push_back(P(i, 0)), tmp[B].push_back(P(i, 1));
        }
    }
    // if (n == 232) return 0;
    for (int i = 1; i <= ncnt; i++) if (tmp[i].size()) {
        for (int j = 0, lst = 0; j < tmp[i].size(); j++) {
            auto t = tmp[i][j];
            ncnt++, adde(ncnt, p[t.first][t.second ^ 1]);
            if (lst) adde(p[t.first][t.second], lst), adde(ncnt, lst);
            lst = ncnt;
        }
        for (int j = tmp[i].size() - 1, lst = 0; j >= 0; j--) {
            auto t = tmp[i][j];
            ncnt++, adde(ncnt, p[t.first][t.second ^ 1]);
            if (lst) adde(p[t.first][t.second], lst), adde(ncnt, lst);
            lst = ncnt;
        }
        for (auto a : tmp[i]) {
            adde(i, p[a.first][a.second ^ 1]);
            adde(id[i], p[a.first][a.second ^ 1]);
            if (trie[i][0]) adde(p[a.first][a.second], trie[i][0]);
            if (trie[i][1]) adde(p[a.first][a.second], trie[i][1]);
            if (fa[i]) adde(p[a.first][a.second], id[fa[i]]);
        }
    }
    for (int i = 1; i <= ncnt; i++) if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i++) if (scc[p[i][0]] == scc[p[i][1]]) {
        puts("NO"); return 0;
    }
    puts("YES");
    for (int i = 1; i <= n; i++) {
        if (!pos[i]) {
            for (int j = 1; j <= fuck[i]; j++) putchar(all[st[i] + j - 1]);
        } else if (scc[p[i][0]] < scc[p[i][1]]) {
            for (int j = 1; j <= fuck[i]; j++) putchar(j == pos[i] ? '0' : all[st[i] + j - 1]);
        } else {
            for (int j = 1; j <= fuck[i]; j++) putchar(j == pos[i] ? '1' : all[st[i] + j - 1]);
        }
        puts("");
    }
}   