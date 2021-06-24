#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> P;

#define int long long

int mod;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

const int SZ = 42899;

struct HashMap {

vector<P> buff[SZ]; vector<int> pos;

inline void insert(int x, int y) {
    int t = x % SZ;
    buff[t].push_back(P(x, y)), pos.push_back(t);
}

inline int query(int x) {
    int t = x % SZ;
    for (auto v : buff[t]) if (v.first == x) return v.second;
    return -1;
}

inline void clear() {
    for (auto t : pos) buff[t].clear();
    pos.clear();
}
    
} s;

vector<int> sol;

inline int BSGS(int A, int B, bool flag = 1) { 
    if (B == -1) return -1;
    if (flag && B % mod == 1) return 0; s.clear();
    int m = ceil(sqrt(mod)), ls = 1;
    for (int i = 0; i < m; i++, ls = (LL)ls * A % mod)
        s.insert((LL)B * ls % mod, i);
    for (int i = m, t = ls; i <= mod; i += m, t = (LL)t * ls % mod) {
        int res = s.query(t);
        if (res != -1) return i - res;
    }
        
    return -1;
}

int fuck;

inline void BSGS1(int A, int B) {
    int a = BSGS(A, B);
    if (a == -1) return;
    sol.push_back(a);
    if (fuck != -1 && fuck % 2 == 1) sol.push_back(a + fuck);
}

inline int Cipolla(int x) {
    if (Pow(x, (mod - 1) / 2) != 1) return -1;
    int a = rand() % mod;
    while (Pow(((LL)a * a - x + mod) % mod, (mod - 1) / 2) != mod - 1) a = rand() % mod;
    int t = ((LL)a * a - x + mod) % mod; 
    auto mul = [&](P a, P b) -> P {
        int A = ((LL)a.first * b.first + (LL)a.second * b.second % mod * t) % mod;
        int B = ((LL)a.first * b.second + (LL)a.second * b.first) % mod;
        return P(A, B);
    };
    P res = P(1, 0), tmp = P(a, 1); int y = (mod + 1) / 2;
    for (; y; y >>= 1, tmp = mul(tmp, tmp)) if (y & 1) res = mul(res, tmp);
    return res.first;
}

int inv2;

inline int solve(int T, int x) {
    int A = Cipolla(((LL)x * x + 4) % mod), B = Cipolla(((LL)x * x - 4 + mod) % mod), res = -1;
//    cout << T << ' ' << x << ' ' << A << ' ' << B << endl;
    fuck = BSGS(T, 1, 0);
    if (A != -1) {
        int a = (LL)(x + A) * inv2 % mod, b = (LL)(x - A + mod) * inv2 % mod;
        sol.clear(), BSGS1(T, a), BSGS1(T, b);
        for (auto t : sol) if (t % 2 == 0) {
            if (res == -1) res = t;
            res = min(res, t);
        }
    } 
    if (B != -1) {
        int a = (LL)(x + B) * inv2 % mod, b = (LL)(x - B + mod) * inv2 % mod;
        sol.clear(), BSGS1(T, a), BSGS1(T, b);
        for (auto t : sol) if (t % 2 == 1) {
            if (res == -1) res = t;
            res = min(res, t); 
        }
    }
    return res;
}

inline int solve1(int x, int sqrt5) {
    x = (LL)x * sqrt5 % mod; int T = (LL)(sqrt5 + 1) * inv2 % mod;
//    cout << T << ' ' << (LL)(mod - 1) * Pow(T, mod - 2) % mod << ' ' << x << endl;
    return solve(T, x);
}

signed main() {
//    freopen("ex_data2.in", "r", stdin), freopen("out.out", "w", stdout);
    srand((LL)new char);
    int T; scanf("%lld", &T);
    while (T--) {
        int x; scanf("%lld%lld", &x, &mod), inv2 = (mod + 1) / 2;
        int sqrt5 = Cipolla(5); sqrt5 = min(sqrt5, mod - sqrt5);
        int A = solve1(x, sqrt5), B = /*solve1(x, mod - sqrt5)*/ -1;
        if (A == -1 || B == -1) printf("%lld\n", max(A, B));
        else printf("%lld\n", min(A, B));
    }
    return 0;
} 
