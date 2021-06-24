#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int N = 10010;
const int M = 110;
const int P = 131;

typedef long long LL;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

vector<int> v[N];

char s[M][N]; int len[M], p[26], inv[26];

int trans[M][N][26], K;

int A[N], B[N];

void preTrans(int id) {
    char *t = s[id]; int n = len[id];
    trans[id][0][t[1] - 'a'] = 1;
    static int nxt[N]; nxt[0] = nxt[1] = 0;
    for (int i = 2; i <= n; i++) {
        int tmp = nxt[i - 1];
        while (tmp && t[tmp + 1] != t[i]) tmp = nxt[tmp];
        nxt[i] = tmp + (t[tmp + 1] == t[i]); 
    }
    for (int i = 1; i < n; i++) {
        for (int c = 0; c < K; c++) {
            if (t[i + 1] == c + 'a') trans[id][i][c] = i + 1;
            else trans[id][i][c] = trans[id][nxt[i]][c];
        }
    }
}

void work(int id) {
    char *t = s[id]; int n = len[id];
    for (int i = 1; i <= n; i++) A[i] = B[i] = 0;
    A[0] = 1, B[0] = 0;
    for (int i = 1; i <= n; i++) {
        int w = p[t[i] - 'a'], tA = A[i - 1], tB = B[i - 1];
        for (int j = 0; j < K; j++) if (t[i] != j + 'a') {
            int k = trans[id][i - 1][j], w1 = p[j];
            tA = (tA - (LL)w1 * A[k]) % mod;
            tB = (tB - (LL)w1 * B[k]) % mod;
        }
        tA = (LL)(tA + mod) * inv[t[i] - 'a'] % mod;
        tB = (LL)(tB + mod - 1) * inv[t[i] - 'a'] % mod;
        A[i] = tA, B[i] = tB;
    }
    int x = (LL)(mod - B[n]) * Pow(A[n], mod - 2) % mod;
    v[id].resize(n + 1);
    for (int i = 0; i <= n; i++)
        v[id][i] = ((LL)x * A[i] + B[i]) % mod;
} 

int G[M][M], val[M][M], res[M];

void gauss(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) if (G[j][i]) {
            swap(G[i], G[j]), swap(val[i], val[j]);
            break;
        }
        assert(G[i][i]);
        int t = Pow(G[i][i], mod - 2);
        for (int j = i + 1; j <= n; j++) if (G[j][i]) {
            int w = (LL)t * G[j][i] % mod;
            for (int k = 1; k <= n; k++) G[j][k] = (G[j][k] + (LL)(mod - G[i][k]) * w) % mod;
            for (int k = 1; k <= n; k++) val[j][k] = (val[j][k] + (LL)(mod - val[i][k]) * w) % mod;
        }
    }
    for (int j = 1; j <= n; j++) 
        res[j] = (LL)val[n][j] * Pow(G[n][n], mod - 2) % mod;
}

char r[N];

int cur[M];

int main() {
    freopen("string.in", "r", stdin), freopen("string.out", "w", stdout);
    int n, m; scanf("%d%d%d", &n, &m, &K);
    int t = Pow(100, mod - 2);
    for (int i = 0; i < K; i++) {
        scanf("%d", &p[i]), p[i] = (LL)p[i] * t % mod;
        inv[i] = Pow(p[i], mod - 2);
    }
    int ct = 0; set<int> s; static char c[N];
    for (int i = 1; i <= n; i++) {
        scanf("%s", c + 1);
        int hsh = 0, l = strlen(c + 1);
        for (int j = 1; j <= l; j++) 
            hsh = ((LL)hsh * P + c[j] - 'a' + 1) % mod;
        if (!s.count(hsh)) {
            ct++, s.insert(hsh);
            for (int j = 1; j <= l; j++)
                ::s[ct][j] = c[j];
            len[ct] = l;
        }
    }
    n = ct;
    for (int i = 1; i <= n; i++) preTrans(i), work(i);
    for (int i = 1; i <= n; i++) {
        val[i][i] = 1;
        for (int j = 1; j <= n; j++) {
            int pos = 0;
            for (int k = 1; k <= len[j]; k++) 
                pos = trans[i][pos][::s[j][k] - 'a'];
            G[i][j] = v[i][pos];
        }
        G[i][n + 1] = 1;
    }
    for (int i = 1; i <= n; i++) G[n + 1][i] = 1;
    val[n + 1][n + 1] = 1;
    gauss(n + 1);
    scanf("%s", r + 1); int l = strlen(r + 1);
    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= n; j++) cur[j] = trans[j][cur[j]][r[i] - 'a'];
        int ans = res[n + 1];
        for (int j = 1; j <= n; j++) ans = (ans + (LL)res[j] * v[j][cur[j]]) % mod;
        printf("%d\n", (ans + i) % mod);
    }
}