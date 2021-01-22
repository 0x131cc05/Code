#include <bits/stdc++.h>
using namespace std;

const int N = 45;
const int M = 2010;
const int mod = 1e9 + 9;
const int inv2 = (mod + 1) / 2;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int frac[M], inv[M];

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % mod * inv[n - r] % mod;
}

int coef[M][M];

int calc(int a, int b, int c) {
    int res = (LL)coef[a + b][c] * C(a + b, a) % mod;
    if (!(a & 1) && !(b & 1)) 
        res = (res + (LL)coef[(a + b) / 2][c / 2] * C((a + b) / 2, a / 2)) % mod;
    return (LL)res * inv2 % mod;
}

int ct[3][N][N], id[127];

int get(int id, int x1, int y1, int x2, int y2) {
    return ct[id][x2][y2] - ct[id][x1 - 1][y2] - ct[id][x2][y1 - 1] + ct[id][x1 - 1][y1 - 1];
}

struct ColorfulJewelry {
    int getChains(vector<string> G, int k) {
        id['R'] = 0, id['G'] = 1, id['B'] = 2;
        
    }
};
