#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

typedef long long LL;

typedef pair<int, int> P;

struct node {
    int l, r;
} T[N << 2];

vector<P> A[N << 2], B[N << 2];

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
}

void update(int rt, int start, int end, int y, int id) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    A[rt].push_back(P(y, id));
    if (start <= l && r <= end) return B[rt].push_back(P(y, id)), void();
    if (start <= mid) update(rt << 1, start, end, y, id);
    if (end > mid) update(rt << 1 | 1, start, end, y, id);
}

int vis[N];

inline void check(int rt) {
    while (A[rt].size() && vis[A[rt].back().second]) A[rt].pop_back();
    while (B[rt].size() && vis[B[rt].back().second]) B[rt].pop_back();
}

inline P merge(P a, P b) {
    return a.first > b.first ? a : b;
}

P query(int rt, int start, int end) {
    int l = T[rt].l, r = T[rt].r; P res(-1e9, 0); check(rt);
    if (B[rt].size()) res = B[rt].back();
//    cout << l << ' ' << r << ' ' << start << ' ' << end << ' ' << res.first << endl;
    if (start <= l && r <= end) {
        if (A[rt].size()) return A[rt].back();
        return res;
    }
    int mid = (l + r) >> 1;
    if (start <= mid) res = merge(res, query(rt << 1, start, end));
    if (end > mid) res = merge(res, query(rt << 1 | 1, start, end));
    return res;
}

int n, m, k;

struct tcurts {
    
int x, y;

bool operator < (const tcurts &b) const {
    return y < b.y;
}

} p[N];

int X[N], Y[N], mX[N], mY[N];

inline void fuck(int a, int b) {
//    cout << "fuck: " << a << ' ' << b << endl;
    X[a] = min(X[a], X[b]), Y[a] = min(Y[a], Y[b]);
    mX[a] = max(mX[a], mX[b]), mY[a] = max(mY[a], mY[b]);
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++) scanf("%d%d", &p[i].x, &p[i].y);
    sort(p + 1, p + k + 1), build(1, 1, n);
    for (int i = 1; i <= k; i++) {
        X[i] = mX[i] = p[i].x, Y[i] = mY[i] = p[i].y; 
        while (233) {
            P res = query(1, X[i] - 2, mX[i] + 2);
            if (res.first >= Y[i]) 
                vis[res.second] = 1, fuck(i, res.second);
            else {
                res = query(1, X[i] - 1, mX[i] + 1);
                if (res.first >= Y[i] - 1)
                    vis[res.second] = 1, fuck(i, res.second);
                else {
                    res = query(1, X[i], mX[i]);
                    if (res.first >= Y[i] - 2)
                        vis[res.second] = 1, fuck(i, res.second);
                    else break;
                }
            }
        }
        update(1, X[i], mX[i], mY[i], i);
//        cout << "update: " << X[i] << ' ' << mX[i] << ' ' << mY[i] << endl;
    }
    LL res = 0;
    for (int i = 1; i <= k; i++) if (!vis[i]) 
        res += (LL)(mX[i] - X[i] + 1) * (mY[i] - Y[i] + 1);
    printf("%lld\n", res);
}
