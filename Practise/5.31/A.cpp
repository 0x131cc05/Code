#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 300010;

struct line {
    int k; LL b;
    line operator+ (line t) { return { k + t.k, b + t.b }; }
    LL get(LL x) { return x * k + b; }
};

LL get(int &head, vector<line> &A, LL x) {
    while (head + 1 < A.size() && A[head + 1].get(x) >= A[head].get(x)) head++;
    return A[head].get(x);
}

bool check(line a, line b, line c) {
    return (a.b - b.b) * (c.k - a.k) >= (a.b - c.b) * (b.k - a.k);
}

void push(vector<line> &x, line l) {
    if (x.size() && l.k <= x.back().k) return;
    while (x.size() >= 2 && check(x[(int)x.size() - 2], x.back(), l)) x.pop_back();
    x.push_back(l);
}

vector<line> add(vector<line> &A, vector<line> &B) { // single point
    vector<line> res;
    int p = 0, q = 0;
    while (p + 1 < A.size() || q + 1 < B.size()) {
        if (p + 1 == A.size()) { push(res, A[p] + B[q++]); continue; }
        if (q + 1 == B.size()) { push(res, A[p++] + B[q]); continue; }
        push(res, A[p] + B[q]);
        LL a = (A[p].b - A[p + 1].b) * (B[q + 1].k - B[q].k);
        LL b = (B[q].b - B[q + 1].b) * (A[p + 1].k - A[p].k);
        if (a <= b) p++;
        if (b <= a) q++;
    }
    push(res, A[p] + B[q]);
    return res;
}

vector<line> chkmax(vector<line> A, vector<line> B) {
    vector<line> res;
    int p = 0, q = 0;
    while (p < A.size() || q < B.size()) {
        if (p == A.size()) { push(res, B[q++]); continue; }
        if (q == B.size()) { push(res, A[p++]); continue; }
        if (A[p].k == B[q].k) {
            if (A[p].b > B[q].b) push(res, A[p]);
            else push(res, B[q]);
            p++, q++;
        } else {
            if (A[p].k > B[q].k) push(res, B[q++]);
            else push(res, A[p++]);
        }
    }
    return res;
}

struct node {
    LL sum; int l, r;
    vector<line> pre, suf, res;
} T[N << 2];

void release(int rt) {
    vector<line>().swap(T[rt].pre);
    vector<line>().swap(T[rt].suf);
    vector<line>().swap(T[rt].res);
}

void pushup(int rt) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    int L = mid - l + 1, R = r - mid;
    vector<line> base; base.push_back({ L, T[rt << 1].sum });
    T[rt].pre = chkmax(T[rt << 1].pre, add(T[rt << 1 | 1].pre, base));
    base[0].k = R, base[0].b = T[rt << 1 | 1].sum;
    T[rt].suf = chkmax(add(T[rt << 1].suf, base), T[rt << 1 | 1].suf);
    T[rt].res = chkmax(T[rt << 1].res, T[rt << 1 | 1].res);
    T[rt].res = chkmax(T[rt].res, add(T[rt << 1].suf, T[rt << 1 | 1].pre));
    T[rt].sum = T[rt << 1].sum + T[rt << 1 | 1].sum;
    release(rt << 1), release(rt << 1 | 1);
}

int num[N], dep[N << 2], all = 0;

void build(int rt, int l, int r) {
    all = max(all, rt);
    T[rt].l = l, T[rt].r = r, dep[rt] = dep[rt >> 1] + 1;
    if (l == r) {
        T[rt].pre = T[rt].suf = T[rt].res = {{0, 0}, {1, num[l]}};
        T[rt].sum = num[l]; return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
}

vector<int> L[N << 2], R[N << 2];

void push(int rt, int start, int end, int id, int cur, int d) {
    if (dep[rt] > d) return;
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) {
        if (dep[rt] != d) return;
        if (cur == -1) cur = 0;
        if (!cur) L[rt].push_back(id);
        else R[rt].push_back(id);
        return;
    }
    if (end <= mid) push(rt << 1, start, end, id, cur, d);
    else if (start > mid) push(rt << 1 | 1, start, end, id, cur, d);
    else {
        push(rt << 1, start, end, id, cur == -1 ? 0 : cur, d);
        push(rt << 1 | 1, start, end, id, cur == -1 ? 1 : cur, d);
    }
}

LL ansL[N * 2], sufL[N * 2];
LL ansR[N * 2], preR[N * 2];

LL x[N * 2];

void solveL(int rt) {
    if (T[rt].l != T[rt].r) pushup(rt);
    int A = 0, B = 0, C = 0;
    for (auto t : L[rt]) {
        LL p = get(A, T[rt].pre, x[t]);
        ansL[t] = max(ansL[t], get(B, T[rt].res, x[t]));
        ansL[t] = max(ansL[t], sufL[t] + p);
        sufL[t] = max(sufL[t] + T[rt].sum + (LL)(T[rt].r - T[rt].l + 1) * x[t], get(C, T[rt].suf, x[t]));
    }
    vector<int>().swap(L[rt]);
}

void solveR(int rt) {
    int A = 0, B = 0, C = 0;
    for (auto t : R[rt]) {
        LL p = get(A, T[rt].suf, x[t]);
        ansR[t] = max(ansR[t], get(B, T[rt].res, x[t]));
        ansR[t] = max(ansR[t], preR[t] + p);
        preR[t] = max(preR[t] + T[rt].sum + (LL)(T[rt].r - T[rt].l + 1) * x[t], get(C, T[rt].pre, x[t]));
    }
    vector<int>().swap(R[rt]);
}

int qL[N * 2], qR[N * 2], fuck[N * 2], id[N << 2], wkr[N * 2];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    build(1, 1, n);
    LL cur = 0;
    for (int i = 1; i <= m; i++) {
        wkr[i] = i;
        int op, a; scanf("%d%d", &op, &a);
        if (op == 1) cur += a;
        else {
            fuck[i] = 1, x[i] = cur;
            int b; scanf("%d", &b), qL[i] = a, qR[i] = b;
        }
    }
    sort(wkr + 1, wkr + m + 1, [&](int a, int b) {
        return x[a] < x[b];
    });
    for (int i = 1; i <= all; i++) id[i] = i;
    sort(id + 1, id + all + 1, [&](int a, int b) {
        if (dep[a] != dep[b]) return dep[a] > dep[b];
        return T[a].l < T[b].l;
    });
    for (int l = 1, r; l <= all; l = r + 1) {
        r = l;
        while (r < all && dep[id[r + 1]] == dep[id[l]]) r++;
        for (int i = 1; i <= m; i++) if (fuck[wkr[i]]) 
            push(1, qL[wkr[i]], qR[wkr[i]], wkr[i], -1, dep[id[l]]);
        for (int i = l; i <= r; i++) solveL(id[i]);
        for (int i = r; i >= l; i--) solveR(id[i]);
    }
    for (int i = 1; i <= m; i++) if (fuck[i]) 
        printf("%lld\n", max(ansL[i], max(ansR[i], sufL[i] + preR[i])));
}