#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
const int mod = 998244353;

typedef long long LL;

int S[N][N], a[N];

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int main() {
    S[0][0] = 1; int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i <= m; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= i; j++) 
            S[i][j] = (S[i - 1][j - 1] + (LL)j * S[i - 1][j]) % mod; 
    int res = 0;
    for (int k = 0, w = 1; k <= m; w = (LL)w * (n - k) % mod, k++) {
        int tmp = 0;
        for (int j = k; j <= m; j++) 
            tmp = (tmp + (LL)S[j][k] * a[j]) % mod;
        res = (res + (LL)tmp * w % mod * Pow(2, n - k)) % mod;
    }
    printf("%d\n", res);
}
