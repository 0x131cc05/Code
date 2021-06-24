#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int P = 131;
const int mod = 1e9 + 7;

typedef long long LL;

int hsh[N], hsh1[N], s[N], pw[N], t[N], n, m; double wkr[N][11];

double p[19][N];

inline void pre() {
    for (int i = 1; i <= n; i++) {
        double mx = 0;
        for (int j = 1; j <= 10; j++) 
            if (wkr[i][j] > mx) mx = wkr[i][j], s[i] = j;
        p[0][i] = mx;
    }
    for (int i = 1; i <= 17; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            p[i][j] = p[i - 1][j] * p[i - 1][j + (1 << i - 1)];
    for (int i = 1; i <= n; i++) 
        hsh[i] = ((LL)hsh[i - 1] * P + s[i]) % mod;
    for (int i = 1; i <= m; i++)
        hsh1[i] = ((LL)hsh1[i - 1] * P + t[i]) % mod;
    pw[0] = 1;
    for (int i = 1; i <= n; i++) 
        pw[i] = (LL)pw[i - 1] * P % mod;
} 

inline int get(int l, int r) {
    return (hsh[r] - (LL)hsh[l - 1] * pw[r - l + 1] % mod + mod) % mod;
}

inline int get1(int l, int r) {
    return (hsh1[r] - (LL)hsh1[l - 1] * pw[r - l + 1] % mod + mod) % mod;
}

inline double calc(int l, int r) {
    double res = 1;
    for (int i = 17; i >= 0; i--) if (l + (1 << i) - 1 <= r) 
        res *= p[i][l], l += 1 << i;
    return res;
}

inline int lcp(int a, int b) {
    int l = 1, r = min(n - a + 1, m - b + 1), ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (get(a, a + mid - 1) == get1(b, b + mid - 1)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}

inline double solve(int pos) {
    int cur = 1; double ans = 1;
    while (cur <= m) {
        if (ans < 1e-9) return ans;
        int hh = lcp(pos, cur); ans *= calc(pos, pos + hh - 1);
        if (cur + hh > m || pos + hh > n) break;
        ans *= wkr[pos + hh][t[cur + hh]];
        pos += hh + 1, cur += hh + 1;
    }
    return ans;
}

char fuck[N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= 10; j++) {
            int a; scanf("%d", &a); wkr[i][j] = a / 1e9;
        }
    scanf("%s", fuck + 1);
    for (int i = 1; i <= m; i++) t[i] = fuck[i] - '0' + 1;
    pre();
    for (int i = 1; i <= n - m + 1; i++) printf("%.10lf\n", solve(i));
}
