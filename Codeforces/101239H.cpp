#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

double x[N];

int main() {
    int w, h, n; cin >> w >> h >> n;
    double k = (double)(w * w - h * h) / (2 * w * w);
    x[1] = 1;
    for (int i = 2; i <= n + 1; i++) 
        x[i] = x[i - 1] / k - x[i - 2];
    double t = 1 / x[n + 1], res = 0; x[n + 1] = w;
    for (int i = 1; i <= n; i++) x[i] *= w * t;
    for (int i = 1; i <= n + 1; i++) {
        double l = x[i] - x[i - 1] + x[i] / w * h + x[i - 1] / w * h;
        res += l * l / 4;
    }
    for (int i = 1; i <= n; i++) {
        double t = x[i] / w * h;
        res -= t * t / 2;
    }
    printf("%.6lf\n", res);
    for (int i = 1; i <= min(n, 10); i++) printf("%.6lf\n", x[i]);
}