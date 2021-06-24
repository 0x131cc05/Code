#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define per(i, r, l) for(int i = (r); i >= (l); i--)
#define mem(a, b) memset(a, b, sizeof a)
#define For(i, l, r) for(int i = (l), i##e = (r); i < i##e; i++)
#define pb push_back
#define upd(a, b) (a = max(a, b))

using namespace std;
using ll = long long;

const int N = 55;

int n, q, a[N], f[N][N];

int main() {
    freopen("sequence.in", "r", stdin);
#ifndef local
    freopen("sequence.out", "w", stdout);
#endif
    cin >> n >> q;
    rep(i, 1, n) scanf("%d", &a[i]);
    int l, r, K;
    if(n <= 50) while(q--) {
        scanf("%d%d%d", &l, &r, &K);
        mem(f, 192);
        rep(i, l - 1, r) f[0][i] = 0;
        rep(k, 1, K) rep(i, l, r) {
            f[k][i] = f[k][i - 1];
            int su = 0;
            per(j, i, l) su += a[j], upd(f[k][i], f[k - 1][j - 1] + su);
        }
        printf("%d\n", f[K][r]);
    } else {
        rep(i, 1, n) a[i] += a[i - 1];
        while(q--) {
            scanf("%d%d%d", &l, &r, &K);
            printf("%d\n", a[r] - a[l - 1]);
        }
    }
    return 0;
}