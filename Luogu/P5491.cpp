#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int mod, w;

struct WEN {

int a, b;

WEN (int a = 0, int b = 0): a(a), b(b) {}

WEN operator * (WEN B) {
    return (WEN){ ((LL)a * B.a + (LL)b * B.b % mod * w) % mod, ((LL)b * B.a + (LL)a * B.b) % mod };
}

};

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res; 
}

inline WEN Pow(WEN x, int y) {
    WEN res(1, 0);
    for (; y; y >>= 1, x = x * x) if (y & 1) res = res * x;
    return res;
}

inline int rnd() { 
    return rand();
    // return rand() << 16 | rand();
}

inline int Cipolla(int x) {
    x %= mod;
    if (Pow(x, (mod - 1) / 2) != 1) return -1;
    int a = 1; w = (LL)a * a % mod - x; if (w < 0) w += mod;
    while (Pow(w, (mod - 1) / 2) != mod - 1) {
        a = rnd() % mod, w = (LL)a * a % mod - x; 
        if (w < 0) w += mod;
    }
    return Pow((WEN){ a, 1 }, (mod + 1) / 2).a;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n; scanf("%d%d", &n, &mod);
        if (!n) { puts("0"); continue; }
        int A = Cipolla(n), B = mod - A;
        if (A > B) swap(A, B);
        if (~A) printf("%d %d\n", A, B);
        else puts("Hola!");
    }
}