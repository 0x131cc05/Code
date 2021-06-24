#include <bits/stdc++.h>
using namespace std;

const int N = 150010;

typedef long long LL;

struct WEN {

int p, t; LL l, r;

bool operator < (const WEN &b) {
    return (LL)p * b.t > (LL)b.p * t;
}

} wkr[N];

int n; LL tot;

inline bool check(double mid) {
    double mx = 0, nw = 0;
    for (int i = 1; i <= n; i++) {
        if (wkr[i].p != wkr[i - 1].p) mx = nw;
        if (wkr[i].p * (1 - mid * wkr[i].r / tot) < mx) return false;
        nw = max(nw, wkr[i].p * (1 - mid * wkr[i].l / tot));
    }
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &wkr[i].p);
    for (int i = 1; i <= n; i++) scanf("%d", &wkr[i].t), tot += wkr[i].t;
    sort(wkr + 1, wkr + n + 1); LL s = 0;
    for (int i = 1; i <= n; i++) {
        int j = i; LL sum = wkr[i].t;
        while (j < n && (LL)wkr[i].p * wkr[j + 1].t == (LL)wkr[j + 1].p * wkr[i].t) j++, sum += wkr[j].t;
        for (int k = i; k <= j; k++) 
            wkr[k].l = s + wkr[k].t, wkr[k].r = s + sum;
        s += sum, i = j;
    }
    sort(wkr + 1, wkr + n + 1, [](WEN a, WEN b) {
        return a.p < b.p;
    });
    double l = 0, r = 1;
    for (int i = 1; i <= 50; i++) {
        double mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    printf("%.7lf\n", l);
    return 0;
}