#include <bits/stdc++.h>
using namespace std;

const int N = 50010;

typedef long long LL;

struct line {
    int k; LL b;
    line operator+ (line t) { return { k + t.k, b + t.b }; }
    double get(double x) { return k * x + b; }
};

line tmp[N];
int sz;

bool check(line a, line b, line c) { 
    return (a.b - b.b) * (c.k - a.k) >= (a.b - c.b) * (b.k - a.k); 
}

void push(line l) {
    if (sz && l.k <= tmp[sz - 1].k)
        return;
    while (sz >= 2 && check(tmp[sz - 2], tmp[sz - 1], l)) sz--;
    tmp[sz++] = l;
}

void upd(line l) { tmp[l.k].b = max(tmp[l.k].b, l.b); }

void reduce() {
    int hh = sz;
    sz = 0;
    for (int i = 0; i < hh; i++) push(tmp[i]);
}

void add(vector<line> A, vector<line> B) {  // single point
    int p = 0, q = 0;
    int szA = A.size(), szB = B.size();
    while (p + 1 < szA || q + 1 < szB) {
        if (p + 1 == szA) { upd(A[p] + B[q++]); continue; }
        if (q + 1 == szB) { upd(A[p++] + B[q]); continue; }
        upd(A[p] + B[q]);
        LL a = (A[p].b - A[p + 1].b) * (B[q + 1].k - B[q].k);
        LL b = (B[q].b - B[q + 1].b) * (A[p + 1].k - A[p].k);
        if (a <= b) p++;
        if (b <= a) q++;
    }
    upd(A[p] + B[q]);
}

struct node {
    int l, r; 
    vector<line> val[2][2];
} T[N << 2];

void pushup(int rt) {
    int l = T[rt].l, r = T[rt].r;
    for (int a = 0; a <= 1; a++)
        for (int c = 0; c <= 1; c++) {
            sz = r - l + 2;
            for (int i = 0; i <= r - l + 1; i++) tmp[i] = { i, (LL)-1e12 };
            for (int b = 0; b <= 1; b++) 
                add(T[rt << 1].val[a][b], T[rt << 1 | 1].val[b][c]);
            reduce();
            for (int i = 0; i < sz; i++)
                T[rt].val[a][c].push_back(tmp[i]);
        }
            
}

int num[N];

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    int mid = (l + r) >> 1;
    if (l == r) {
        T[rt].val[0][0] = { {0, 0}, {1, num[l]} };
        T[rt].val[1][0] = { {0, max(0, num[l])}, {1, num[l]} };
        T[rt].val[0][1] = { {1, num[l]} };
        T[rt].val[1][1] = { {0, num[l]}, {1, num[l]} };
        return;
    }
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}

line nw[2];

line get(vector<line> &v, double x) {
    line t = v[0];
    int l = 1, r = (int)v.size() - 1, mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        double A = v[mid - 1].get(x), B = v[mid].get(x);
        if (A < B) t = v[mid], l = mid + 1;
        else r = mid - 1;
    }
    return t;
}

vector<int> zjk;

void process(double x) {
    for (auto rt : zjk) {
        line nxt[2] = { {0, (LL)-1e12}, {0, (LL)-1e12} };
        for (int a = 0; a <= 1; a++)
            for (int b = 0; b <= 1; b++) {
                line tmp = get(T[rt].val[a][b], x);
                double A = nw[a].get(x) + tmp.get(x);
                double B = nxt[b].get(x);
                if (A > B) nxt[b] = nw[a] + tmp;
            }
        nw[0] = nxt[0], nw[1] = nxt[1];
    }
}

void query(int rt, int start, int end) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) {
        zjk.push_back(rt);
        return;
    }
    if (start <= mid) query(rt << 1, start, end);
    if (end > mid) query(rt << 1 | 1, start, end);
}

int main() {
     freopen("sequence20.in", "r", stdin), freopen("sequence20.out", "w", stdout);
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &num[i]);
    }
    build(1, 1, n);
    while (q--) {
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        double tl = -5e8, tr = 5e8, mid; int fk = 0; line res;
        line wkr;
        zjk.clear(), query(1, l, r);
        for (int i = 1; i <= 35; i++) {
            mid = (tl + tr) / 2;
            nw[0] = {0, 0}, nw[1] = {0, (LL)-1e12};
            process(mid);
            if (nw[0].k <= k) tl = mid, res = nw[0], fk = nw[0].k;
            else wkr = nw[0], tr = mid;
            if (nw[0].k == k) break;
        }
        if (res.k == k) printf("%lld\n", res.b);
        else {
            int delta = (wkr.b - res.b) / (wkr.k - res.k);
            printf("%lld\n", res.b + delta * (k - res.k));
        }
    }
}
