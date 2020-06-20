#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL x, y;

LL exgcd(LL a, LL b) {
    if (b == 0) return x = 1, y = 0, a;
    LL tmp = exgcd(b, a % b), t = x;
    return x = y, y = t - a / b * y, tmp;
}

inline LL excrt(LL A[], LL P[], int n) {
    LL lcm = P[1], a = A[1];
    for (int i = 2; i <= n; i++) {
        LL t = exgcd(lcm, P[i]), delta = A[i] - a, fuck = P[i] / t;
        if (delta % t) return -1; 
        x = x * (delta / t), x = (x % fuck + fuck) % fuck;
        a = x * lcm + a, lcm *= fuck;
    }
    return a;
}

const double eps = 1e-8;

inline double Abs(double x) {
    return x > 0 ? x : -x;
}

inline void normal(vector<double> &p) {
    double sum = 0;
    for (auto t : p) sum += t;
    for (auto &t : p) t /= sum;
}

double dfs(vector<double> &p, int remain) {
    assert((int)p.size() == remain); 
    if (remain == 2) {
        if (Abs(p[0] - p[1]) < eps) return 0.5;
        return p[0] < p[1] ? 0 : 1;
    }
    double mx = *max_element(p.begin(), p.end()), res = 0; int ct = 0, pos = 0;
    for (int i = 0; i < remain; i++) if (Abs(p[i] - mx) < eps) 
        ct++, pos = i;
    double mn1 = 1, mn2 = 1;
    if (Abs(p[0] - mx) < eps) {
        for (int i = 1; i < remain; i++) {
            vector<double> p1(1, 0); p1[0] = p[0] / (remain - 1);
            for (int j = 1; j < remain; j++) if (i != j) 
                p1.push_back(p[j] / (remain - 2));
            normal(p1), mn1 = min(mn1, dfs(p1, remain - 1));
        }
        res += mn1 / ct;
    }
    if (pos) {
        for (int i = 1; i < remain; i++) if (i != pos) {
            vector<double> p1; 
            for (int j = 0; j < remain; j++) if (i != j) {
                if (j != pos) p1.push_back(p[j] / (remain - 2));
                else p1.push_back(p[j] / (remain - 1));
            }
            normal(p1), mn2 = min(mn2, dfs(p1, remain - 1));
        }
        if (Abs(p[0] - mx) < eps) res += mn2 * (ct - 1) / ct;
        else res += mn2;
    }
    return res;
}

const int N = 50010;

LL A[N], P[N];

int main() {
    int T; scanf("%d", &T);
    for (int i = 1; i <= T; i++) scanf("%lld%lld", &A[i], &P[i]);
    LL n = excrt(A, P, T);
    if (n == -1 || n < 2) return puts("error"), 0;
    if (n > 10) return puts("0.000000"), 0;
    vector<double> p;
    for (int i = 1; i <= n; i++) p.push_back(1.0 / n);
    printf("%.6lf\n", dfs(p, n));
}
