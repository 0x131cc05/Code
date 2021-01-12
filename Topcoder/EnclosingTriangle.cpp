#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> P;

const int N = 234400;

struct node {
    int l, r, tag; LL sum;
} T[N << 2];

void build(int rt, int l, int r) {
    T[rt].l = l, T[rt].r = r;
    int mid = (l + r) >> 1;
    if (l == r) return;
    build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
} 

void pushdown(int rt) {
    if (!T[rt].tag) return;
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    T[rt << 1].sum += (LL)(mid - l + 1) * T[rt].tag, T[rt << 1].tag += T[rt].tag;
    T[rt << 1 | 1].sum += (LL)(r - mid) * T[rt].tag, T[rt << 1 | 1].tag += T[rt].tag;
    T[rt].tag = 0;
}

void pushup(int rt) {
    T[rt].sum = T[rt << 1].sum + T[rt << 1 | 1].sum;
}

void update(int rt, int start, int end, int x) {
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) {
        T[rt].sum += (LL)(r - l + 1) * x;
        T[rt].tag += x;
        return;
    }
    pushdown(rt);
    if (start <= mid) update(rt << 1, start, end, x);
    if (end > mid) update(rt << 1 | 1, start, end, x);
    pushup(rt);
}

LL query(int rt, int start, int end) {
    if (start > end) return 0;
    int l = T[rt].l, r = T[rt].r, mid = (l + r) >> 1;
    if (start <= l && r <= end) return T[rt].sum;
    pushdown(rt);
    LL res = 0;
    if (start <= mid) res += query(rt << 1, start, end);
    if (end > mid) res += query(rt << 1 | 1, start, end);
    return res;
}

P seg[N];

bool check(P a, P b, P c) {
    int x1 = b.first - a.first, y1 = b.second - a.second;
    int x2 = c.first - a.first, y2 = c.second - a.second;
    return (LL)x1 * y2 - (LL)y1 * x2 >= 0;
}

class EnclosingTriangle {
public:
    LL getNumber(int m, vector<int> x, vector<int> y) {
        vector<P> pos;
        for (int i = 0; i <= m; i++) pos.push_back(P(i, 0));
        for (int i = 1; i <= m; i++) pos.push_back(P(m, i));
        for (int i = m - 1; i >= 0; i--) pos.push_back(P(i, m));
        for (int i = m - 1; i >= 1; i--) pos.push_back(P(0, i));
        // for (auto t : pos) cout << t.first << ' ' << t.second << endl;
        int n = pos.size(), p = x.size();
        build(1, 0, n);
        int p1 = 0, p2 = n;
        auto fuck = [&](P a, P b) {
            for (int j = 0; j < p; j++) 
                if (!check(a, b, P(x[j], y[j]))) return false;
            return true;
        };
        for (int i = n - 1; i >= 1; i--) {
            if (!fuck(pos[i], P(0, 0))) break;
            p2 = i;
        }
        // cout << p2 << endl;
        int cur = p1;
        for (int i = 0; i < n; i++) {
            cur = max(cur, i);
            while (cur + 1 < n && fuck(pos[i], pos[cur + 1])) cur++;
            seg[i].first = i + 1, seg[i].second = cur;  
            // cout << "at: " << pos[i].first << ' ' << pos[i].second << ' ' << pos[cur].first << ' ' << pos[cur].second << endl;
        }
        LL res = 0;
        for (int i = 0; i < n; i++) {
            if (i && seg[i].first <= seg[i].second) update(1, seg[i].first, seg[i].second, -1);
            p1 = max(p1, i + 1);
            while (p1 <= seg[i].second) {
                update(1, seg[p1].first, seg[p1].second, 1);
                p1++;
            }
            while (p2 < n && !fuck(pos[p2], pos[i])) p2++;
            // if (p2 < n)
            // cout << "p2: " << i << ' ' << pos[p2].first << ' ' << pos[p2].second << endl;
            res += query(1, p2, n - 1);
        }
        return res;
    }
};

// int main() {
//     EnclosingTriangle solver;
//     cout << solver.getNumber(
// 15,
// { 7, 6, 5, 4, 3 },
// { 1, 4, 7, 10, 13 }
// ) << endl;
// }