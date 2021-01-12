#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int F[N * 10], G[N * 10];

int st[N], len[N], tot, son[N];

void dfs(int u, int f) {
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u);
            if (len[e[i].to] >= len[son[u]]) 
                son[u] = e[i].to, len[u] = len[e[i].to] + 1;
        }
}

inline void apply(int u) {
    st[u] = tot, tot += len[u] + 2;
    for (int i = 0; i <= len[u]; i++) G[st[u] + i] = 1;
}

inline void pushdown(int u, int l) {
    int pre = 1;
    for (int j = 0; j <= l; j++) {
        pre = (LL)pre * G[st[u] + j] % mod;
        F[st[u] + j] = (LL)F[st[u] + j] * pre % mod, G[st[u] + j] = 1;
    }
    if (l != len[u]) G[st[u] + l + 1] = (LL)G[st[u] + l + 1] * pre % mod;
}

void dfs1(int u, int f) {
    if (!son[u]) return F[st[u]] = G[st[u]] = 1, void();
    st[son[u]] = st[u] + 1, dfs1(son[u], u), G[st[u]] = F[st[u]] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && e[i].to != son[u]) {
            apply(e[i].to), dfs1(e[i].to, u); static int tmp[N];
            // if (u == 2) cout << "to: " << e[i].to << endl;
            pushdown(u, len[e[i].to] + 1), pushdown(e[i].to, len[e[i].to]);
            for (int j = 0; j <= len[e[i].to] + 1; j++) {
                tmp[j] = F[st[u] + j];
                // cout << F[st[u] + j] << ' ';
                if (j) tmp[j] = (tmp[j - 1] + tmp[j]) % mod;
            }
            // cout << endl;
            int sum = 1; 
            for (int j = 0; j <= len[e[i].to]; j++) {
                int a = ((LL)tmp[j + 1] * F[st[e[i].to] + j] + (LL)F[st[u] + j + 1] * sum) % mod;
                sum = (sum + F[st[e[i].to] + j]) % mod, F[st[u] + j + 1] = a;
                // cout << sum << ' ' << a << endl;
            }
            if (len[u] != len[e[i].to] + 1) 
                G[st[u] + len[e[i].to] + 2] = (LL)G[st[u] + len[e[i].to] + 2] * sum % mod;
        }
    // pushdown(u, len[u]);
    // cout << "at: " << u << endl;
    // for (int i = 0; i <= len[u]; i++) cout << F[st[u] + i] << ' ';
    // cout << endl;
}

int fuck[N], suf[N], tag[N];

int main() {
    int n; scanf("%d", &n);
    for (int i = 1, a, b; i < n; i++) scanf("%d%d", &a, &b), adde(a, b);
    dfs(1, 0);
    for (int i = 0; i <= n; i++) suf[i] = tag[i] = 1;
    for (int i = head[1]; i; i = e[i].next) {
        apply(e[i].to), dfs1(e[i].to, 1), pushdown(e[i].to, len[e[i].to]);
        // cout << e[i].to << endl;
        // for (int j = 0; j <= len[e[i].to]; j++)
        //     cout << F[st[e[i].to] + j] << ' ';
        // cout << endl;
        F[st[e[i].to]]++;
        for (int j = 1; j <= len[e[i].to]; j++) 
            F[st[e[i].to] + j] = (F[st[e[i].to] + j] + F[st[e[i].to] + j - 1]) % mod;
        for (int j = 0; j < len[e[i].to]; j++) tag[j] = (LL)tag[j] * F[st[e[i].to] + j] % mod;
        suf[len[e[i].to]] = (LL)suf[len[e[i].to]] * F[st[e[i].to] + len[e[i].to]] % mod;
    }
    for (int i = 0, pre = 1; i <= n; i++) {
        pre = (LL)pre * suf[i] % mod;
        fuck[i] = (LL)tag[i] * pre % mod;
    }
    int res = 0;
    for (int i = head[1]; i; i = e[i].next) {
        for (int j = 0; j <= len[e[i].to]; j++) {
            int t = j ? fuck[j - 1] : 1;
            if (j) t = (LL)t * Pow(F[st[e[i].to] + j - 1], mod - 2) % mod;
            int delta = F[st[e[i].to] + j];
            if (j) delta -= F[st[e[i].to] + j - 1];
            else delta--; 
            res = (res + (LL)delta * t) % mod;
        }
    }
    res = (res + mod) % mod;
    printf("%d\n", res);
    return 0;
}
