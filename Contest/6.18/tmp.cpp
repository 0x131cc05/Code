#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 9;

typedef long long LL;

inline void Inc(int &x, int y) { x += y, x -= x >= mod ? mod : 0; }

inline void Dec(int &x, int y) { x -= y, x += x < 0 ? mod : 0; }

inline void FWT(int a[], int len) {
    for (int mid = 2; mid <= len; mid <<= 1)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++) 
                Inc(a[j + (mid >> 1)], a[j]);
}

inline void IFWT(int a[], int len) {
    for (int mid = 2; mid <= len; mid <<= 1)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++) 
                Dec(a[j + (mid >> 1)], a[j]);
}

int A[21][1 << 20], B[21][1 << 20], C[21][1 << 20];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0, a; i < 1 << n; i++) 
        scanf("%d", &a), A[__builtin_popcount(i)][i] = a;
    for (int i = 0, b; i < 1 << n; i++)
        scanf("%d", &b), B[__builtin_popcount(i)][i] = b;
    for (int i = 0; i <= n; i++) FWT(A[i], 1 << n);
    for (int i = 0; i <= n; i++) FWT(B[i], 1 << n);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= i; j++) 
            for (int k = 0; k < 1 << n; k++)
                C[i][k] = (C[i][k] + (LL)A[j][k] * B[i - j][k]) % mod;
    for (int i = 0; i <= n; i++) IFWT(C[i], 1 << n);
    for (int i = 0; i <= n; i++) printf("%d ", C[__builtin_popcount(i)][i]);
}
