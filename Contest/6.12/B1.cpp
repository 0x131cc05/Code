#include "module.h"

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> P;
typedef __int128 WEN;

const int m1 = 1e9 + 7;
const int m2 = 1e9 + 9;
const int up = 1e9;
const int WenYeShenXian = 233;

LL c, mod;

inline LL Pow(LL x, LL y) {
    LL res = 1;
    for (; y; y >>= 1, x = (WEN)x * x % mod) if (y & 1) res = (WEN)res * x % mod;
    return res;
}

inline bool dirct(int p, int q) { // 1 -> right
    return (WEN)c * q >= (WEN)p * mod;
}

P Solve() {
    int a = Query(m1), b = Query(m2);
    mod = (LL)m1 * m2, c = ((WEN)a * Pow(m2, m1 - 1) + (WEN)b * Pow(m1, m2 - 1)) % mod;
    int pl = 0, ql = 1, pr = 1, qr = 1;
    while (WenYeShenXian) {
        LL fuck = (WEN)ql * c % mod;
        if (fuck <= 1e9) return P(fuck, ql);
        int p = pl + pr, q = ql + qr, dir = dirct(p, q);
        int l = 0, r = dir ? min(!pr ? up : (up - p) / pr, (up - q) / qr) : min(!pl ? up : (up - p) / pl, (up - q) / ql);
        while (l <= r) {
            int mid = (l + r) >> 1;
            int tp = p + (dir ? pr * mid : pl * mid), tq = q + (dir ? qr * mid : ql * mid);
            if (dirct(tp, tq) == dir) {
                if (dir) pl = tp, ql = tq;
                else pr = tp, qr = tq;
                l = mid + 1;
            } else r = mid - 1;
        }
    }
}
