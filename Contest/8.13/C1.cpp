// f(x): 长度为 n 的弱回文串拆分数
// g(x): 最短周期为 n 的弱双回文串数量 g(x) = f * (mu × i)
// h(x): 弱双回文串数量
// f1(x): 长度为 n 的回文串数量
// g1(x): 最短周期为 n 的回文串数量 g1(x) = f1 * mu

#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int mod = 1e9 + 7;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int flag[N], prime[N], mu[N], n, c;
int sum[N], sum1[N], lim;

int ID(int x) { return x <= n / x ? x : lim + n / x; }

void sieve() {
    mu[1] = 1; int tot = 0;
    for (int i = 2; i <= N - 10; i++) {
        if (!flag[i]) prime[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * prime[j] <= N - 10; j++) {
            flag[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = mod - mu[i];
        }
    }
    for (int i = 1; i <= N - 10; i++) {
        sum[i] = (sum[i - 1] + mu[i]) % mod;
        sum1[i] = (sum1[i - 1] + (LL)mu[i] * i) % mod;
    }
}

int preMu(int n) {
    static int tmp[2 * N] = { 0 }; 
    if (n <= N - 10) return sum[n];
    int &res = tmp[ID(n)];
    if (res) return res;
    res = 1;
    for (int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        res = (res - (LL)(r - l + 1) * preMu(n / l)) % mod;
    }
    if (res < 0) res += mod;
    return res;
}

int preMu1(int n) { // sum of mu[i] * i
    static int tmp[2 * N] = { 0 };
    if (n <= N - 10) return sum1[n];
    int &res = tmp[ID(n)];
    if (res) return res;
    res = 1;
    for (int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        res = (res - ((LL)r * (r + 1) / 2 - (LL)l * (l - 1) / 2) % mod * preMu1(n / l)) % mod;
    }
    if (res < 0) res += mod;
    return res;
} 

int preC(int n) { // sum of c^i (from 1)
    int t = Pow(c, n + 1) - c; 
    if (t < 0) t += mod;
    return (LL)t * Pow(c - 1, mod - 2) % mod;
}

int preCI(int n) { // sum of c^i * i (from 1)
    int t = ((LL)n * Pow(c, n + 1) - preC(n)) % mod;
    if (t < 0) t += mod;
    return (LL)t * Pow(c - 1, mod - 2) % mod;
}

int preOddF(int n) {
    int up = (n + 1) / 2;
    return ((preCI(up) * 2 - preC(up)) % mod + mod) % mod;
}
int preEvenF(int n) {
    int up = n / 2;
    return (LL)preCI(up) * (c + 1) % mod;
}
int preF(int n) { 
    if (!n) return 0;
    static int tmp[N * 2] = { 0 };
    if (tmp[ID(n)]) return tmp[ID(n)];
    return tmp[ID(n)] = (preOddF(n) + preEvenF(n)) % mod; 
}

int preG(int n) {
    static int tmp[N * 2] = { 0 };
    if (tmp[ID(n)]) return tmp[ID(n)];
    int res = 0; 
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        res = (res + (LL)(preF(r) - preF(l - 1)) * preMu1(n / l)) % mod;
    }
    if (res < 0) res += mod;
    return tmp[ID(n)] = res;
}

int preH(int n) {
    int res = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        res = (res + (LL)(r - l + 1) * preG(n / l)) % mod;
    }
    return res;
}

int preF1(int n) {
    if (!n) return 0;
    static int tmp[N * 2] = { 0 };
    if (tmp[ID(n)]) return tmp[ID(n)];
    int res = preC(n / 2) * 2 % mod;
    if (res < 0) res += mod;
    if (n & 1) res = (res + Pow(c, (n + 1) / 2)) % mod;
    return tmp[ID(n)] = res;
}

int preG1(int n) {
    int res = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        res = (res + (LL)(preF1(r) - preF1(l - 1)) * preMu(n / l)) % mod;
    }
    if (res < 0) res += mod;
    return res;
}

int main() {
    scanf("%d%d", &n, &c), sieve();
    while ((lim + 1) * (lim + 1) <= n) lim++;
    // cout << preF(1) << ' ' << preF(2) << endl;
    printf("%d\n", (preH(n) - preG1(n) + mod) % mod);
}
