#include <bits/stdc++.h>
using namespace std;

const int M = 1000010;
const int mod = 998244353;

typedef long long LL;

int pw2[M], inv2[M];

int trie[M][2], ncnt, at[M], t[M] = { -1 }, d[M] = { 0 }, A[M], B[M], totA, totB;

void clear(int u) {
    if (!u) return;
    if (at[u]) {
        totA = (totA - A[at[u]] + mod) % mod;
        totB = (totB - B[at[u]] + mod) % mod;
        at[u] = 0;
    }
    clear(trie[u][0]), clear(trie[u][1]);
}

void insert(char s[], int id) {
    int nw = 0, lst = 0;
    for (int i = 1; i <= d[id]; i++) {
        if (at[nw]) lst = at[nw];
        int nxt = s[i] == 'R';
        if (!trie[nw][nxt]) trie[nw][nxt] = ++ncnt, trie[ncnt][0] = trie[ncnt][1] = at[ncnt] = 0;
        nw = trie[nw][nxt];
    }
    clear(nw), trie[nw][0] = trie[nw][1] = 0, at[nw] = id;
    A[id] = inv2[t[lst] + d[id] - d[lst]], B[id] = inv2[t[id]];
    totA = (totA + A[id]) % mod, totB = (totB + B[id]) % mod;
}

char s[M];

int main() {
//    freopen("ex_pikachu1.in", "r", stdin), freopen("out.out", "w", stdout);
    int T; scanf("%d", &T);
    pw2[0] = inv2[0] = 1, pw2[1] = 2, inv2[1] = (mod + 1) / 2;
    for (int i = 2; i <= M - 10; i++) pw2[i] = 2 * pw2[i - 1] % mod, inv2[i] = (LL)inv2[i - 1] * inv2[1] % mod;
    while (T--) {
        ncnt = trie[0][0] = trie[0][1] = at[0] = totA = 0, totB = 2;
        int n, cur = 0; scanf("%d", &n);
        for (int i = 1, nw = 0; i <= n; i++) {
            char op[5]; scanf("%s", op + 1);
            if (op[1] == 'G') {
                int delta; scanf("%d", &delta), cur += delta;
            } else {
                nw++, scanf("%s", s + 1), d[nw] = strlen(s + 1), t[nw] = cur;
                insert(s, nw);
            }
            printf("%d\n", ((LL)(totB - totA + mod) * pw2[cur] - 1 + mod) % mod);
        }
    }
}
