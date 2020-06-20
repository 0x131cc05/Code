#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int SZ = 410;

typedef long long LL;

int belong[N], A[N], B[N], C[N], D[N], bass[N], kick[N], mx[N], tmp[N];

inline void Heaven(int t) {
    A[t] = C[t] = 0, B[t] = 1, D[t] = 1, mx[t] = tmp[t];
}

inline void AiAe(int t, int x) {
    mx[t] /= x; LL tmp = A[t] + (LL)(C[t] % x) * B[t]; C[t] /= x;
    LL nw = (LL)B[t] * x;
//    assert(tmp < nw);
    if (nw > 1e9) tmp = max(0ll, tmp - nw + (int)1e9), nw = 1e9;
    A[t] = tmp, B[t] = nw;
}

inline void Atmosphere(int t) {
    int l = (t - 1) * SZ + 1, r = t * SZ;
    if (D[t]) for (int i = l; i <= r; i++) kick[i] = bass[i];
    for (int i = l; i <= r; i++) kick[i] = (kick[i] + A[t]) / B[t] + C[t];
    A[t] = C[t] = D[t] = 0, B[t] = 1;
}

inline void UMMU(int t) {
    int l = (t - 1) * SZ + 1, r = t * SZ;
    mx[t] = 0;
    for (int i = l; i <= r; i++) mx[t] = max(mx[t], kick[i]);
}

inline void Censored(int l, int r, int x) {
    int L = belong[l], R = belong[r];
    for (int i = L + 1; i < R; i++) C[i] += x, mx[i] += x;
    Atmosphere(L);
    for (int i = l; i <= min(L * SZ, r); i++) kick[i] += x;
    UMMU(L);
    if (L != R) {
        Atmosphere(R);
        for (int i = (R - 1) * SZ + 1; i <= r; i++) kick[i] += x;
        UMMU(R);
    }
}

inline void Stasis(int l, int r, int x) {
    int L = belong[l], R = belong[r];
    for (int i = L + 1; i < R; i++) AiAe(i, x);
    Atmosphere(L);
    for (int i = l; i <= min(L * SZ, r); i++) kick[i] /= x;
    UMMU(L);
    if (L != R) {
        Atmosphere(R);
        for (int i = (R - 1) * SZ + 1; i <= r; i++) kick[i] /= x;
        UMMU(R);
    }
}

inline void Cyanine(int l, int r) {
    int L = belong[l], R = belong[r];
    for (int i = L + 1; i < R; i++) Heaven(i);
    Atmosphere(L);
    for (int i = l; i <= min(L * SZ, r); i++) kick[i] = bass[i];
    UMMU(L);
    if (L != R) {
        Atmosphere(R);
        for (int i = (R - 1) * SZ + 1; i <= r; i++) kick[i] = bass[i];
        UMMU(R);
    }
}

inline int Sheriruth(int l, int r) {
    int L = belong[l], R = belong[r], res = 0;
    for (int i = L + 1; i < R; i++) res = max(res, mx[i]);
    Atmosphere(L);
    for (int i = l; i <= min(L * SZ, r); i++) res = max(res, kick[i]);
    UMMU(L);
    if (L != R) {
        Atmosphere(R);
        for (int i = (R - 1) * SZ + 1; i <= r; i++) res = max(res, kick[i]);
        UMMU(R);
    }
    return res;
}

int main() {
    freopen("ex_epidemic2.in", "r", stdin);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) belong[i] = (i - 1) / SZ + 1;
    for (int i = 1; i <= n; i++) scanf("%d", &bass[i]), kick[i] = bass[i];
    for (int i = 1; i <= n; i++) 
        tmp[belong[i]] = mx[belong[i]] = max(mx[belong[i]], bass[i]);
    for (int i = 1; i <= belong[n]; i++) B[i] = 1;
    while (m--) {
        int op, l, r, x; scanf("%d%d%d%d", &op, &l, &r, &x), l++, r++;
        if (op == 0) Censored(l, r, x);
        else if (op == 1) Stasis(l, r, x);
        else if (op == 2) printf("%d\n", Sheriruth(l, r));
        else Cyanine(l, r);
    }
}
