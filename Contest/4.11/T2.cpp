#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> P;

LL mod;

inline LL mul(LL a, LL b) {
    return (a * b - (LL)((long double)a / mod * b) * mod + mod) % mod;
}

inline LL Pow(LL x, LL y) {
    LL res = 1;
    for (; y; y >>= 1, x = mul(x, x)) if (y & 1) res = mul(res, x);
    return res;
}

inline LL Cipolla(LL x) {
    if (Pow(x, (mod - 1) / 2) != 1) return -1;
    LL a = rand() % mod;
    while (Pow((mul(a, a) - x + mod) % mod, (mod - 1) / 2) != mod - 1) a = rand() % mod;
    LL t = (mul(a, a) - x + mod) % mod;
    auto Mul = [&](P a, P b) -> P {
        LL A = (mul(a.first, b.first) + mul(a.second, mul(b.second, t))) % mod;
        LL B = (mul(a.first, b.second) + mul(a.second, b.first)) % mod;
        return P(A, B);
    };
    P res(1, 0), tmp(a, 1); LL y = (mod + 1) / 2;
    for (; y; y >>= 1, tmp = Mul(tmp, tmp)) if (y & 1) res = Mul(res, tmp);
    return res.first;
}

const int N = 100010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

inline void adde(int from, int to) {
    e[++ecnt] = (edge){to, head[from]}, head[from] = ecnt;
    e[++ecnt] = (edge){from, head[to]}, head[to] = ecnt;
}

LL num[N], t1, t2, res; map<LL, int> mp[N]; int RT[N];

inline void merge(int a, int b) {
    if (mp[RT[a]].size() > mp[RT[b]].size()) swap(a, b);
    for (auto t : mp[RT[a]]) mp[RT[b]][t.first] += t.second;
    mp[RT[a]].clear(), RT[a] = RT[b];
}

void dfs(int u, int f) {
    RT[u] = u;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) 
            dfs(e[i].to, u), merge(u, e[i].to);
    if (t1 == -1) {
        if (!u) res += mp[RT[u]][0];
    } else {
        res += mp[RT[u]][mul(num[u], t1)];
        if (t1 != t2) res += mp[RT[u]][mul(num[u], t2)];
    }
    mp[RT[u]][num[u]]++;
}

int main() {
    srand((LL)new char);
    int n; LL A, B; scanf("%d%lld%lld%lld", &n, &mod, &A, &B);
    LL tmp = ((mul(A, A) - 4 * B) % mod + mod) % mod, inv2 = (mod + 1) / 2; tmp = Cipolla(tmp);
    if (tmp == -1) t1 = -1;
    else {
        t1 = (tmp - A + mod) % mod, t2 = (-tmp - A + 2 * mod) % mod;
        t1 = mul(t1, inv2), t2 = mul(t2, inv2);
    }
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    for (int i = 2, a; i <= n; i++) scanf("%d", &a), adde(a, i);
    dfs(1, 0), printf("%lld\n", res);
    return 0;
}