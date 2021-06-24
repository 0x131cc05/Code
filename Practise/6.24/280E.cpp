#include <bits/stdc++.h>
using namespace std;

#define double long double

const int N = 6010;
const double eps = 1e-7;

struct quadraticFunction {
    double a, b, c;
    double val(double pos) { return a * pos * pos + b * pos + c; }
    void move(double dis) { // right shift
        c += (a * dis - b) * dis;
        b -= 2 * a * dis;
    }
    double pos(double l, double r) {
        if (a < eps) return b > 0 ? l : r;
        double p = -b / 2 / a;
        if (l <= p && p <= r) return p;
        return p <= l ? l : r; 
    }
} f[N * 2];

double x[N], pos[N * 2], fuck[N];
double res[N];

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int n, q, a, b; cin >> n >> q >> a >> b;
    for (int i = 1; i <= n; i++) cin >> x[i];
    int tot = 1;
    pos[0] = 1, pos[1] = q; double ans = 0;
    for (int i = 1; i <= n + 1; i++) {
        if (i != 1) {
            double mn = 1e100, wkr = 0; int tar = 0;
            for (int j = 1; j <= tot; j++) {
                double p = f[j].pos(pos[j - 1], pos[j]);
                double val = f[j].val(p);
                if (val < mn) mn = val, tar = j, wkr = p;
            }
            fuck[i - 1] = wkr, ans = mn;
            if (i == n + 1) break;
            copy(f + tar, f + tot + 1, f + tar + 2);
            copy(pos + tar, pos + tot + 1, pos + tar + 2);
            tot += 2, f[tar + 1] = { 0, 0, mn };
            pos[tar] = wkr, pos[tar + 1] = wkr + b; 
            for (int i = tar + 2; i <= tot; i++) 
                pos[i] += b, f[i].move(b);
            for (int i = 0; i <= tar; i++)
                pos[i] += a, f[i].move(a);
            while (tot >= 2 && pos[tot - 1] >= q - eps) tot--;
            pos[tot] = q;
        }
        for (int j = 1; j <= tot; j++) 
            f[j].a++, f[j].b -= 2 * x[i], f[j].c += x[i] * x[i];
    }
    res[n] = fuck[n];
    for (int i = n - 1; i >= 1; i--) {
        if (fuck[i] < res[i + 1] - b) res[i] = res[i + 1] - b;
        else if (fuck[i] > res[i + 1] - a) res[i] = res[i + 1] - a;
        else res[i] = fuck[i];
    }
    cout << fixed << setprecision(6);
    for (int i = 1; i <= n; i++) cout << res[i] << ' ';
    cout << endl << ans << endl;
}