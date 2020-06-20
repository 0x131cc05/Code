#include "module.h"

#include <iostream>

using namespace std;

typedef pair<int, int> P;
typedef long long LL;

const int m1 = 1e9 + 7;
const int m2 = 1e9 + 9;

inline LL Add(LL x, LL y, LL mod) {
    LL t = x + y;
    return t >= mod ? t - mod : t;
}

inline LL Mul(LL x, LL y, LL mod) {
    LL res = 0;
    for (; y; y >>= 1, x = Add(x, x, mod)) if (y & 1) res = Add(res, x, mod);
    return res;
}

inline LL Pow(LL x, LL y, LL mod) {
    LL res = 1;
    for (; y; y >>= 1, x = Mul(x, x, mod)) if (y & 1) res = Mul(res, x, mod);
    return res;
}

P Solve() {
    int a = Query(m1), b = Query(m2);
    LL mod = (LL)m1 * m2;
    LL v = Add(Mul(a, Pow(m2, m1 - 1, mod), mod), Mul(b, Pow(m1, m2 - 1, mod), mod), mod);
    cout << v << endl;
    LL x = 0;
    for (int y = 1; ; y++) {
        x = Add(x, v, mod);
        if (x <= 1e9) return P(x, y);
    }
}
