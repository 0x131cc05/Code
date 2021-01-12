#include <bits/stdc++.h>
using namespace std;

const int N = 4010;

typedef long long LL;

int f[N], num[N];

int Pow(int x, int y, int mod) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int k, mod; scanf("%d%d", &k, &mod);
        for (int i = 1; i <= k; i++) scanf("%d", &num[i]);
        vector<int> coef = {1};
        f[0] = f[1] = 1;
        for (int i = 2; i <= k; i++) f[i] = (f[i - 1] + f[i - 2]) % mod;
        for (int i = 1; i <= k; i++) {
            vector<int> nw(i + 1);
            for (int j = 0; j <= i; j++) {
                if (j) nw[j] = coef[j - 1];
                if (j != i) nw[j] = (nw[j] + (LL)coef[j] * (mod - f[i])) % mod;
            }
            coef = nw;
        } 
        int res = 0;
        for (int i = 0; i + 1 < coef.size(); i++) res = (res + (LL)coef[i] * num[i + 1]) % mod;
        res = mod - res;
        printf("%lld\n", (LL)res * Pow(coef.back(), mod - 2, mod) % mod);
    }
}