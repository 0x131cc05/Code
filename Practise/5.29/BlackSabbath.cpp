#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);
const double eps = 1e-7;
const int N = 10010;

struct point {
    double x, y;
    point(double x = 0, double y = 0): x(x), y(y) {}
    point operator+ (point b) { return { x + b.x, y + b.y }; }
    point operator- (point b) { return { x - b.x, y - b.y }; }
    point operator* (double d) { return { x * d, y * d }; }
    double operator^ (point b) { return x * b.y - y * b.x; }
    double operator* (point b) { return x * b.x + y * b.y; }
};

point rotate(point x, double ang) {
    double a = sin(ang), b = cos(ang);
    return { x.x * b + x.y * a, x.x * -a + x.y * b };
}

struct line { 
    point a, b; 
    double ang() { return atan2(b.y - a.y, b.x - a.x); }
} q[N];

point inter(line a, line b) {
    double tot = (a.b - a.a) ^ (b.b - b.a), tmp = (b.b - b.a) ^ (a.a - b.a);
    return a.a + (a.b - a.a) * (tmp / tot);
}

double dis(point a, point b) {
    return sqrt((b - a) * (b - a));
}

bool check(line a, line b, line c) {
    point p = inter(a, b);
    return ((p - c.a) ^ (c.b - c.a)) > 0;
}

int head, tail;

vector<line> halfPlaneIntersection(vector<line> l) {
    int n = l.size();
    sort(l.begin(), l.end(), [](line a, line b) { 
        double g1 = a.ang(), g2 = b.ang();
        if (fabs(g1 - g2) > eps) return g1 < g2; 
        return ((b.b - a.a) ^ (a.b - a.a)) > eps;
    });
    double lst = 233; head = 1, tail = 0;
    for (int i = 0; i < n; i++) {
        double t = l[i].ang();
        if (fabs(t - lst) < eps) continue;
        lst = t;
        while (head < tail && check(q[tail - 1], q[tail], l[i])) tail--;
        while (head < tail && check(q[head], q[head + 1], l[i])) head++;
        q[++tail] = l[i];
    }
    while (head < tail && check(q[head], q[head + 1], q[tail])) head++;
    while (head < tail && check(q[tail - 1], q[tail], q[head])) tail--;
    l.clear();
    for (int i = head; i <= tail; i++) l.push_back(q[i]);
    return l;
}

int x[N], y[N], r[N];

int main() {
    int w, h, n; scanf("%d%d%d", &w, &h, &n);
    vector<line> base; 
    base.push_back({ { 0, 0 }, { w, 0 } });
    base.push_back({ { w, 0 }, { w, h } });
    base.push_back({ { w, h }, { 0, h } });
    base.push_back({ { 0, h }, { 0, 0 } });
    for (int i = 1; i <= n; i++) 
        scanf("%d%d%d", &x[i], &y[i], &r[i]);
    for (int i = 1; i <= n; i++) {
        vector<line> l = base;
        for (int j = 1; j <= n; j++) if (j != i) {
            point u(x[i], y[i]), v(x[j], y[j]);
            double d = dis(u, v);
            double t = d / 2 - (r[j] * r[j] - r[i] * r[i]) / d / 2;
            point p = u + (v - u) * (t / d), q = rotate(v - u, -PI / 2);
            l.push_back({ p, p + q });
        }
        l = halfPlaneIntersection(l);
        printf("%d\n", l.size()), l.push_back(l[0]);
        for (int i = 0; i + 1 < l.size(); i++) {
            point p = inter(l[i], l[i + 1]);
            printf("%.6lf %.6lf\n", p.x, p.y);
        }
    }
}