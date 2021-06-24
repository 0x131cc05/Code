#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<double, LL> P;

priority_queue<P> q;

LL C[21][21]; double p[4];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < 4; i++) scanf("%lf", &p[i]);
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    for (int a = 0; a <= n; a++)
        for (int b = 0; a + b <= n; b++) 
            for (int c = 0; a + b + c <= n; c++) {
                int d = n - a - b - c; LL w = C[n][a] * C[n - a][b] * C[n - a - b][c];
                q.push(P(-pow(p[0], a) * pow(p[1], b) * pow(p[2], c) * pow(p[3], d), w));
            }
    double ans = 0;
    while (233) {
        auto t = q.top(); q.pop();
        if (t.second == 1) {
            if (q.empty()) {
                printf("%.10lf", -ans); return 0;
            } 
            auto t1 = q.top(); q.pop();
            q.push(P(t.first + t1.first, 1)), ans += t.first + t1.first;
            if (t1.second > 1) q.push(P(t1.first, t1.second - 1));
        } else {
            if (t.second & 1) q.push(P(t.first, 1));
            q.push(P(t.first * 2, t.second / 2)), ans += t.first * (t.second / 2 * 2);
        }
    }
}
