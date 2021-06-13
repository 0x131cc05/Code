#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 998244353;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int num[N];

int get(int x, int layer) {
    return (x & ((1 << layer) - 1)) + 1;
}

struct data {
    int v0, v1;
    void reset() { v0 = 1, v1 = 0; }
};

data merge(data a, data b) {
    return (data){ ((LL)a.v0 * b.v0 + (LL)a.v1 * b.v1) % mod, ((LL)a.v0 * b.v1 + (LL)a.v1 * b.v0) % mod };
}

struct node {
    int l, r, mul[30]; data x[30];
} T[N << 2];

void pushup(int rt) {
    for (int i = 0; i < 30; i++) {
        T[rt].x[i] = merge(T[rt << 1].x[i], T[rt << 1 | 1].x[i]);
        T[rt].mul[i] = (LL)T[rt << 1].mul[i] * T[rt << 1 | 1].mul[i] % mod;
    }
}

void init(int rt, int x) {
    for (int i = 0; i < 30; i++) {
        int c = (x >> i) & 1;
        int w = 1 << i, w1 = get(x, i);
        if (c) T[rt].x[i].v1 = w1, T[rt].x[i].v0 = w;
        else T[rt].x[i].v0 = w1, T[rt].x[i].v1 = 0;
        T[rt].mul[i] = w1;
    }
}

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) { init(rt, num[l]); return; }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}

void update(int rt, int pos, int x) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l == r) { init(rt, x); return; }
    if (pos <= mid) update(rt << 1, pos, x);
    else update(rt << 1 | 1, pos, x);
    pushup(rt);
}

data res[30]; int mul[30];

void query(int rt, int start, int end) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) {
        for (int i = 0; i < 30; i++) {
            res[i] = merge(res[i], T[rt].x[i]);
            mul[i] = (LL)mul[i] * T[rt].mul[i] % mod;
        }
        return;
    }
    if (start <= mid) query(rt << 1, start, end);
    if (end > mid) query(rt << 1 | 1, start, end);
}

int inv[30];

int tree[N], n;

void upd(int x, int y) {
    for (; x <= n; x += x & -x) tree[x] ^= y;
}

int que(int x) {
    int res = 0;
    for (; x; x -= x & -x) res ^= tree[x];
    return res;
}

int tot;

int work(int x) {
    if (x < 0) return 0;
    bool flag = false;
    int ans = 0;
    for (int i = 29; i >= 0; i--) {
        int v0 = res[i].v0, v1 = res[i].v1;
        int c = (tot >> i) & 1;
        if (c) v1 = (v1 - mul[i] + mod) % mod;
        else v0 = (v0 - mul[i] + mod) % mod;
        v0 = (LL)v0 * inv[i] % mod, v1 = (LL)v1 * inv[i] % mod;
        int w1 = 1 << i, w2 = get(x, i);
        if (flag) ans = (ans + (LL)(v0 + v1) * w1) % mod;
        else {
            int c1 = (x >> i) & 1;
            if (c1) ans = (ans + (LL)v0 * w1 + (LL)v1 * w2) % mod;
            else ans = (ans + (LL)v0 * w2) % mod;
            if (c < c1) flag = true;
            if (c > c1) break;
        }
    }
    if (tot <= x) ans++;
    return ans;
}

int main() {
    freopen("xor.in", "r", stdin), freopen("xor.out", "w", stdout);
    int m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]), upd(i, num[i]);
    for (int i = 0; i < 30; i++) inv[i] = Pow(1 << i, mod - 2);
    build(1, 1, n);
    while (m--) {
        int op, a, b, l, r; scanf("%d%d%d", &op, &a, &b);
        if (op == 1) update(1, a, b), upd(a, num[a] ^ b), num[a] = b;
        else {
            scanf("%d%d", &l, &r);
            tot = que(b) ^ que(a - 1);
            for (int i = 0; i < 30; i++) 
                res[i].reset(), mul[i] = 1;
            query(1, a, b);
            printf("%d\n", (work(r) - work(l - 1) + mod) % mod);
        }
    }
}
