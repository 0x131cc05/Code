#include <bits/stdc++.h>
using namespace std;

const int N = 15;
const double eps = 1e-7;
const double PI = acos(-1);

struct point {
    double x, y;
    point operator+ (point b) { return { x + b.x, y + b.y }; }
    point operator- (point b) { return { x - b.x, y - b.y }; }
    point operator/ (double b) { return { x / b, y / b }; }
    point operator* (double b) { return { x * b, y * b }; }
    point normal() { return { -y, x }; }
} wkr[N];

struct cir {
    point p; double r;
};

double dis(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double angle(point a) {
    return atan2(a.y, a.x);
}

bool inter(cir c1, cir c2, point &a, point &b) {
    double d = dis(c1.p, c2.p);
    if (d >= c1.r + c2.r - eps) return false;
    if (d <= fabs(c1.r - c2.r) + eps) return false;
    double base = angle(c2.p - c1.p);
    double offset = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    a = c1.p + (point){ cos(base + offset) * c1.r, sin(base + offset) * c1.r };
    b = c1.p + (point){ cos(base - offset) * c1.r, sin(base - offset) * c1.r };
    return true;
}

int n; double mid;

bool check(point p) {
    for (int i = 1; i <= n; i++) 
        if (dis(p, wkr[i]) <= 1 - eps) return false;
    for (int i = 1; i <= n; i++) 
        for (int j = i + 1; j <= n; j++) {
            double g = angle(wkr[i] - p) - angle(wkr[j] - p);
            if (g < 0) g += 2 * PI;
            if (g > PI) g = 2 * PI - g;
            if (g < mid - eps) return false;
        }
    return true;
}

point res;

bool process() {
    vector<cir> tmp;
    for (int i = 1; i <= n; i++) tmp.push_back({ wkr[i], 1 });
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            double d = dis(wkr[i], wkr[j]);
            point c = (wkr[i] + wkr[j]) / 2;
            point offset = (wkr[j] - wkr[i]).normal() / (2 * tan(mid));
            double r = d / 2 / sin(mid);
            tmp.push_back({ c + offset, r }), tmp.push_back({ c - offset, r });
        }
    for (int i = 0; i < tmp.size(); i++)
        for (int j = i + 1; j < tmp.size(); j++) {
            point a, b;
            if (inter(tmp[i], tmp[j], a, b)) {
                if (check(a)) { res = a; return true; }
                if (check(b)) { res = b; return true; }
            }
        }
    return false;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> wkr[i].x >> wkr[i].y;
    double l = 0, r = PI;
    for (int i = 1; i <= 40; i++) {
        mid = (l + r) / 2;
        if (process()) l = mid;
        else r = mid;
    } 
    printf("%.6lf %.6lf\n", res.x, res.y);
}