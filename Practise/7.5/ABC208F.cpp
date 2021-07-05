#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int mod = 1e9 + 7;
const int N = 2500500;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int k, sum[N];
int flag[N], prime[N], tot;

int lim;

void sieve() {
    sum[1] = 1;
    for (int i = 2; i <= lim; i++) {
        if (!flag[i]) sum[i] = Pow(i, k), prime[++tot] = i;
        for (int j = 1; j <= tot && i * prime[j] <= lim; j++) {
            flag[i * prime[j]] = 1, sum[i * prime[j]] = (LL)sum[i] * sum[prime[j]] % mod;
            if (i % prime[j] == 0) break;
        }
    }
}

int inv[N];

void pre() {
    inv[0] = 1;
    for (int i = 1; i <= lim; i++) inv[i] = (LL)inv[i - 1] * i % mod;
    inv[lim] = Pow(inv[lim], mod - 2);
    for (int i = lim - 1; i >= 1; i--) inv[i] = (LL)inv[i + 1] * (i + 1) % mod;
}

int solve(LL n) {
    n %= mod;
    int *A = flag, *B = prime;
    A[0] = n, B[lim] = n - lim;
    for (int i = 1; i <= lim; i++) 
        A[i] = (LL)A[i - 1] * (n - i + mod) % mod;
    for (int i = lim - 1; i >= 0; i--)
        B[i] = (LL)B[i + 1] * (n - i + mod) % mod;
    int res = 0;
    for (int i = 0; i <= lim; i++) {
        int l = (LL)inv[i] * (i ? A[i - 1] : 1) % mod;
        int r = (LL)inv[lim - i] * (i != lim ? B[i + 1] : 1) % mod;
        if ((lim - i) & 1) r = mod - r;
        res = (res + (LL)l * r % mod * sum[i]) % mod;
    }
    return (res + mod) % mod;
}

int main() {
    LL n; int m; cin >> n >> m >> k, pre();
    lim = k + m + 1;
    sieve(), pre();
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= lim; j++)
            sum[j] = (sum[j] + sum[j - 1]) % mod;
    cout << solve(n) << endl;
}