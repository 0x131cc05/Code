#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;
const int mod = 1e9 + 7;

int ch[N][26], link[N], wkr[N], len[N], ncnt, last, diff[N];

inline void init() {
    link[0] = 1, len[0] = 0, len[1] = -1, ncnt = 1, last = 0;
}

char s[N];

inline int jump(int u, int pos) {
    while (s[pos] != s[pos - len[u] - 1]) u = link[u];
    return u;
}

inline void insert(int pos) {
    int nxt = jump(last, pos); char c = s[pos];
    if (!ch[nxt][c - 'a']) {
        int nw = ++ncnt; len[nw] = len[nxt] + 2;
        link[nw] = ch[jump(link[nxt], pos)][c - 'a'], diff[nw] = len[nw] - len[link[nw]];
        ch[nxt][c - 'a'] = nw, wkr[nw] = diff[nw] == diff[link[nw]] ? wkr[link[nw]] : link[nw];
    } 
    last = ch[nxt][c - 'a'];
}

char t[N]; int f[N], g[N];

int main() {
    scanf("%s", t + 1); int n = strlen(t + 1);
    for (int i = 1; i <= n; i++) s[i * 2 - 1] = t[i];
    for (int i = 1; i <= n; i++) s[2 * (n - i + 1)] = t[i];
    init(), f[0] = 1;
    for (int i = 1; i <= n; i++) {
        insert(i);
        for (int p = last; p; p = wkr[p]) {
            g[p] = f[i - len[wkr[p]] - diff[p]];
            if (wkr[p] != link[p]) g[p] = (g[p] + g[link[p]]) % mod;
            if (i % 2 == 0) f[i] = (f[i] + g[p]) % mod;
        }
    }
    printf("%d\n", f[n]);
}