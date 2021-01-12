#include <bits/stdc++.h>
using namespace std;

typedef unsigned int LL;

int n, q, p;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

inline LL C(int n, int r) {
    vector<int> tmp;
    for (int i = 1; i <= r; i++) tmp.push_back(n - i + 1);
    for (int i = 1; i <= r; i++) {
        int zjk = i;
        for (auto &t : tmp) if (t != 1) {
            int g = gcd(zjk, t);
            zjk /= g, t /= g;
        }
    }
    LL res = 1;
    for (auto t : tmp) res *= t;
    return res;
}

inline LL Pow(LL x, int y) {
    LL res = 1;
    for (; y; y >>= 1, x *= x) if (y & 1) res *= x;
    return res;
}

LL t[150];

int main() {
    scanf("%d%d%d", &n, &p, &q), p = min(p, n - 1);
    for (int i = 0; i <= p; i++) t[i] = C(n, i);
    LL res = 0;
    for (int i = 1; i <= q; i++) {
        LL tmp = 0;
        for (int j = 0; j <= p; j++) 
            tmp += t[j] * Pow(i, j);
        res ^= tmp * i;
    }
    printf("%u\n", res);
    return 0;
}