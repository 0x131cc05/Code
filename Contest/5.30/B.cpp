#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
const int mod = 1e9 + 7;

typedef long long LL;
typedef pair<int, int> P;

#define x first
#define y second

int A[N], C[N], ct[N], ct1[N], id[N], ans[N], n;

P p[N];

inline P sub(int a, int b) {
    return P(p[a].x - p[b].x, p[a].y - p[b].y);
}

inline bool check(int a, int b, int c) {
    P t1 = sub(b, a), t2 = sub(c, a);
    if ((LL)t1.x * t2.y - (LL)t1.y * t2.x != 0) return false;
    return abs(p[c].x - p[a].x) + abs(p[b].x - p[c].x) == abs(p[b].x - p[a].x) && abs(p[c].y - p[a].y) + abs(p[b].y - p[c].y) == abs(p[b].y - p[a].y);
}

double fuck[N];

inline void process(int t) {
    int tot = 0;
    for (int i = 1; i <= n; i++) if (i != t) id[++tot] = i;
    for (int i = 1; i <= n; i++) if (i != t) 
        fuck[i] = atan2(p[i].y - p[t].y, p[i].x - p[t].x);
    sort(id + 1, id + tot + 1, [&](int a, int b) {
        double A = fuck[a], B = fuck[b];
        if (fabs(A - B) > 1e-6) return A > B;
        P t1 = sub(a, t), t2 = sub(b, t);
        return abs(t1.x) > abs(t2.x) || abs(t1.y) > abs(t2.y);
    });
    for (int i = 1, pos = 1, nw = 0, t1 = 0; i <= tot; i++, nw--) {
        if (pos == i - 1 && nw < 0) pos = i, nw = t1 = 0;
        P delta = sub(id[i], t);
        if (i == 1 || !check(t, id[i - 1], id[i])) t1 = 0;
        else t1++;
        delta = P(-delta.x, -delta.y);
        while (233) {
            int nxt = pos == tot ? 1 : pos + 1;
            P tmp = sub(id[nxt], t);
            LL cross = (LL)tmp.x * delta.y - (LL)tmp.y * delta.x;
            if (cross > 0 || nxt == i) break;
            if (cross == 0 && !check(t, id[i], id[nxt])) break;
            pos = nxt, nw++;
        }
        ct[nw + 2]++, ct1[t1 + 2]++;
    }
}

int frac[N], inv[N];

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline int C1(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int main() {
    scanf("%d", &n); int a, b, c; scanf("%d%d%d", &a, &b, &c);
    A[0] = C[0] = frac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) 
        A[i] = (LL)A[i - 1] * a % mod, C[i] = (LL)C[i - 1] * c % mod;
    for (int i = 1; i <= n; i++) 
        frac[i] = (LL)frac[i - 1] * i % mod, inv[i] = Pow(frac[i], mod - 2);
    for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y);
    for (int i = 1; i <= n; i++) 
        process(i);
    for (int i = 3; i <= n; i++)
        for (int j = 3; j <= i; j++) {
            int w = C1(i - 2, j - 2);
            ans[j] = (ans[j] + (LL)w * (ct[i] - ct1[i])) % mod;
        }
    int res = 0;
    for (int i = 3; i <= n; i++)
        res = (res + (LL)A[i] * ans[i] % mod * C[n - i]) % mod;
    res = (res + mod) % mod;
    printf("%d\n", res);
}
