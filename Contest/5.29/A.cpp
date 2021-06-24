#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

int flag[N], prime[N], tot, id[N];

inline void sieve() {
    for (int i = 2; i <= 1000; i++) {
        if (!flag[i]) id[i] = ++tot, prime[tot] = i;
        for (int j = 1; j <= tot && i * prime[j] <= 1000; j++) {
            flag[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

const int SZ = (N >> 6) + 1;

typedef unsigned long long LL;

struct WEN {

LL val[SZ + 1];

void operator ^= (const WEN &b) {
    for (int i = 0; i <= SZ; i++) val[i] ^= b.val[i];
}

int operator [] (int x) {
    int base = x >> 6, t = x & 63;
    return val[base] >> t & 1;
}

int count() {
    int res = 0;
    for (int i = 0; i <= SZ; i++) res += __builtin_popcountll(val[i]);
    return res;
}

void flip(int x) {
    int base = x >> 6, t = x & 63;
    val[base] ^= 1ull << t;
}

} mask[170], num;

int ans;

int main() {
    int n, q; scanf("%d%d", &n, &q); sieve();
    for (int i = 1; i <= tot; i++) {
        int t = prime[i];
        for (int j = t; j <= n; j += t) {
            int ct = 0, tmp = j;
            while (tmp % t == 0) tmp /= t, ct ^= 1;
            if (ct) mask[i].flip(j); 
        }
    }
    while (q--) {
        int p; scanf("%d", &p);
        if (p > 1000) {
            for (int i = p; i <= n; i += p) {
                int ct = 0, tmp = i;
                while (tmp % p == 0) tmp /= p, ct ^= 1;
                if (ct) ans -= num[i], num.flip(i), ans += num[i];
            } 
        } else num ^= mask[id[p]], ans = num.count();
        printf("%d\n", ans);
    }
}
