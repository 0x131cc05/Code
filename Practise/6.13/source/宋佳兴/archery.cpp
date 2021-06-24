#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define per(i, r, l) for(int i = (r); i >= (l); i--)
#define mem(a, b) memset(a, b, sizeof a)
#define For(i, l, r) for(int i = (l), i##e = (r); i < i##e; i++)
#define pb push_back

using namespace std;

const int N = 505;

int n, r, a[N * 2], x[N], y[N];
int main() {
    freopen("archery.in", "r", stdin);
#ifndef local
    freopen("archery.out", "w", stdout);
#endif
    cin >> n >> r, r %= n;
    For(i, 0, n * 2) scanf("%d", &a[i]);
    int mi = 1e9, as;
    For(k, 0, n) {
        For(i, 0, n) x[i] = i * 2, y[i] = i * 2 + 1;
        rep(j, 1, n * 2) {
            if(a[x[0]] > a[y[0]]) swap(x[0], y[0]);
            For(i, 1, n) if(a[x[i]] < a[y[i]]) swap(x[i], y[i]);
            rotate(y, y + 1, y + n);
        }
        rotate(y, y + r, y + n);
        int pos;
        For(i, 0, n) if(x[i] == k * 2 || y[i] == k * 2) pos = i;
        if(pos <= mi) mi = pos, as = k + 1;
        rep(i, 0, 1) swap(a[k * 2 + i], a[k * 2 + i + 1]);
    }
    cout << as;
    return 0;
}
