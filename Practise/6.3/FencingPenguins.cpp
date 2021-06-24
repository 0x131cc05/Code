#include <bits/stdc++.h>
using namespace std;

const int N = 230;
const int mod = 1e5 + 7;
const double PI = acos(-1);
const double eps = 1e-7;

typedef long long LL;

bool ok[N][N]; 
int ct[N][N], f[N][N], g[2][2][N][N];

int F(int l, int r);

int G(int fir, int flag, int l, int r) {
    if (l == r) return fir == 0 && flag;
    if (~g[fir][flag][l][r]) return g[fir][flag][l][r];
    int &res = g[fir][flag][l][r]; res = 0;
    for (int mid = l + 1; mid <= r; mid++) if (ok[l][mid]) {
        if (fir && mid == r) continue;
        if (ct[l + 1][mid - 1] < ct[l][mid]) continue;
        res = (res + (LL)F(l + 1, mid - 1) * G(0, flag || (ct[l][mid] + ct[mid][r] != ct[l][r]), mid, r)) % mod;
    }
    return res;
}

int F(int l, int r) {
    if (!ct[l][r]) return 1;
    if (~f[l][r]) return f[l][r];
    int &res = f[l][r]; res = 0;
    for (int mid = l; mid < r; mid++)
        for (int t = mid + 1; t <= r; t++) 
            if (ok[mid][t] && ct[mid][t] + ct[t + 1][r] == ct[l][r]) {
                res = (res + (LL)G(1, 0, mid, t) * F(t + 1, r)) % mod;
            }
    return res;
}

double X[N], Y[N];

bool cross(double x1, double y1, double x2, double y2) {
    return x1 * y2 - y1 * x2 > eps;
}

struct FencingPenguins {
    int countWays(int n, int r, vector<int> x, vector<int> y, string color) {
        double delta = 2 * PI / n;
        int m = x.size();
        for (int i = 0; i < n; i++) {
            X[i] = cos(delta * i) * r;
            Y[i] = sin(delta * i) * r;
        }
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++) ok[i][j] = true;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                static int tp[N]; memset(tp, -1, sizeof(tp));
                bool flag = true;
                for (int t = 0; t < m; t++) {
                    bool type = cross(X[i] - X[j], Y[i] - Y[j], x[t] - X[j], y[t] - Y[j]);
                    if (type) ct[i][j]++;
                    int c = color[t];
                    if (!~tp[c]) tp[c] = type;
                    else if (tp[c] != type) flag = false;
                }
                ok[i][j] = flag;
            }
        if (ct[0][n - 1] != m) return 0;
        memset(f, -1, sizeof(f)), memset(g, -1, sizeof(g));
        return F(0, n - 1);
    }
};

