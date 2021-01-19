#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int N = 70010;

typedef long long LL;

int Pow(int x, int y, int mod = ::mod) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N << 2], Wn[2][18][N << 1];

void getWn(int len) {
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) {
        int w0 = Pow(3, (mod - 1) / mid), w1 = Pow(3, mod - 1 - (mod - 1) / mid);
        Wn[1][step][0] = Wn[0][step][0] = 1;
        for (int i = 1; i < (mid >> 1); i++) {
            Wn[1][step][i] = (LL)Wn[1][step][i - 1] * w0 % mod;
            Wn[0][step][i] = (LL)Wn[0][step][i - 1] * w1 % mod;
        } 
    }
}

void NTT(int a[], int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++)
        for (int i = 0; i < len; i += mid) 
            for (int j = i, t; j < i + (mid >> 1); j++)
                t = (LL)a[j + (mid >> 1)] * Wn[type][step][j - i] % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod;
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

int G(int x) {
    if (x == 2) return 1;
    for (int i = 2, flg = 1; i; i++, flg = 1) {
        for (int j = 2; j * j < x; j++) 
            if ((x - 1) % j == 0 && Pow(i, (x - 1) / j, x) == 1) { flg = 0; break; }
        if (flg) return i;
    }
}

int bk[N], g, len, frac[N], inv[N], p;

void pre() {
    g = G(p), len = frac[0] = inv[0] = 1; int l = 0;
    while (len <= p * 2) len <<= 1, l++;
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1); 
    getWn(len);
    for (int i = 0, t = 1; i < p; i++)
        bk[t] = i, t = (LL)t * g % p;
    for (int i = 1; i < p; i++) 
        frac[i] = (LL)frac[i - 1] * i % p, inv[i] = Pow(frac[i], p - 2, p);
}

int C(int n, int r) {
    return (LL)frac[n] * inv[r] % p * inv[n - r] % p;
}

void Mul(int A[], int B[], int res[]) {
    static int C[N << 2], D[N << 2]; 
    memset(C, 0, sizeof(C)), memset(D, 0, sizeof(D));
    for (int i = 1; i < p; i++) C[bk[i]] = A[i], D[bk[i]] = B[i];
    NTT(C, len, 1), NTT(D, len, 1);
    for (int i = 0; i < len; i++) C[i] = (LL)C[i] * D[i] % mod;
    NTT(C, len, 0);
    for (int i = 0, t = 1; i < len; i++)
        res[t] = (res[t] + C[i]) % 29, t = (LL)t * g % p;
}

int dp[11][N], tot, v[11];

void DP() {
    dp[0][1] = 1;
    for (int i = tot, cur = 1; i >= 1; i--, cur++) {
        int r = v[i];
        static int v[N]; memset(v, 0, sizeof(v));
        for (int j = 0; j <= r; j++) {
            int w = C(r, j);
            if (++v[w] >= 29) v[w] -= 29;
        }
        Mul(dp[cur - 1], v, dp[cur]);
    }
}

char n[110], tmp[110];

int ans[N];

int main() {
    freopen("C.in", "r", stdin), freopen("C.out", "w", stdout);
    scanf("%s%d", n + 1, &p), pre();
    int all = strlen(n + 1), fuck = 0;
    for (int i = 1; i <= all; i++)
        fuck = (fuck * 10 + n[i] - '0') % 29;
    fuck = (fuck + 1) % 29;
    while (233) {
        bool flag = false;
        int nw = 0;
        for (int i = 1; i <= all; i++) {
            nw = nw * 10 + n[i] - '0', flag |= n[i] - '0';
            tmp[i] = nw / p + '0', nw %= p;
        }
        if (!flag) break;
        v[++tot] = nw, swap(n, tmp);
    }
    DP(), ans[0] = fuck;
    for (int i = 1; i < p; i++)
        ans[i] = dp[tot][i];
    for (int i = 1; i < p; i++) ans[0] = (ans[0] - ans[i] + 29) % 29;
    for (int i = 0; i < p; i++) {
        if (ans[i] < 10) printf("%d", ans[i]);
        else putchar(ans[i] - 10 + 'A');
    }
}
