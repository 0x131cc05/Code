#include <bits/stdc++.h>
using namespace std;
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define loop(i, a) for (int i = 0; i < (a); ++i)
#define cont(i, a) for (int i = 1; i <= (a); ++i)
#define circ(i, a, b) for (int i = (a); i <= (b); ++i)
#define range(i, a, b, c) for (int i = (a); (c) > 0 ? i <= (b) : i >= (b); i += (c))
#define parse(it, x) for (auto &it : (x))
#define pub push_back
#define pob pop_back
#define emb emplace_back
#define mak make_pair
#define mkt make_tuple
typedef long long ll;
typedef long double lf;
const int Inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

int n, q;

struct Point {
    int x; ll y;
	Point() : x(0), y(0) {}
	Point(int x, ll y) : x(x), y(y) {}
	Point inline operator + (const Point &p) const { return Point(x + p.x, y + p.y); }
	Point inline operator - (const Point &p) const { return Point(x - p.x, y - p.y); }
	ll inline operator * (const Point &p) const { return x * p.y - y * p.x; }
	ll inline operator % (const Point &p) const { return x * p.x + y * p.y; }
    bool operator < (const Point &p) const { return y * p.x > x * p.y; }
    void inline update(const Point &p) { if (y < p.y || (y == p.y && x < p.x)) x = p.x, y = p.y; }
};

struct Hull {
    vector<Point> ps;
    int ptr;
    Hull() : ptr(0) {}
    void init() { ps.clear(); ps.emb(0, 0); }
    void init(Point p) { ps.clear(); ps.emb(0, -1e12); ps.pub(p); }
    void inline append(Point p) {
        while(SZ(ps) > 1 && (ps[SZ(ps) - 2] - ps.back()) * (p - ps.back()) <= 0) ps.pob();
        if (SZ(ps) >= 1 && ps.back().x == p.x) {
            if (ps.back().y < p.y) ps.pob();
            else return;
        }
        ps.pub(p);
    }
    void inline merge(const Hull &h) {
        vector<Point> p1, p2;
        cont(i, SZ(ps) - 1) p1.pub(ps[i] - ps[i - 1]);
        cont(i, SZ(h.ps) - 1) p2.pub(h.ps[i] - h.ps[i - 1]);
        Point ini = ps[0] + h.ps[0];
        ps.clear(); ps.pub(ini);
        int pt1 = 0, pt2 = 0;
        Point pre = ini;
        while (pt1 < SZ(p1) && pt2 < SZ(p2)) {
            if (p1[pt1] < p2[pt2]) ps.pub(pre = pre + p1[pt1++]);
            else ps.pub(pre = pre + p2[pt2++]);
        }
        while (pt1 < SZ(p1)) ps.pub(pre = pre + p1[pt1++]);
        while (pt2 < SZ(p2)) ps.pub(pre = pre + p2[pt2++]);
    }
    void inline chmax(const Hull &h) {
        vector<Point> pts; ps.swap(pts);
        int pt1 = 0, pt2 = 0;
        while (pt1 < SZ(pts) && pt2 < SZ(h.ps)) {
            if (pts[pt1].x < h.ps[pt2].x) append(pts[pt1++]);
            else append(h.ps[pt2++]);
        }
        while (pt1 < SZ(pts)) append(pts[pt1++]);
        while (pt2 < SZ(h.ps)) append(h.ps[pt2++]);
    }
    Point getval(ll k) {
        while (ptr < SZ(ps) - 1 && k * ps[ptr].x + ps[ptr].y <= k * ps[ptr + 1].x + ps[ptr + 1].y) ++ptr;
        return Point(ps[ptr].x, k * ps[ptr].x + ps[ptr].y);
    }
};

const int maxn = 1 << 16;
int a[maxn];

struct Answer {
    Point h[2][2];
    Answer() { loop(i, 2) loop(j, 2) h[i][j] = Point(0, -1e12); }
    friend Answer inline operator + (const Answer &a, const Answer &b) {
        Answer res;
        loop(i, 2) loop(j, 2) loop(k, 2) res.h[i][j].update(a.h[i][k] + b.h[k][j]);
        return res;
    }
};

