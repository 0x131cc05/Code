#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

#define int LL

typedef long long LL;
typedef pair<int, int> P;

// k * t + b
// delta * (t - t') + k * t + b = (k + delta) * t + b - t' * delta

struct node {
    int l, r, same, x, tag; LL k, b, tk, tb;
} T[N << 2];

inline void pushup(int rt) {
    T[rt].x = max(T[rt << 1].x, T[rt << 1 | 1].x);
    T[rt].k = T[rt << 1].k + T[rt << 1 | 1].k;
    T[rt].b = T[rt << 1].b + T[rt << 1 | 1].b;
    if (T[rt << 1].same && T[rt << 1 | 1].same && T[rt << 1].x == T[rt << 1 | 1].x) T[rt].same = 1;
    else T[rt].same = 0;
}

inline void pushdown(int rt) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (T[rt].tk != 0) {
        T[rt << 1].k += T[rt].tk * (mid - l + 1), T[rt << 1 | 1].k += T[rt].tk * (r - mid);
        T[rt << 1].tk += T[rt].tk, T[rt << 1 | 1].tk += T[rt].tk, T[rt].tk = 0;
    }
    if (T[rt].tb != 0) {
        T[rt << 1].b += T[rt].tb * (mid - l + 1), T[rt << 1 | 1].b += T[rt].tb * (r - mid);
        T[rt << 1].tb += T[rt].tb, T[rt << 1 | 1].tb += T[rt].tb, T[rt].tb = 0;
    }
    if (T[rt].tag != -1) 
        T[rt << 1].x = T[rt << 1 | 1].x = T[rt << 1].tag = T[rt << 1 | 1].tag = T[rt].tag, T[rt].tag = -1;
}

int ans[N];

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r, T[rt].tag = -1;
    if (l == r) return T[rt].x = T[rt].k = ans[l], T[rt].same = 1, void();
    int mid = (l + r) >> 1; build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r), pushup(rt);
}

void update(int rt, int start, int end, int x, int t) {
    if (start > end) return;
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l != r) pushdown(rt);
    if (T[rt].x <= x) return;
    if (start <= l && r <= end && T[rt].same) {
        int delta = x - T[rt].x; T[rt].x = T[rt].tag = x;
        T[rt].tk = delta, T[rt].tb = -(LL)delta * t, T[rt].k += (LL)delta * (r - l + 1), T[rt].b -= (LL)delta * (r - l + 1) * t;
        return;
    }
    if (start <= mid) update(rt << 1, start, end, x, t);
    if (end > mid) update(rt << 1 | 1, start, end, x, t);
    pushup(rt);
}

LL query(int rt, int start, int end, int t) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) return T[rt].k * t + T[rt].b;
    pushdown(rt); LL res = 0;
    if (start <= mid) res += query(rt << 1, start, end, t);
    if (end > mid) res += query(rt << 1 | 1, start, end, t);
    return res;
}

int num[N], buk[N];

vector<P> fuck[N]; LL res[N], tmp[N]; int L[N], R[N], tp[N]; vector<int> appear[N];

signed main() {
//    freopen("ex_escape2.in", "r", stdin);
    int n; scanf("%*d%lld", &n);
    for (int i = 1; i <= n; i++) 
        scanf("%lld", &num[i]), num[i] = min(num[i], n + 1), appear[num[i]].push_back(i);
    appear[0].push_back(n + 1);
    for (int i = 1, mex = 0; i <= n; i++) {
        buk[num[i]] = 1;
        while (mex <= n && buk[mex]) mex++;
        ans[i] = mex, appear[i].push_back(n + 1);
    }
    build(1, 1, n);
    int q; scanf("%lld", &q);
    for (int i = 1, l, r; i <= q; i++) 
        scanf("%lld%lld", &l, &r), fuck[l - 1].push_back(P(r, i)), L[i] = l, R[i] = r;
    for (int i = 1; i <= n; i++) {
        tmp[i] = query(1, 1, i, i);
        for (auto t : fuck[i]) res[t.second] -= query(1, i + 1, t.first, i);
        if (num[i] <= n && i < n) {
//            cout << "update: " << ' ' << i + 1 << ' ' << appear[num[i]][tp[num[i]] + 1] - 1 << ' ' << num[i] << endl;
            update(1, i, appear[num[i]][++tp[num[i]]] - 1, num[i], i);
        }
//        cout << i << ' ' << tmp[i] << endl;
    }
    for (int i = 1; i <= q; i++) 
        printf("%lld\n", res[i] + tmp[R[i]] - tmp[L[i] - 1]);
}
