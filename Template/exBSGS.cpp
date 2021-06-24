#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

unordered_map<int, int> mp;

int BSGS(int pls, int a, int b, int mod) { // pls * a^x === b 
    pls %= mod, a %= mod, b %= mod;
    if (pls == b) return 0;
    int m = ceil(sqrt(mod)), ls = 1; 
    for (int i = 0; i < m; i++, ls = (LL)ls * a % mod) 
        mp[(LL)ls * b % mod] = i;
    for (int i = 1, nw = (LL)ls * pls % mod; i <= m; i++, nw = (LL)nw * ls % mod) 
        if (mp.count(nw)) return i * m - mp[nw];
    return -1;
}

int exBSGS(int a, int b, int mod) {
    if (b == 1) return 0;
    a %= mod, b %= mod;
    int pls = 1, ct = 0, g; mp.clear();
    while ((g = gcd(a, mod)) != 1) {
        ct++, pls = (LL)pls * (a / g) % mod, mod /= g;
        if (b % g != 0) return -1;
        b /= g;
    }
    int res = BSGS(pls, a, b, mod);
    return ~res ? res + ct : -1;
}

int main() {
    int a, b, mod;
    while (~scanf("%d%d%d", &a, &mod, &b) && mod) {
        int res = exBSGS(a, b, mod);
        if (~res) printf("%d\n", res);
        else puts("No Solution");
    }
        
}