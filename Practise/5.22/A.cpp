#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int inv = (mod + 1) / 3;

typedef long long LL;

int draw_territory(int N, int A, int B, vector<int> D, vector<int> L) {
    int t = L[0] + 1;
    int a = (LL)t * (t + 1) / 2 % mod;
    int b = (LL)t * (t + 1) % mod * (t + 2) % mod * inv % mod;
    return ((LL)a * A + (LL)b * B) % mod;
}