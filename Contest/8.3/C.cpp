#include <bits/stdc++.h>
using namespace std;

const int N = 300010;
const int mod = 998244353;

typedef long long LL;
typedef unsigned long long uLL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N << 2];

int GetR(int n) {
    int len = 1, l = 0;
    while (len <= n) len <<= 1, l++;
    for (int i = 1; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    return len;
}

void NTT(int a[], int len, int type) {
    for (int i = 1; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0; i < len; i += mid)
            for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod)
                t = (LL)a[j + (mid >> 1)] * w % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
    }
    if (!type) for (int inv = Pow(len, mod - 2), i = 0; i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

int n, mx;

void solve(int a, int b, int res[][2], int bit) {
    static int A[2][N << 2], B[2][N << 2], A0[N << 2], A1[N << 2]; 
    memset(A, 0, sizeof(A)), memset(B, 0, sizeof(B));
    for (int i = 0; i <= a; i++) A[(i >> bit) & 1][i]++;
    for (int i = 0; i <= b; i++) B[(i >> bit) & 1][mx - i]++;
    int len = GetR(mx * 2); NTT(A[0], len, 1), NTT(A[1], len, 1), NTT(B[0], len, 1), NTT(B[1], len, 1);
    for (int i = 0; i < len; i++) {
        A0[i] = ((LL)A[0][i] * B[0][i] + (LL)A[1][i] * B[1][i]) % mod;
        A1[i] = ((LL)A[1][i] * B[0][i] + (LL)A[0][i] * B[1][i]) % mod;
    }
    NTT(A0, len, 0), NTT(A1, len, 0);
    for (int i = -mx, t; i <= mx; i++) 
        t = abs(i), res[t][0] += A0[i + mx], res[t][1] += A1[i + mx];
}

int A[3][16][N][2], num[6]; uLL pre[3][16][2];

int main() {
    for (int i = 0; i < 6; i++) scanf("%d", &num[i]), mx = max(mx, num[i]);
    for (int i = 0; i <= 15; i++)
        solve(num[0], num[3], A[0][i], i), solve(num[1], num[4], A[1][i], i), solve(num[2], num[5], A[2][i], i);
    uLL res = 0;
    for (int i = 0; i <= mx; i++) {
        uLL w = 1;
        for (int j = 0; j <= 15; j++, w *= 2) {
            int t = (i >> j) & 1;
            for (int k = 0; k < 3; k++) {
                int k1 = (k + 1) % 3, k2 = (k1 + 1) % 3;
                for (int a = 0; a <= 1; a++) if (A[k][j][i][a])
                    for (int b = 0; b <= 1; b++) if (pre[k1][j][b])
                        for (int c = 0; c <= 1; c++) if (pre[k2][j][c])
                            if (t ^ a ^ b ^ c) 
                                res += w * A[k][j][i][a] * pre[k1][j][b] * pre[k2][j][c];
                for (int a = 0; a <= 1; a++) pre[k][j][a] += A[k][j][i][a];
            }
        }
    }
    printf("%llu", res);
}
