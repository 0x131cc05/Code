#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

unordered_map<bitset<N>, int> mp;

bitset<N> wkr[35];

int main() {
    int n, s, q; scanf("%d%d%d", &n, &s, &q);
    for (int i = 1; i <= s; i++) {
        int k; scanf("%d", &k);
        for (int j = 1, a; j <= k; j++) scanf("%d", &a), wkr[i][a] = 1;
    }
    int lim = s / 3, r = s - lim;
    for (int s = 0; s < 1 << r; s++) {
        bitset<N> tmp;
        for (int j = 1; j <= r; j++) if (s & (1 << j - 1)) 
            tmp ^= wkr[j + lim];
        if (!mp.count(tmp)) mp[tmp] = __builtin_popcount(s);
        else mp[tmp] = min(mp[tmp], __builtin_popcount(s));
    }
    while (q--) {
        bitset<N> nw;
        int k; scanf("%d", &k);
        for (int i = 1, a; i <= k; i++) scanf("%d", &a), nw[a] = 1;
        int res = 1e9;
        for (int s = 0; s < 1 << lim; s++) {
            bitset<N> tmp = nw;
            for (int j = 1; j <= lim; j++) if (s & (1 << j - 1)) tmp ^= wkr[j];
            if (mp.count(tmp)) res = min(res, mp[tmp] + __builtin_popcount(s));
        }
        if (res < 1e8) printf("%d\n", res);
        else puts("-1");
    }
}