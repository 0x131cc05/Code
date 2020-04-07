
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int W, mod; 
struct comp {
    int x, y;
    comp(int x, int y = 0): x(x), y(y) {}
    comp operator * (const comp &b) {
        return comp(((LL)x * b.x % mod + (LL)y * b.y % mod * W) % mod, ((LL)x * b.y + (LL)y * b.x) % mod);
    }
};
inline comp Pow(comp x, int y) {
    comp res(1);
    for (;y;y >>= 1, x = x * x) if (y & 1) res = res * x;
    return res;
}
inline int Pow(int x, int y, int p = mod) {
    int res = 1;
    for (;y;y >>= 1, x = (LL)x * x % p) if (y & 1) res = (LL)res * x % p;
    return res;
}
inline int Rand() {
    return (rand() << 16) | rand();
}
inline int Cipolla(int n) {
    n = (n % mod + mod) % mod;
    if (n == 0) return 0;
    if (Pow(n, (mod - 1) / 2) + 1 == mod) return -1;
    int a;
    while (233) {
        a = Rand() % mod, W = (((LL)a * a - n) % mod + mod) % mod;
        if (Pow(W, (mod - 1) / 2) + 1 == mod) break;
    }
    return (Pow(comp(a, 1), (mod + 1) / 2).x + mod) % mod;
}
map<int, int> s; set<int> sol;
inline void BSGS(int A, int B) {
    cout << A << ' ' << B << endl;
    sol.clear();
    if (B == 1) sol.insert(0);
    s.clear();
    int m = ceil(sqrt(mod)), ls = 1;
    for (int i = 0;i < m;i++, ls = (LL)ls * A % mod) 
        s[(LL)B * ls % mod] = i;
    for (int i = m, t = ls;i <= mod;i += m, t = (LL)t * ls % mod)
        if (s.count(t) && (i - s[t]) < (mod - 1)) sol.insert(i - s[t]);
}
#define P pair<int, int>
inline LL calc(LL n, LL p, LL m) {
    return n / p + (m && m <= n % p);
}
inline LL calc(LL n, LL p, LL m, int d) {
    LL p1 = 4 * p, t = d * p % p1 * p + m * Pow(4, p - 1, p1); 
    return calc(n, p1, t % p1);
}
inline LL calc(LL L, LL R, LL p, LL m, int d) {
    return calc(R, p, m, d) - calc(L - 1, p, m, d);
}
inline int BF1(int A, int x, int p, LL L, LL R) {
    int res = 0, a = 1, b = 0;
    if (x == 1 && L == 1) res++;
    for (int i = 2;i <= R;i++) {
        int t = b; b = a, a = ((LL)A * a + t) % p;
        if (L <= i && a == x) res++;
    }
    return res;
}
#define P pair<int, int>
map<P, int> ss; int flag[2000010];
inline LL calc2(int pos, LL len, int l, int c) {
    LL res = len / l * c; len %= l;
    return res + flag[pos + len - 1] - flag[pos - 1];
}
inline LL BF2(int A, int x, int p, LL L, LL R) {
    int a = 1, b = 0, i; ss.clear();
    for (i = 1;!ss.count(P(a, b));i++) {
        ss[P(a, b)] = i;
        flag[i] = flag[i - 1] + (a == x);
        int t = b; b = a, a = ((LL)A * a + t) % p;
    }
    int ls = ss[P(a, b)]; LL res = 0;
    if (R < ls) return flag[R] - flag[L - 1];
    if (L < ls) res = flag[ls] - flag[L - 1];
    L = max(L, (LL)ls); int c = flag[i - 1] - flag[ls - 1];
    return res + calc2(ls, R - ls + 1, i - ls, c) - calc2(ls, L - ls, i - ls, c);
}
#define SIT set<int>::iterator 
inline LL solve(int A, int x, int p, LL L, LL R) {
//    if (R <= 100000) return BF1(A, x, p, L, R);
//    if (p <= 1000000) return BF2(A, x, p, L, R);
    mod = p; int T = Cipolla((LL)A * A % mod + 4), inv2 = (p + 1) / 2;
    if (T == 0) {
        int i = (LL)A * inv2 % mod;
        LL res = 0;
        for (int j = 0, b = 1;j < 4;j++, b = (LL)b * i % mod) 
            res += calc(L, R, p, (LL)x * Pow(b, mod - 2) % mod, (j + 1) % 4);
        return res;
    } 
    if (T == -1) return 0;
    int y = (LL)(T + A) * inv2 % mod; x = (LL)x * T % mod;
    cout << T << ' ' << y << ' ' << x << endl;
    LL ans = 0;
    {
        int res = Cipolla((LL)x * x % mod - 4);
        if (res != -1) {
            int t1 = (LL)(x + res) * inv2 % mod, t2 = (LL)(x + mod - res) * inv2 % mod;
            BSGS(y, t1); 
            for (auto v : sol) if (v % 2 == 1) ans += calc(R, p - 1, v) - calc(L - 1, p - 1, v);
            if (t1 != t2) {
                BSGS(y, t2);
                for (auto v : sol) if (v % 2 == 1) ans += calc(R, p - 1, v) - calc(L - 1, p - 1, v);
            } 
        }
    }
    {
        int res = Cipolla((LL)x * x % mod + 4);
        if (res != -1) {
            int t1 = (LL)(x + res) * inv2 % mod, t2 = (LL)(x + mod - res) * inv2 % mod;
            BSGS(y, t1);
            for (auto v : sol) if (v % 2 == 0) ans += calc(R, p - 1, v) - calc(L - 1, p - 1, v);
            if (t1 != t2) {
                BSGS(y, t2);
                for (auto v : sol) if (v % 2 == 0) ans += calc(R, p - 1, v) - calc(L - 1, p - 1, v);
            } 
        } 
    }
    return ans;
}
int main() {
//    freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
    srand((long long)new char); int T; scanf("%d", &T);
    while (T--) {
        int A, p, x; LL L, R; scanf("%d%d%d%lld%lld", &A, &p, &x, &L, &R);
        printf("%lld\n", solve(A, x, p, L, R));
    }
}
