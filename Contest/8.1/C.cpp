#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

typedef long long LL;

int ch[N][26], len[N], link[N] = { -1 }, tot, lst;

int insert(char c) {
    int nw = ++tot, p = lst; len[nw] = len[lst] + 1, lst = nw;
    while (p != -1 && !ch[p][c - 'a']) ch[p][c - 'a'] = nw, p = link[p];
    if (p == -1) return lst;
    int q = ch[p][c - 'a'];
    if (len[q] == len[p] + 1) return link[nw] = q, lst;
    int clone = ++tot; memcpy(ch[clone], ch[q], sizeof(ch[q])), len[clone] = len[p] + 1;
    link[clone] = link[q], link[q] = link[nw] = clone;
    while (p != -1 && ch[p][c - 'a'] == q) ch[p][c - 'a'] = clone, p = link[p];
    return lst;
}

char s[N]; int appear[N], id[N]; vector<int> wkr[N];

LL dp[N];

int main() {
    scanf("%s", s + 1); int n = strlen(s + 1);
    for (int i = 1; i <= n; i++) appear[insert(s[i])]++;
    for (int i = 1; i <= tot; i++) id[i] = i;
    sort(id + 1, id + tot + 1, [&](int a, int b) { return len[a] > len[b]; });
    for (int i = 1; i <= tot; i++) appear[link[id[i]]] += appear[id[i]], wkr[link[i]].push_back(i);
    LL res = 0;
    for (int i = 1; i <= tot; i++) {
        LL t = 0; int u = id[i];
        for (auto v : wkr[u]) t = max(t, dp[v] + (LL)(len[v] - len[u]) * appear[v]);
        for (int j = 0; j < 26; j++) if (ch[u][j]) {
            int v = ch[u][j];
            t = max(t, dp[v] + (LL)(len[v] - len[u]) * appear[v]);
        } 
        dp[u] = t, res = max(res, dp[u] + (LL)appear[u] * len[u]);
    }
    printf("%lld\n", res);
}