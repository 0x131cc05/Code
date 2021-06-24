#include <bits/stdc++.h>
using namespace std;

// int sg[110][110];

// int SG(int n, int m) {
//     if (n > m) swap(n, m);
//     if (sg[n][m] != -1) return sg[n][m];
//     vector<int> hh;
//     for (int i = 1; i * i <= n; i++) if (n % i == 0) {
//         if (i != 1) hh.push_back(i & 1 ? SG(n / i, m) : 0);
//         if (n / i != i) hh.push_back((n / i) & 1 ? SG(i, m) : 0);
//     }
//     for (int i = 1; i * i <= m; i++) if (m % i == 0) {
//         if (i != 1) hh.push_back(i & 1 ? SG(n, m / i) : 0);
//         if (m / i != i) hh.push_back((m / i) & 1 ? SG(n, i) : 0);
//     }
//     sort(hh.begin(), hh.end());
//     hh.resize(unique(hh.begin(), hh.end()) - hh.begin()); 
//     int res = hh.size();
//     for (int i = 0; i < hh.size(); i++) if (hh[i] != i) return sg[n][m] = i;
//     return sg[n][m] = res;
// }

const int N = 100010;

int pre[N], wkr[N];

inline int SG(int n, int m) {
    if (n % 2 == 1 && m % 2 == 1) return wkr[n] ^ wkr[m];
    return (wkr[n] ^ wkr[m]) + 1;
}

int main() {
    // memset(sg, -1, sizeof(sg));
    for (int i = 2; i <= N - 10; i++) {
        int tp = i;
        while (tp % 2 == 0) tp /= 2;
        for (int j = 2; j * j <= tp; j++) 
            while (tp % j == 0) tp /= j, wkr[i]++;
        if (tp > 1) wkr[i]++;
    }
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int w, h; scanf("%*d%*d%d%d", &w, &h);
        pre[i] = pre[i - 1] ^ SG(w, h);
    }
    int q; scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        puts((pre[r] ^ pre[l - 1]) ? "Yes" : "No");
    }
}

