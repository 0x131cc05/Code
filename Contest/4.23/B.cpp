#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int inv2 = 499122177;
const int N = 1000010;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

inline void FWT(vector<int> &a, int len) {
    for (int mid = 2; mid <= len; mid <<= 1)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++) {
                int t = (a[j] + a[j + (mid >> 1)]) % mod, t1 = (a[j] - a[j + (mid >> 1)] + mod) % mod;
                a[j] = t, a[j + (mid >> 1)] = t1;
            }
}

inline void IFWT(vector<int> &a, int len) {
    for (int mid = 2; mid <= len; mid <<= 1)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++) {
                int t = (LL)(a[j] + a[j + (mid >> 1)]) * inv2 % mod, t1 = (LL)(a[j] - a[j + (mid >> 1)] + mod) * inv2 % mod;
                a[j] = t, a[j + (mid >> 1)] = t1;
            }
}

int p[N][11], a[11];

vector<int> F[1 << 19];

int w[1 << 10];

int main() {
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= k; j++) scanf("%d", &p[i][j]);
    for (int i = 0; i < 1 << m; i++) F[i].resize(1 << k);
    for (int s = 1; s < 1 << k; s++) { // 方程组的值
        vector<int> tmp(1 << m, 0); 
        for (int i = 1; i <= n; i++) {
            int pos = 0;
            for (int j = 1; j <= k; j++) if (s & (1 << j - 1))
                pos ^= p[i][j];
            tmp[pos]++;
        }
        FWT(tmp, 1 << m);
        for (int i = 0; i < 1 << m; i++) 
            F[i][s] = tmp[i];
    }
    for (int i = 0; i < 1 << m; i++)  // 求解方程组
        F[i][0] = n, IFWT(F[i], 1 << k);
    for (int i = 0; i < 1 << k; i++) { // 预处理每个编号对应的系数
        int t = 0;
        for (int j = 1; j <= k; j++) {
            if (i & (1 << j - 1)) t = (t + mod - a[j]) % mod;
            else t = (t + a[j]) % mod;
        }
        w[i] = t;
    }
    vector<int> ans(1 << m, 0);
    for (int i = 0; i < 1 << m; i++) {
        int t = 1;
        for (int j = 0; j < 1 << k; j++)
            t = (LL)t * Pow(w[j], F[i][j]) % mod;
        ans[i] = t;
    }
    IFWT(ans, 1 << m);
    for (int i = 0; i < 1 << m; i++) printf("%d ", ans[i]);
    return 0;
}