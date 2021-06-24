#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    freopen("color.in", "r", stdin), freopen("color.out", "w", stdout);
    int T; scanf("%d", &T);
    while (T--) {
        LL a, b, k; scanf("%lld%lld%lld", &a, &b, &k);
        if (a == b) { puts(k == 1 ? "NO" : "YES"); continue; }
        LL g = gcd(a, b); a /= g, b /= g;
        if (a > b) swap(a, b);
        if ((b - 2) / a + 1 < k) puts("YES");
        else puts("NO");
    }
}
