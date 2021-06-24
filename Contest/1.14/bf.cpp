#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 10010;

int Pow(int x, int y, int mod) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int frac[N], inv[N], p;

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % p * inv[n - r] % p;
}

int C1(int n, int r) {
    if (n < r) return 0;
    if (n < p) return C(n, r);
    return (LL)C(n % p, r % p) * C1(n / p, r / p) % p;
}

int res[N];

int main() {
    int n; cin >> n >> p, frac[0] = inv[0] = 1;
    for (int i = 1; i < p; i++) 
        frac[i] = (LL)frac[i - 1] * i % p, inv[i] = Pow(frac[i], p - 2, p);
    for (int i = 0; i <= n; i++)
        res[C1(n, i)]++;
    for (int i = 0; i < p; i++) {
        res[i] %= 29;
        if (res[i] < 10) printf("%d", res[i]);
        else putchar(res[i] - 10 + 'A');
    }
}