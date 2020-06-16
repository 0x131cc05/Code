#include <bits/stdc++.h>
using namespace std;

const int N = (1 << 18) + 1;
const int mod = 1e9 + 7;

typedef long long LL;

int ct[N], f[N];

int flag[N], phi[N], prime[N], tot;

inline void sieve() {
    phi[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!flag[i]) prime[++tot] = i, phi[i] = i - 1;
        for (int j = 1; j <= tot && i * prime[j] < N; j++) {
            flag[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } 
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}

template<class T> inline void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar(); 
}

int main() {
    freopen("sequence.in", "r", stdin), freopen("sequence.out", "w", stdout);
    int n; scanf("%d", &n), sieve();
    for (int i = 1, a; i <= n; i++) read(a), ct[a]++;
    f[0] = 1;
    for (int i = 0; i < 18; i++) {
        for (int s = (1 << (i + 1)) - 1; s >= 1 << i; s--) {
            int t = s ^ (1 << i);
            for (int ss = t; ; ss = (ss - 1) & t) {
                int s1 = ss | (1 << i);
                f[s] = (f[s] + (LL)ct[s1] * f[s ^ s1]) % mod;
                if (!ss) break;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < 1 << 18; i++) 
        res = (res + (LL)phi[1 + i] * f[i]) % mod;
    for (int i = 1; i <= ct[0]; i++) res = res * 2 % mod;
    printf("%d\n", res);
}
