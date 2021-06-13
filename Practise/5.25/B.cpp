#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

struct item {
    int zero, one, lst;
    void init(int x) {
        zero = one = lst = 0;
        if (x == 0) lst = 1;
        else one = 1;
    }
    int len() { return zero + one + lst; }
    void merge(item b) {
        int tot = lst + b.zero, remain;
        if (tot & 1) remain = one + b.one - 2 * min(one, b.one);
        else remain = one + b.one;
        item res = { len() + b.len() - remain - b.lst, remain, b.lst };
        if ((tot & 1) && one > b.one) {
            if (res.lst) res.zero++, res.lst = 0;
            else if (res.zero) res.lst = 1, res.zero--;
        }
        if (!res.one && !res.lst) res.lst = 1, res.zero--; 
        *this = res;
    }
};

struct node {
    int l, r; item res;
} T[N << 2];

void pushup(int rt) {
    T[rt].res = T[rt << 1].res, T[rt].res.merge(T[rt << 1 | 1].res);
}

int num[N];

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return T[rt].res.init(num[l] & 1), void();
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r), pushup(rt);
    // cout << T[rt].res.zero << ' ' << T[rt].res.one << ' ' << T[rt].res.lst << ' ' << l << ' ' << r << endl;
}

void update(int rt, int pos, int x) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (l == r) return T[rt].res.init(x & 1), void();
    if (pos <= mid) update(rt << 1, pos, x);
    else update(rt << 1 | 1, pos, x);
    pushup(rt);
}

item fuck;

void query(int rt, int start, int end) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) return fuck.merge(T[rt].res), void();
    if (start <= mid) query(rt << 1, start, end);
    if (end > mid) query(rt << 1 | 1, start, end);
}

int tree[N], n;

void upd(int x, int y) {
    for (; x <= n; x += x & -x) tree[x] += y;
}

int que(int x) {
    int res = 0;
    for (; x; x -= x & -x) res += tree[x];
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) 
        scanf("%d", &num[i]), upd(i, !!num[i]);
    build(1, 1, n);
    int q; scanf("%d", &q);
    while (q--) {
        int op, a, b; scanf("%d%d%d", &op, &a, &b);
        if (op == 1) upd(a, -!!num[a]), num[a] = b, upd(a, !!num[a]), update(1, a, b);
        else {
            fuck = {0, 0, 0}, query(1, a, b);
            // cout << fuck.one << ' ' << fuck.zero << ' ' << fuck.lst << endl;
            int sum = que(b) - que(a - 1);
            if (!sum) printf("%d\n", b - a + 1);
            else {
                int zero = b - a + 1 - sum;
                printf("%d\n", max(zero, fuck.zero));
            }
        }
    }
}