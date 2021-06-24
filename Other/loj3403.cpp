#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 200010;

int flag[N], prime[N], tot, sum[N], wkr[N];

void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (!flag[i]) {
            prime[++tot] = i, sum[tot] = sum[tot - 1], wkr[tot] = wkr[tot - 1];
            if (i % 3 == 1) sum[tot]++, wkr[tot]++;
            else if (i % 3 == 2) sum[tot]--;
        }
        for (int j = 1; j <= tot && i * prime[j] <= n; j++) {
            flag[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

LL val[2 * N], g[2 * N], p[2 * N], n; // g[i][j]: 1 ~ i, s(n) > p_j
int id1[N], id2[N], lim;

int get(LL x) {
    return x <= lim ? id1[x] : id2[n / x];
}

array<LL, 10> S(LL n, int m) {
    // cout << n << ' ' << m << endl;
    array<LL, 10> nw; nw.fill(0);
    if (n < prime[m]) return nw;
    // if (((g[get(n)] + p[get(n)]) % 2 + 2) % 2 != 1) cout << "FUCK: " << n << endl;
    LL A = (g[get(n)] + p[get(n)] - 1) / 2 - wkr[m - 1];
    nw[1] = A, nw[0] = p[get(n)] - (m - 1) - A;
    for (int i = m; i <= tot && (LL)prime[i] * prime[i] <= n; i++) {
        for (LL j = prime[i], c = 1; j * prime[i] <= n; j *= prime[i], c++) {
            int t = (prime[i] == 3 && c > 1) || prime[i] % 3 == 1;
            nw[prime[i] % 3 != 2]++; auto tmp = S(n / j, i + 1);
            if (t) rotate(tmp.begin(), tmp.end() - 1, tmp.end());
            for (int k = 0; k < 10; k++) nw[k] += tmp[k];
        }
    }
    return nw;
}

int main() {
    LL m; scanf("%lld%lld", &n, &m), m++;
    int ct = 0;
    while (m != 1) {
        if (m % 3) return puts("0"), 0;
        m /= 3, ct++; 
    }
    lim = ceil(sqrt(n)), sieve(lim); int blk = 0;
    for (LL l = 1; l <= n; l = n / (n / l) + 1) {
        LL t = n / l;
        blk++, val[blk] = t;
        if (t <= lim) id1[t] = blk; else id2[n / t] = blk;
        g[blk] = (t % 3 == 1) - 1, p[blk] = t - 1;
    }
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= blk && (LL)prime[i] * prime[i] <= val[j]; j++) {
            int pos = get(val[j] / prime[i]);
            if (prime[i] % 3) {
                int t = prime[i] % 3 == 1 ? 1 : -1;
                g[j] -= t * (g[pos] - sum[i - 1]);
            }
            p[j] -= p[pos] - (i - 1);
        }
    auto res = S(n, 1); res[0]++;
    printf("%lld\n", res[ct]);
}