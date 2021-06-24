#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int mod = 998244353;

typedef long long LL;
typedef pair<int, int> P;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int frac[N], inv[N], pw2[N]; 

inline int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

P solve(int a, int b, int c, int d) {
//    cout << "solve: " << a << ' ' << b << ' ' << c << ' ' << d << endl;
    if (b == 0 && c == 0) {
        if (a == d) return P(0, 1);
        if ((a + d) % 2 == 0) return P(2, 2);
        return P(1, 1);
    }
    if (b < 0) {
        if (a % 2 == 0) a = 2 - a;
        if (d % 2 == 0) d = 2 - d;
        return solve(a, -b, c, d);
    }  
    if (c < 0) {
        if (a % 2 == 1) a = 4 - a;
        if (d % 2 == 1) d = 4 - d;
        return solve(a, b, -c, d);
    }
    if (b < c) return solve(a ^ 1, c, b, d ^ 1);
    if (!c) {
        int len = (b - 1) * 3 + 1;
        if (a == 1 || a == 3) len++;
        if (d == 1 || d == 3) len++;
        if (a == 2) len += 2;
        if (d == 0) len += 2;
        return P(len, pw2[b - 1 + (a == 2) + (d == 0)]);
    }
    if (a == 1 || a == 0 || d == 2 || d == 3) {
        P fuck(1e9, 0);
        for (int t1 = 2; t1 <= 3; t1++)
            for (int t2 = 0; t2 <= 1; t2++) {
                int tb = b - (t1 == 2) - (t2 == 0), tc = c - (t1 == 3) - (t2 == 1);
                if (tb < 0 || tc < 0) continue;
                P res = solve(t1, tb, tc, t2);
//                cout << t1 << ' ' << tb << ' ' << tc << ' ' << t2 << ' ' << res.first << ' ' << res.second << endl;
                if (a == t1) res.first += 2, res.second = res.second * 2 % mod;
                else if (a % 2 != t1 % 2) res.first++;
                if (d == t2) res.first += 2, res.second = res.second * 2 % mod;
                else if (d % 2 != t2 % 2) res.first++;
                res.first += 2;
                if (res.first < fuck.first) fuck = res;
                else if (res.first == fuck.first) fuck.second = (fuck.second + res.second) % mod;
            }
        return fuck;
    }
    if (b == c) {
        if (a == 3) return solve(a ^ 1, b, c, d ^ 1);
        if (d == 1) return P(4 * b + 1, 1);
        P A = solve(a, b - 1, c, 0), B = solve(a, b, c - 1, 1);
        A.first += 3, B.first += 2, A.second = A.second * 2 % mod;
        if (A.first != B.first) return A.first < B.first ? A : B;
        return P(A.first, (A.second + B.second) % mod);
    }
    if (a == 2 && d == 1) {
        int t = c * 2, delta = b + c - t;
        return P(c * 4 + (b - c) * 3 + 1, (LL)C(delta + c, c) * pw2[delta] % mod);
    }
    if (a == 2 && d == 0) {
        int t = c * 2 - 1, delta = b + c - t;
        return P(c * 4 + (b - c) * 3 + 2, (LL)C(delta + c, c) * pw2[delta] % mod);
    }
    if (a == 3 && d == 1) {
        int t = c * 2 + 1, delta = b + c - t;
        return P(c * 4 + (b - c) * 3, (LL)C(delta + c, c) * pw2[delta] % mod);
    }
    if (a == 3 && d == 0) {
        int t = c * 2, delta = b + c - t;
        return P(c * 4 + (b - c) * 3 + 1, (LL)C(delta + c, c) * pw2[delta] % mod);
    }
}

int main() {
    frac[0] = inv[0] = pw2[0] = 1;
    for (int i = 1; i <= N - 10; i++) {
        frac[i] = (LL)frac[i - 1] * i % mod;
        pw2[i] = 2 * pw2[i - 1] % mod;
    }
    inv[N - 10] = Pow(frac[N - 10], mod - 2);
    for (int i = N - 11; i >= 1; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % mod;
    int T; scanf("%d", &T);
    while (T--) {
        int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
        P res = solve(a, b, c, d);
        printf("%d %d\n", res.first, res.second);
    }
}
