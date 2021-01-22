#include <bits/stdc++.h>
using namespace std;

const int N = 250010;
const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int w[2][N << 2], _all;

void pre(int n) {
    int &len = _all = 1;     
    while (len <= n * 2) len <<= 1;
    w[0][0] = w[1][0] = 1, w[1][1] = Pow(3, (mod - 1) / len), w[0][1] = Pow(w[1][1], mod - 2);
    for (int i = 2; i < len; i++) 
        w[0][i] = (LL)w[0][i - 1] * w[0][1] % mod, w[1][i] = (LL)w[1][i - 1] * w[1][1] % mod;
}

int r[N << 2];

void getR(int len, int l) {
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
}

template<class T>
void NTT(T a, int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2, step = 1; mid <= len; mid <<= 1, step++) 
        for (int i = 0; i < len; i += mid) {
            int cur = 0, tmp = _all >> step;
            for (int j = i; j < i + (mid >> 1); j++, cur += tmp) {
                int t = (LL)a[j + (mid >> 1)] * w[type][cur] % mod;
                a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
            } 
        }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

vector<int> Mul(vector<int> A, vector<int> B) {
    int a = A.size(), b = B.size(), len = 1, l = 0;
    while (len <= a + b) len <<= 1, l++;
    getR(len, l), A.resize(len), B.resize(len);
    NTT<vector<int>&>(A, A.size(), 1), NTT<vector<int>&>(B, B.size(), 1);
    for (int i = 0; i < len; i++) A[i] = (LL)A[i] * B[i] % mod;
    NTT<vector<int>&>(A, A.size(), 0), A.resize(a + b - 1);
    return A;
}

vector<int> Add(vector<int> A, vector<int> B) {
    int n = max(A.size(), B.size());
    A.resize(n), B.resize(n);
    for (int i = 0; i < n; i++) A[i] = (A[i] + B[i]) % mod;
    return A;
}

using FUCK = pair<vector<int>, vector<int>>;

vector<vector<int>> poly;
FUCK solve(int l, int r) {
    if (l == r) return make_pair(poly[l], vector<int>{});
    int mid = (l + r) >> 1;
    auto A = solve(l, mid), B = solve(mid + 1, r);
    return make_pair(Add(A.first, B.first), Add(Add(A.second, B.second), Mul(A.first, B.first)));
}

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
}

int sz[N], vis[N];

int getSZ(int u) {
    sz[u] = vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) sz[u] += getSZ(e[i].to);
    return vis[u] = 0, sz[u];
}

int getRT(int u, int tot) {
    vis[u] = 1;
    for (int i = head[u], tmp; i; i = e[i].next)
        if (!vis[e[i].to] && (tmp = getRT(e[i].to, tot))) 
            return vis[u] = 0, tmp;
    return vis[u] = 0, sz[u] >= (tot >> 1) ? u : 0;
}

vector<int> tmp;

void dfs(int u, int d) {
    while (tmp.size() <= d) tmp.push_back(0); 
    tmp[d]++, vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) dfs(e[i].to, d + 1);
    vis[u] = 0;
}

int ans[N];

void divide(int u) {
    u = getRT(u, getSZ(u)), vis[u] = 1;
    poly.clear(), poly.push_back({ 1 });
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) 
            tmp.resize(0), dfs(e[i].to, 1), poly.push_back(tmp);
    vector<int> res = solve(0, (int)poly.size() - 1).second;
    for (int i = 0; i < res.size(); i++) ans[i] = (ans[i] + res[i]) % mod;
    for (int i = head[u]; i; i = e[i].next)
        if (!vis[e[i].to]) divide(e[i].to);
}

int main() {
    freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
    int n, k; scanf("%d%d", &n, &k), pre(n);
    for (int i = 1, a, b; i <= n; i++) {
        scanf("%d%d", &a, &b);
        if (a != b) adde(a, b);
    }
    int res = 0, tot = 0;
    divide(1);
    for (int i = 1; i <= n; i++) {
        tot = (tot + ans[i]) % mod;
        res = (res + (LL)ans[i] * Pow(i, k)) % mod;
    } 
    printf("%lld\n", (LL)res * Pow(tot, mod - 2) % mod);
}