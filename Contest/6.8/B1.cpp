#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int frac[N], inv[N];

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt, sz[N];

inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int Wn[2][20][N << 1], r[N << 2];

inline void Pre(int len) {
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) {
        int t1 = Pow(3, (mod - 1) / mid), t2 = Pow(t1, mod - 2);
        Wn[0][step][0] = Wn[1][step][0] = 1, Wn[1][step][1] = t1, Wn[0][step][1] = t2;
        for (int i = 2; i < (mid >> 1); i++) {
            Wn[1][step][i] = (LL)Wn[1][step][i - 1] * t1 % mod;
            Wn[0][step][i] = (LL)Wn[0][step][i - 1] * t2 % mod;
        }
    }
}

inline void Inc(int &x, int y) { x += y, x -= x >= mod ? mod : 0; }
inline int Sub(int x, int y) { int t = x - y; return t < 0 ? t + mod : t; }

inline void NTT(vector<int> &a, int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++) {
                int t = (LL)Wn[type][step][j - i] * a[j + (mid >> 1)] % mod;
                a[j + (mid >> 1)] = Sub(a[j], t), Inc(a[j], t);
            }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

inline void GetR(int len, int l) {
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
}

int n;

inline vector<int> mul(vector<int> a, vector<int> b) { 
    int t = a.size() + b.size() - 2, len = 1, l = 0;
    while (len <= t) len <<= 1, l++;
    GetR(len, l), a.resize(len + 1), b.resize(len + 1);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = (LL)a[i] * b[i] % mod;
    NTT(a, len, 0), a.resize(min(n + 1, t + 1));
    return a;
}

inline vector<int> add(vector<int> a, vector<int> b) {
    vector<int> res(max(a.size(), b.size()), 0);
    for (int i = 0; i < a.size(); i++) res[i] = a[i];
    for (int i = 0; i < b.size(); i++) Inc(res[i], b[i]);
    return res;
}

int son[N];

void dfs(int u, int f) {
    sz[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u), sz[u] += sz[e[i].to];
            if (sz[son[u]] < sz[e[i].to]) son[u] = e[i].to;
        }
}

vector<int> q[N], q1[N];

struct node { vector<int> A, B; };

inline node merge(node a, node b) {
    return (node){ add(a.A, mul(a.B, b.A)), mul(a.B, b.B) };
}

vector<int> CDQ1(int l, int r) {
    if (l > r) return {1};
    if (l == r) return q[l];
    int mid = (l + r) >> 1;
    vector<int> L = CDQ1(l, mid), R = CDQ1(mid + 1, r);
    return mul(L, R);
}

node CDQ2(int l, int r) {
    if (l == r) return (node){ q1[l], q1[l] };
    int mid = (l + r) >> 1;
    return merge(CDQ2(l, mid), CDQ2(mid + 1, r));
}

vector<int> res[N];

int top = 0, appear[N];

void dfs(int u, int f, int t) {
    int tot = 0;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && e[i].to != son[u]) dfs(e[i].to, u, e[i].to);
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && e[i].to != son[u])
            q[++tot] = res[e[i].to], q[tot][0]++;
    vector<int> tmp = CDQ1(1, tot); tmp.insert(tmp.begin(), 0), q1[++top] = tmp, appear[u] = top;
    if (son[u]) dfs(son[u], u, t);
    else res[t] = CDQ2(appear[t], top).A; 
    top--;
}

int main() {
    LL s; scanf("%d%lld", &n, &s), frac[0] = inv[0] = 1, s %= mod;
    for (int i = 1; i <= n; i++) frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 1, a, b; i < n; i++)
        scanf("%d%d", &a, &b), adde(a, b);
    int len = 1;
    while (len <= n * 2) len <<= 1;
    Pre(len);
    dfs(1, 0), dfs(1, 0, 1);
    int ans = 0;
    for (int i = 1, tmp = 1; i <= n; tmp = (LL)tmp * (s + i) % mod, i++) 
        ans = (ans + (LL)res[1][i] * tmp % mod * inv[i - 1]) % mod;
    printf("%d\n", ans);
}
