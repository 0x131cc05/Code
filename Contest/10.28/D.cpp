#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct line {
    int k, b;
    int get(int x) { return x * k + b; }
} L[N * 32];

int lson[N * 32], rson[N * 32], ncnt;

void update(int &rt, int l, int r, line k) {
    if (!rt) return L[rt = ++ncnt] = k, void();
    int mid = (l + r) >> 1;
    if (k.get(mid) > L[rt].get(mid)) swap(L[rt], k);
    if (k.get(l) > L[rt].get(l)) update(lson[rt], l, mid, k);
    if (k.get(r) > L[rt].get(r)) update(rson[rt], mid + 1, r, k);
} 

int query(int rt, int l, int r, int pos) {
    if (!rt) return -1e9;
    int res = L[rt].get(pos);
    if (l == r) return res;
    int mid = (l + r) >> 1;
    if (pos <= mid) return max(res, query(lson[rt], l, mid, pos));
    else return max(res, query(rson[rt], mid + 1, r, pos));
}

int tree[N], n, m;

void update(int x, line k) {
    for (; x <= m; x += x & -x) update(tree[x], 1, n + m, k);
}

int query(int x, int pos) {
    int res = 0;
    for (; x; x -= x & -x) res = max(res, query(tree[x], 1, n + m, pos));
    return res;
}

template<class T> void read(T &x) {
    x = 0; char c = getchar(); bool flag = false;
    while (!isdigit(c)) flag |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (flag) x = -x;
}

template<class T, typename... Tail> void read(T &x, Tail&... tail) {
   read(x), read(tail...);
}

vector<int> A, B;

int main() {
    read(n, m);
    for (int i = 1, a; i <= n * m; i++) read(a), B.push_back(a);
    for (int i = 1, a; i <= n * m; i++) read(a), A.push_back(a);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int id = (i - 1) * m + j, nw = query(j, i + j);
            // cout << i << ' ' << j << ' ' << nw << ' ' << A[id - 1] << ' ' << B[id - 1] << endl;
            if (id == n * m) return printf("%d", nw), 0;
            update(j, { B[id - 1], -(i + j) * B[id - 1] + nw + A[id - 1]});
        }
}