struct Segtree {
    Hull h[maxn << 1][2][2];
    void inline init(int now = 1, int nl = 1, int nr = n) {
        if (nl == nr) {
            h[now][0][0].init();
            h[now][0][1].init(Point(1, a[nl]));
            h[now][1][0].init();
            h[now][1][1].init(Point(1, a[nl]));
            h[now][1][1].ps[0] = Point(0, a[nl]);
            return;
        }
        int m = (nl + nr) >> 1;
        init(now << 1, nl, m);
        init(now << 1 | 1, m + 1, nr);
        loop(i, 2) loop(j, 2) {
            h[now][i][j].ps.emb(0, -1e12);
        }
        loop(i, 2) loop(j, 2) loop(k, 2) {
            Hull tmp = h[now << 1][i][k];
            tmp.merge(h[now << 1 | 1][k][j]);
            if (i == 0 && j == 0 && k == 0)assert(tmp.ps[0].y == 0);
            h[now][i][j].chmax(tmp);
        }
        assert(h[now][0][0].ps[0].y == 0);
    }
    void inline reinit(int now = 1, int nl = 1, int nr = n) {
        loop(i, 2) loop(j, 2) h[now][i][j].ptr = 0;
        if (nl == nr) return;
        int m = (nl + nr) >> 1;
        reinit(now << 1, nl, m);
        reinit(now << 1 | 1, m + 1, nr);
    }
    Answer inline query(int l, int r, ll k, int now = 1, int nl = 1, int nr = n) {
        if (nl >= l && nr <= r) {
            Answer res;
            loop(i, 2) loop(j, 2) res.h[i][j] = h[now][i][j].getval(k);
            return res;
        }
        int m = (nl + nr) >> 1;
        if (m >= l) {
            Answer res = query(l, r, k, now << 1, nl, m);
            if (m < r) res = res + query(l, r, k, now << 1 | 1, m + 1, nr);
            return res;
        }
        return query(l, r, k, now << 1 | 1, m + 1, nr);
    }
} seg;

int ql[maxn], qr[maxn], qk[maxn];
ll L[maxn], R[maxn];
ll Ans[maxn];
int ord[maxn];

int main() {
    #ifndef Acetyl
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    #endif
    scanf("%d%d", &n, &q);
    cont(i, n) scanf("%d", a + i);
    seg.init();
    cont(i, q) {
        scanf("%d%d%d", ql + i, qr + i, qk + i);
        ord[i] = i;
        L[i] = -2e9; R[i] = 2e9;
    }
    loop(i, 32) {
        sort(ord + 1, ord + q + 1, [&] (int a, int b) { return L[a] + R[a] < L[b] + R[b]; });
        seg.reinit();
        cont(J, q) {
            int j = ord[J];
            ll m = (L[j] + R[j]) >> 1;
            Answer ans = seg.query(ql[j], qr[j], m);
            Point res = ans.h[0][0];
            if (ans.h[0][1].y > res.y) res = ans.h[0][1];
            if (res.x >= qk[j]) R[j] = m;
            else L[j] = m;
        }
    }
    sort(ord + 1, ord + q + 1, [&] (int a, int b) { return R[a] < R[b]; });
    seg.reinit();
    cont(I, q) {
        int i = ord[I];
        Answer ans = seg.query(ql[i], qr[i], R[i]);
        Point res = ans.h[0][0];
        if (ans.h[0][1].y > res.y) res = ans.h[0][1];
        Ans[i] = res.y - qk[i] * R[i];
    }
    cont(i, q) printf("%lld\n", Ans[i]);
    return 0;
}
/*

6 5
-1 3 -1 2 3 -1
1 4 2
2 5 1
3 4 2
1 3 2
1 1 1

10 10
-3 4 2 -5 1 2 4 -3 2 1
2 6 2
3 9 2
1 5 1
5 9 3
1 10 7
1 4 4
6 9 2
4 8 1
2 9 5
2 5 2

*/