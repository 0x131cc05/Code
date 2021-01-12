#include <bits/stdc++.h>
using namespace std;

const int M = 2520;
const int N = 510;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int x[N], r[N], g[N], period[N], n, vis[N], cover[110][110];
double p[N];

void solve(int a) {
    memset(vis, 0, sizeof(vis)), memset(cover, 0, sizeof(cover));
    double cur = 1;
    for (int i = 1; i <= n; i++) {
        vector<int> pass; int len = period[i];
        for (int j = 0; j < len; j++) {
            int t = (a + j * M + x[i]) % (r[i] + g[i]);
            if (t >= r[i]) pass.push_back(j); 
        }
        if (len != 1) {
            while (len * period[i] <= 100) len *= period[i];
            for (int t = 0; t < pass.size(); t++) 
                if (pass[t] + period[i] < len) pass.push_back(pass[t] + period[i]);
        }
        if (!vis[len]) {
            vis[len] = 1, cur *= (double)pass.size() / len;
            for (auto t : pass) cover[len][t] = 1;
        } else {
            static int tmp[110]; memset(tmp, 0, sizeof(tmp)); int tot = 0;
            for (int i = 0; i < len; i++) if (cover[len][i]) 
                tot++, tmp[i] = 1, cover[len][i] = 0;
            int lst = tot;
            cur /= tot, tot = 0;
            for (auto t : pass) if (tmp[t]) 
                cover[len][t] = 1, tot++;
            cur *= tot, assert(lst >= tot);
        }
        if (cur < 1e-8) return;
        p[i] += cur / M;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d%d", &x[i], &r[i], &g[i]), period[i] = (r[i] + g[i]) / gcd(r[i] + g[i], M);
    for (int i = 0; i < M; i++) solve(i);
    p[0] = 1;
    for (int i = n; i >= 1; i--) p[i] = p[i - 1] - p[i];
    double sum = 1;
    for (int i = 1; i <= n; i++) printf("%.10lf\n", p[i]), sum -= p[i];
    printf("%.10lf\n", sum);
}