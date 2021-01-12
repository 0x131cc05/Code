#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 300010;

int A[N], B[N], id1[N], id2[N], rk1[N], rk2[N]; LL res1, res2;

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]), id1[i] = i;
    for (int i = 1; i <= n; i++) scanf("%d", &B[i]), id2[i] = i;
    sort(id1 + 1, id1 + n + 1, [](int a, int b) {
        return A[a] < A[b];
    });
    sort(id2 + 1, id2 + n + 1, [](int a, int b) {
        return B[a] < B[b];
    });
    for (int i = 1; i <= n; i++) res1 += (LL)A[id1[i]] * B[id2[i]], res2 += (LL)A[id1[i]] * B[id2[n - i + 1]];
    for (int i = 1; i <= n; i++) rk1[id1[i]] = i, rk2[id2[i]] = i;
    printf("%lld %lld\n", res2, res1);
    while (m--) {
        int a, b, c, at; scanf("%d%d%d", &a, &b, &c);
        if (a == 1) {
            int pos = rk1[b];
//            cout << pos << endl;
            if (c == 1) {
                int l = pos, r = n;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (A[id1[mid]] == A[b]) at = mid, l = mid + 1;
                    else r = mid - 1;
                }
            } else {
                int l = 1, r = pos;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (A[id1[mid]] == A[b]) at = mid, r = mid - 1;
                    else l = mid + 1;
                }
            }
//            cout << at << endl;
            res1 -= (LL)A[id1[pos]] * B[id2[pos]], res2 -= (LL)A[id1[pos]] * B[id2[n - pos + 1]];
            if (pos != at) res1 -= (LL)A[id1[at]] * B[id2[at]], res2 -= (LL)A[id1[at]] * B[id2[n - at + 1]];
            rk1[id1[pos]] = at, rk1[id1[at]] = pos, swap(id1[pos], id1[at]), A[b] += c;
            res1 += (LL)A[id1[pos]] * B[id2[pos]], res2 += (LL)A[id1[pos]] * B[id2[n - pos + 1]];
            if (pos != at) res1 += (LL)A[id1[at]] * B[id2[at]], res2 += (LL)A[id1[at]] * B[id2[n - at + 1]];
        } else {
            int pos = rk2[b];
            if (c == 1) {
                int l = pos, r = n;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (B[id2[mid]] == B[b]) at = mid, l = mid + 1;
                    else r = mid - 1;
                }
            } else {
                int l = 1, r = pos;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (B[id2[mid]] == B[b]) at = mid, r = mid - 1;
                    else l = mid + 1;
                }
            }
            res1 -= (LL)A[id1[pos]] * B[id2[pos]], res2 -= (LL)A[id1[n - pos + 1]] * B[id2[pos]];
            if (pos != at) res1 -= (LL)A[id1[at]] * B[id2[at]], res2 -= (LL)A[id1[n - at + 1]] * B[id2[at]];
            rk2[id2[pos]] = at, rk2[id2[at]] = pos, swap(id2[pos], id2[at]), B[b] += c;
            res1 += (LL)A[id1[pos]] * B[id2[pos]], res2 += (LL)A[id1[n - pos + 1]] * B[id2[pos]];
            if (pos != at) res1 += (LL)A[id1[at]] * B[id2[at]], res2 += (LL)A[id1[n - at + 1]] * B[id2[at]];
        }
        printf("%lld %lld\n", res2, res1);
//        for (int i = 1; i <= n; i++) cout << id1[i] << ' ';
//        cout << endl;
    }
}
