#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
const int mod = 1e9 + 7;

typedef long long LL;

struct node {
    int l, r, s, tag;
} T[N << 2];

inline void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

inline int Add(int x, int y) {
    int t = x + y;
    return t >= mod ? t - mod : t;
}

inline void add(int rt, int x) {
    T[rt].tag += x; int len = T[rt].r - T[rt].l + 1;
    T[rt].s = (T[rt].s + (LL)x * len) % mod;
}

inline void pushdown(int rt) {
    if (T[rt].tag) add(rt << 1, T[rt].tag), add(rt << 1 | 1, T[rt].tag), T[rt].tag = 0;
}

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
}

inline void pushup(int rt) {
    T[rt].s = Add(T[rt << 1].s, T[rt << 1 | 1].s);
}

int update(int rt, int start, int end) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) {
        int ls = T[rt].s;
        return T[rt].tag++, Inc(T[rt].s, r - l + 1), ls;
    }
    pushdown(rt); int res = 0;
    if (start <= mid) Inc(res, update(rt << 1, start, end));
    if (end > mid) Inc(res, update(rt << 1 | 1, start, end));
    return pushup(rt), res;
}

inline void read(int &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int num[N], val[N], top, ls[N];

int main() {
    freopen("sequence.in", "r", stdin), freopen("sequence.out", "w", stdout);
//    freopen("input", "r", stdin);
    int n, res = 0; read(n); build(1, 1, n);
    for (int i = 1; i <= n; i++) 
        read(num[i]), val[++top] = num[i];
    sort(val + 1, val + top + 1), top = unique(val + 1, val + top + 1) - val - 1;
    for (int i = 1, h = 0; i <= n; i++) {
        int x = lower_bound(val + 1, val + top + 1, num[i]) - val; 
        int p = ls[x], t = update(1, p + 1, i);
        ls[x] = i, h = (h + (LL)t * 2 + i - p) % mod, Inc(res, h);
    }
    printf("%d\n", res);
}
