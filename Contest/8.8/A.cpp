#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const double eps = 1e-10;

typedef long long LL;
typedef pair<double, double> P;

struct Line {
    double l, r; int pos;
    bool operator < (const Line &b) const {
        return l < b.l;
    }
} l1[N], l2[N];

int tot1, tot2;

int L, R, x[N], y[N], n, q[N], ok[N]; double cast[N], st[N], res[N];

double inter(int a, int b) {
    return (double)(y[a] - y[b]) / (x[a] - x[b]); 
}

set<P> s;

void push(Line line[], int &tot, double l, double r, int pos) {
    // cout << "push: " << l << ' ' << r << ' ' << pos << endl;
    auto p = s.lower_bound(P(l - eps, r));
    double ls = l, mx = r; 
    while (p != s.begin()) {
        auto q = p; q--;
        if (q -> first >= l - eps) p--;
        else break;
    } 
    if (p != s.begin()) {
        auto q = p; q--;
        ls = max(ls, q -> second);
    }
    while (p != s.end() && p -> first <= r + eps) {
        if (ls + eps < p -> first) line[++tot] = (Line){ ls, p -> first, pos };
        ls = p -> second;
        s.erase(p++), mx = max(mx, ls);
    }
    s.insert(P(l, mx));
    if (ls < r - eps) line[++tot] = (Line){ ls, r, pos };
    // cout << "end" << endl;
}

void rightSide() {
    int top = 0;
    for (int i = n; i >= 1; i--) {
        double st = (double)(R - L) / (R - x[i]); ok[i] = 0;
        // cout << st << endl;
        while (top >= 2 && inter(q[top], q[top - 1]) >= st - eps) top--;
        if (top && y[q[top]] + (R - x[q[top]]) * st >= y[i] + (R - x[i]) * st - eps) {
            // cout << y[q[top]] << ' ' << y[q[top]] + (R - x[q[top]]) * st << endl;
            continue;
        }
        ok[i] = 1, ::st[i] = st;
        while (top >= 2 && inter(q[top], q[top - 1]) >= inter(i, q[top]) + eps) top--;
        q[++top] = i, cast[i] = top == 1 ? -1e9 : inter(i, q[top - 1]);
    }
    s.clear();
    for (int i = 1; i <= n; i++) if (ok[i]) {
        cast[i] = max(cast[i], 1.);
        if (cast[i] + eps < st[i])
            push(l1, tot1, cast[i], st[i], i);
    }
        
}

void leftSide() {
    int top = 0;
    // cout << "start" << endl;
    for (int i = 1; i <= n; i++) {
        double st = (double)(R - L) / (x[i] - L); ok[i] = 0;
        // cout << "st: " << st << endl;
        while (top >= 2 && -inter(q[top], q[top - 1]) >= st - eps) top--;
        if (top && y[q[top]] + (x[q[top]] - L) * st >= y[i] + (x[i] - L) * st - eps) {
            // cout << y[q[top]] + (x[q[top]] - L) * st << endl;
            continue;
        }
        ok[i] = 1, ::st[i] = st;
        while (top >= 2 && -inter(q[top], q[top - 1]) >= -inter(i, q[top]) - eps) top--;
        q[++top] = i, cast[i] = top == 1 ? -1e9 : -inter(i, q[top - 1]);
    }
    // cout << "end" << endl;
    s.clear();
    for (int i = n; i >= 1; i--) if (ok[i]) {
        cast[i] = max(cast[i], 1.);
        if (cast[i] + eps <= st[i])
            push(l2, tot2, cast[i], st[i], i);
    }
        
}

vector<double> fuck;

int main() {
    scanf("%*d%d%d%d", &n, &L, &R);
    for (int i = 1; i <= n; i++) scanf("%d", &x[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &y[i]);
    rightSide(), leftSide();
    for (int i = 1; i <= tot1; i++) 
        l1[i].l = R - (R - L) / l1[i].l, l1[i].r = R - (R - L) / l1[i].r;
    for (int i = 1; i <= tot2; i++) 
        l2[i].l = (R - L) / l2[i].l + L, l2[i].r = (R - L) / l2[i].r + L, swap(l2[i].l, l2[i].r);
    sort(l1 + 1, l1 + tot1 + 1), sort(l2 + 1, l2 + tot2 + 1);
    fuck.push_back(L), fuck.push_back(R);
    for (int i = 1; i <= tot1; i++) fuck.push_back(l1[i].l), fuck.push_back(l1[i].r);
    for (int i = 1; i <= tot2; i++) fuck.push_back(l2[i].l), fuck.push_back(l2[i].r);
    sort(fuck.begin(), fuck.end()), fuck.resize(unique(fuck.begin(), fuck.end()) - fuck.begin());
    // for (int i = 1; i <= tot1; i++) cout << l1[i].l << ' ' << l1[i].r << endl;
    // for (int i = 0; i < fuck.size(); i++) cout << fuck[i] << ' ';
    // cout << endl;
    for (int i = 0, t1 = 1, t2 = 1; i + 1 < fuck.size(); i++) {
        double l = fuck[i], r = fuck[i + 1];
        while (t1 <= tot1 && l1[t1].r <= l + eps) t1++;
        while (t2 <= tot2 && l2[t2].r <= l + eps) t2++;
        if (t1 <= tot1 && t2 <= tot2) {
            if (l1[t1].l >= r - eps) res[l2[t2].pos] += r - l;
            else if (l2[t2].l >= r - eps) res[l1[t1].pos] += r - l;
            else {
                double L1 = l, R1 = r, mid; int a = l1[t1].pos, b = l2[t2].pos;
                for (int j = 1; j <= 50; j++) {
                    mid = (L1 + R1) / 2;
                    double left = (x[b] - L) / (mid - L) * (R - L) + y[b];
                    double right = (R - x[a]) / (R - mid) * (R - L) + y[a];
                    if (left > right) L1 = mid;
                    else R1 = mid;
                }
                // cout << l << ' ' << r << ' ' << L1 << ' ' << a << ' ' << b << endl;
                res[a] += r - L1, res[b] += L1 - l;
            } 
        } else {
            if (t1 > tot1) res[l2[t2].pos] += r - l;
            else res[l1[t1].pos] += r - l;
        }
    }
    for (int i = 1; i <= n; i++) printf("%.11lf\n", res[i] / (R - L));
}