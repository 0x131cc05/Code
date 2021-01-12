#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast")

const int N = 50010;
const int P = 131;
const int mod = 998244353;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline int Add(int x, int y) {
    int t = x + y; return t >= mod ? t - mod : t;
}

int pw[N], inv[N];

int lson[N * 32], rson[N * 32], sum[N * 32], ncnt;

int build(int l, int r) {
    int rt = ++ncnt, mid = (l + r) >> 1;
    if (l == r) return rt;
    lson[rt] = build(l, mid), rson[rt] = build(mid + 1, r);
    return rt; 
}

int x, t, start;

int update(int rt, int l, int r) {
    int nw = ++ncnt; sum[nw] = Add(sum[rt], t), lson[nw] = lson[rt], rson[nw] = rson[rt];
    if (l == r) return nw;
    int mid = (l + r) >> 1;
    if (x <= mid) lson[nw] = update(lson[nw], l, mid);
    else rson[nw] = update(rson[nw], mid + 1, r);
    return nw;
}

inline int update(int rt, int l, int r, int x, int t) {
    return ::x = x, ::t = t, update(rt, l, r);
}

int query(int rt, int l, int r) {
    if (start <= l) return sum[rt];
    int mid = (l + r) >> 1;
    if (mid >= start) return Add(query(lson[rt], l, mid), sum[rson[rt]]);
    return query(rson[rt], mid + 1, r);
}

inline int query(int rt, int l, int r, int start) {
    return ::start = start, query(rt, l, r);
}

int nxt[N], num[N], RT[N], n; vector<int> appear[N], fuck[N];

inline int get(int l, int r) {
    return (LL)query(RT[r], 1, n, l) * inv[l] % mod;
}

inline int LCP(int a, int b) {
    int l = 1, r = min(n - a + 1, n - b + 1), mid, ans = 0;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (get(a, a + mid - 1) == get(b, b + mid - 1)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}

int id[N];

inline int find(int l, int x) {
    return *lower_bound(appear[num[x]].begin(), appear[num[x]].end(), l) - l;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]), appear[num[i]].push_back(i);
    for (int i = 1; i <= n; i++) if (appear[i].size()) {
        for (int j = 0; j + 1 < appear[i].size(); j++)
            nxt[appear[i][j]] = appear[i][j + 1];
        nxt[appear[i].back()] = appear[i].back();
    } 
    pw[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = (LL)pw[i - 1] * P % mod;
        inv[i] = Pow(pw[i], mod - 2);
    }
    for (int i = 1; i <= n; i++) fuck[nxt[i]].push_back(i);
    RT[0] = build(1, n);
    for (int i = 1; i <= n; i++) {
        RT[i] = RT[i - 1];
        for (auto t : fuck[i]) 
            RT[i] = update(RT[i], 1, n, t, (LL)(i - t) * pw[t] % mod); 
    }
    for (int i = 1; i <= n; i++) id[i] = i;
    stable_sort(id + 1, id + n + 1, [](int a, int b) {
        int len = LCP(a, b);
        if (a + len - 1 == n || b + len - 1 == n) return a > b;
        return find(a, a + len) > find(b, b + len);
    });
    for (int i = 1; i <= n; i++) cout << id[i] << ' ';
    cout << endl;
    int res = (LL)n * (n + 1) / 2;
    for (int i = 1; i < n; i++) res -= LCP(id[i], id[i + 1]);
    printf("%d\n", res);
}
