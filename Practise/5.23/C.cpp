#include <bits/stdc++.h>
using namespace std;

const int N = 51;

typedef long long LL;


LL G[N][N]; int ct[N][N], n;

void clr() {
    memset(G, 0x3f, sizeof(G)), memset(ct, 0, sizeof(ct));
    for (int i = 1; i <= n; i++) G[i][i] = 0;
}

void adde(int from, int to, LL w, int d) {
    if (G[from][to] > w) 
        G[from][to] = w, ct[from][to] = d;
}

int Floyd(LL d) {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                LL tmp = G[i][k] + G[k][j];
                if (tmp < G[i][j]) {
                    G[i][j] = tmp, ct[i][j] = ct[i][k] + ct[k][j];
                } 
            }
    int type = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) if (G[i][j] + G[j][i] < 0) {
            int all = ct[i][j] + ct[j][i], tp = all < 0 ? 1 : -1;
            if (!all || (type && type != tp)) 
                puts("0"), exit(0);
            type = tp;
        }
    return type;
}

struct command { int l, r, w; };
vector<command> A, B;

void build(LL d) {
    clr();
    for (int i = 1; i < n; i++) adde(i + 1, i, -1, 0);
    for (auto t : A) {
        if (t.l < t.r) adde(t.r, t.l, -t.w, 0);
        else adde(t.r, t.l, d - t.w, 1);
    }
    for (auto t : B) {
        if (t.l < t.r) adde(t.l, t.r, t.w, 0);
        else adde(t.l, t.r, t.w - d, -1);
    }
}

int main() {
    // freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
    int m1, m2; scanf("%d%d%d", &n, &m1, &m2);
    for (int i = 1; i <= m1; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c), a++, b++;
        A.push_back({ a, b, c });
    }
    A.push_back({ n, 1, 1 });
    for (int i = 1; i <= m2; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c), a++, b++;
        B.push_back({ a, b, c });
    }
    LL l = n, r = 1e12, mid, L = -1, R = -1;
    while (l <= r) {
        mid = (l + r) >> 1, build(mid);
        if (Floyd(mid) >= 0) L = mid, r = mid - 1;
        else l = mid + 1; 
    }
    l = n, r = 1e12;
    while (l <= r) {
        mid = (l + r) >> 1; build(mid);
        if (Floyd(mid) <= 0) R = mid, l = mid + 1;
        else r = mid - 1;
    }
    build(L); 
    if (Floyd(L) != 0) puts("0");
    else {
        if (R > 1e11) puts("-1");
        else printf("%lld\n", max(0ll, R - L + 1));
    }
}