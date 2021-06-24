#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

typedef long long LL;

template<class T> void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int num[N], fk[N];

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
    int T; read(T);
    while (T--) {
        int n, m, mn = 1e9; read(n), read(m);
        for (int i = 0; i < n; i++) read(num[i]), mn = min(mn, num[i]);
        for (int i = 0; i < n; i++) num[i] -= mn;
        bool flag = true;
        for (int i = 2 * m; i < n; i++) {
            if (num[i] != num[i & ((m << 1) - 1)]) {
                flag = false; break;
            }
        }
        if (!flag) { puts("-1"); continue; }
        LL res = 0;
        for (int i = 0; i < 2 * m; i++) res += num[i];
        if (res % m) { puts("-1"); continue; }
        res /= m;
        if (m <= 1000) {
            for (int i = 1; i <= m; i <<= 1) {
                int len = 2 * i;
                for (int j = 0; j < len; j++) {
                    int mn = 1e9;
                    for (int k = 0; k < 2 * m; k++) {
                        int cur = k & (len - 1);
                        int l = cur >= j ? cur - j : cur + len - j;
                        if (l < i) mn = min(mn, num[k]);
                    }
                    for (int k = 0; k < 2 * m; k++) {
                        int cur = k & (len - 1);
                        int l = cur >= j ? cur - j : cur + len - j;
                        if (l < i) num[k] -= mn;
                    }
                }
            }
            for (int i = 0; i < 2 * m; i++) if (num[i]) flag = false;
            if (!flag) { puts("-1"); continue; }
            printf("%lld\n", res);
        } else {
            int g = 0;
            for (int i = 0; i < 2 * m; i++) g = gcd(g, num[i]);
            if (g) for (int i = 0; i < 2 * m; i++) num[i] /= g, fk[i] = num[i] == 0;
            for (int i = m, t = 1; i >= 1 && flag; i >>= 1, t <<= 1) {
                for (int j = 0; j < i; j++) {
                    if ((num[j] & (t - 1)) != (num[j + i] & (t - 1))) {
                        flag = false; break;
                    }
                    num[j] = (num[j] + num[j + i]) & (m - 1), fk[j] &= fk[j + i];
                }
            }
            if (fk[0] ^ fk[1]) flag = false;
            if (!flag) { puts("-1"); continue; }
            printf("%lld\n", res);
        }
    }
}