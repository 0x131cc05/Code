#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const double PI = acos(-1);

double x[N], y[N];

int main() {
    int n; cin >> n;
    if (n <= 4) return puts("No solution"), 0;
    double d = 300;
    double delta = 2 * PI / n;
    for (int i = 1; i <= n; i++) {
        d += 0.01;
        double ang = delta * (i - 1);
        double dx = cos(ang) * d, dy = sin(ang) * d;
        x[i] = x[i - 1] + dx, y[i] = y[i - 1] + dy;
    }
    double tmp = 1 + y[n] / (y[n - 1] - y[n]);
    x[n] = x[n - 1] + (x[n] - x[n - 1]) * tmp, y[n] = 0;
    for (int i = 1; i <= n; i++) printf("%.5lf %.5lf\n", x[i], y[i]);
}