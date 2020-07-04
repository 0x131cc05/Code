#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int eps = 1e-8;

struct Point {

double x, y;

Point(double x = 0, double y = 0) : x(x), y(y) {}

Point operator + (Point b) { return Point(x + b.x, y + b.y); }

Point operator - (Point b) { return Point(x - b.x, y - b.y); }

Point operator * (double d) {return Point(x * d, y * d);}

double operator ^ (Point b) { return x * b.y - y * b.x; }

} p[N];

struct Line { Point a, b; } l[N], q[N];

inline Point Inter(Line a, Line b) {
    double tot = (a.b - a.a) ^ (b.b - b.a), tmp = (b.b - b.a) ^ (a.a - b.a);
    return a.a + (a.b - a.a) * (tmp / tot);
}

inline double ang(Line x) {
    return atan2(x.b.y - x.a.y, x.b.x - x.a.x);
}

inline bool check(Line ls1, Line ls, Line nw) {
    Point t = Inter(ls, ls1);
    return ((t - nw.a) ^ (nw.b - nw.a)) >= 0;
}

int head, tail;

inline void SI(int n) {
    sort(l + 1, l + n + 1, [](Line a, Line b) {
        double A = ang(a), B = ang(b);
        if (fabs(A - B) > eps) return A < B;
        return ((b.b - b.a) ^ (a.b - b.b)) > 0;
    });
    int tot = 1;
    for (int i = 2; i <= n; i++) 
        if (fabs(ang(l[i]) - ang(l[i - 1]) > eps)) l[++tot] = l[i];
    head = 1, tail = 0;
    for (int i = 1; i <= tot; i++) {
        while (head <= tail - 1 && check(q[tail - 1], q[tail], l[i])) tail--;
        while (head <= tail - 1 && check(q[head], q[head + 1], l[i])) head++;
        q[++tail] = l[i];
    }
    while (head <= tail - 1 && check(q[head], q[head + 1], q[tail])) head++;
    while (head <= tail - 1 && check(q[tail - 1], q[tail], q[head])) tail--;
}

int main() {
    int n, tot = 0; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int t; scanf("%d", &t);
        for (int j = 1; j <= t; j++) scanf("%lf%lf", &p[j].x, &p[j].y);
        p[t + 1] = p[1];
        for (int j = 1; j <= t; j++) l[++tot] = (Line){ p[j], p[j + 1] };
    }
    SI(tot), q[tail + 1] = q[head]; double res = 0;
    if (tail <= head + 1) return puts("0.000"), 0;
    for (int i = head; i <= tail; i++) 
        p[i] = Inter(q[i], q[i + 1]);
    p[tail + 1] = p[head];
    for (int i = head; i <= tail; i++) res += p[i] ^ p[i + 1];
    printf("%.3lf\n", res / 2);
}