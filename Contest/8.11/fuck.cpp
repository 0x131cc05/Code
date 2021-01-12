#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

typedef long long LL;

int tot;

struct matrix {
    int a[57][57];
    matrix() { memset(a, 0, sizeof(a)); }
    int* operator [] (int x) { return a[x]; }
    matrix operator * (matrix &b) {
        matrix res;
        for (int i = 1; i <= tot; i++)
            for (int k = 1; k <= tot; k++) if (a[i][k])
                for (int j = 1; j <= tot; j++) 
                    res[i][j] = (res[i][j] + (LL)a[i][k] * b[k][j]) % mod;
        return res;
    }
};

matrix Pow(matrix x, LL y) {
    matrix res;
    for (int i = 1; i <= tot; i++) res[i][i] = 1;
    for (; y; y >>= 1, x = x * x) if (y & 1) res = res * x;
    return res;
}

int id[12][12];

//matrix pw1[1 << 16], pw2[1 << 16];

int main() {
    matrix base; 
    for (int j = 0; j <= 9; j++)
        for (int k = 1; j + k <= 10; k++) id[j][k] = ++tot;
    tot++, base[tot][tot] = 1;
    for (int j = 0; j <= 9; j++)
        for (int k = 1; j + k <= 10; k++) {
            int t = id[j][k];
            base[t][id[j + k][1]] = j + k - 10 + mod;
            base[t][id[j][k]] = k;
            base[t][id[j][k + 1]] = 10 - j - k;
            base[t][tot] = k;
        }
//    for (int i = 1; i <= tot; i++) pw1[0][i][i] = pw2[0][i][i] = 1;
//    for (int i = 1; i < 1 << 16; i++) pw1[i] = pw1[i - 1] * base, cout << i << endl;
//    cout << "end" << endl;
//    pw2[1] = Pow(base, 1 << 16);
//    for (int i = 2; i < 1 << 16; i++) pw2[i] = pw2[i - 1] * pw2[1];
//    cout << tot << endl;
    int T; scanf("%d", &T);
    while (T--) {
        LL n; scanf("%lld", &n);
        matrix nw = Pow(base, n);//pw1[n & ((1 << 16) - 1)] * pw2[n >> 16];
        printf("%d\n", nw[id[0][1]][tot]);
    }   
}
