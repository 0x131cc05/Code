#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int mod = 998244353;
const int N = 500010;

int r[N << 2];

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

void NTT(int a[], int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0; i < len; i += mid)
            for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod) 
                t = (LL)a[j + (mid >> 1)] * w % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++) 
        a[i] = (LL)a[i] * inv % mod;
}

int A[N << 2], st[20][N], lg[N];

int Max(int a, int b) {
    return A[a] >= A[b] ? a : b;
}

int main() {
    for (int i = 1; i <= 500000; i++)
        for (int j = i; j <= 500000; j += i) A[j]++;
    int len = 1, l = 0;
    while (len <= 1000000) len <<= 1, l++;
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    NTT(A, len, 1);
    for (int i = 0; i < len; i++) A[i] = (LL)A[i] * A[i] % mod;
    NTT(A, len, 0);
    for (int i = 1; i <= 500000; i++) st[0][i] = i;
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j + (1 << i) - 1 <= 500000; j++)
            st[i][j] = Max(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
    for (int i = 2; i <= 500000; i++) lg[i] = lg[i >> 1] + 1;
    int q; scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        int len = lg[r - l + 1], mx = Max(st[len][l], st[len][r - (1 << len) + 1]);
        printf("%d %d\n", mx, A[mx]);
    }
}
