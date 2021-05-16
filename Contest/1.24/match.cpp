#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int N = 100010;

typedef long long LL;
typedef pair<int, int> P;

int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}

int r[N << 2];

void NTT(int a[], int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int Wn = Pow(3, type ? (mod - 1) / mid : mod - 1 - (mod - 1) / mid);
        for (int i = 0; i < len; i += mid)
            for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (LL)w * Wn % mod) 
                t = (LL)w * a[j + (mid >> 1)] % mod, a[j + (mid >> 1)] = (a[j] - t + mod) % mod, a[j] = (a[j] + t) % mod; 
    }
    if (!type) for (int i = 0, inv = Pow(len, mod - 2); i < len; i++)
        a[i] = (LL)a[i] * inv % mod;
}

char s[N], t[N]; int n, m, sum[N], ok[N];

void match() {
    static int A[N << 2], B[N << 2], C[N << 2], D[N << 2];
    for (int i = 1; i <= n; i++) {
        int c = s[i] == '?' ? 0 : s[i] - 'a' + 1, c1 = t[i] - 'a' + 1;
        sum[i] = (sum[i - 1] + c * c * c) % mod;
        A[i] = (LL)(mod - 2) * c * c % mod, B[i] = c;
        C[m - i] = c1, D[m - i] = c1 * c1;
    }
    int len = 1, l = 0;
    while (len <= n + m) len <<= 1, l++;
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    NTT(A, len, 1), NTT(B, len, 1), NTT(C, len, 1), NTT(D, len, 1);
    for (int i = 0; i < len; i++)
        A[i] = ((LL)A[i] * C[i] + (LL)B[i] * D[i]) % mod;
    NTT(A, len, 0);
    for (int i = 0; i <= n - m; i++) {
        int x = (sum[i + m] - sum[i] + mod) % mod;
        x = (x + A[i + m]) % mod;
        if (!x) ok[i + m] = 1;
    }
}

int nxt[N];

void getnxt() {
    for (int i = 2; i <= m; i++) {
        int lst = nxt[i - 1];
        while (lst && t[lst + 1] != t[i]) lst = nxt[lst];
        nxt[i] = lst + (t[lst + 1] == t[i]);
    }
}

multiset<P> S[21][N];
vector<tuple<int, int, P>> add[N], del[N];

P f[N], g[N];

void chkmax(P &a, P b) {
    if (b.first > a.first) a = b;
}

int main() {
    freopen("match.in", "r", stdin), freopen("match.out", "w", stdout);
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1), m = strlen(t + 1), match(), getnxt();
    vector<int> wkr;
    for (int nw = nxt[m]; nw; nw = nxt[nw]) 
        wkr.push_back(m - nw);
    vector<int> diff, pos; vector<P> seg;
    for (int l = 0; l < wkr.size(); l++) {
        int r = l;
        while (r + 1 < wkr.size() && wkr[r + 1] - wkr[r] == wkr[l + 1] - wkr[l]) r++;
        if (l == r) pos.push_back(wkr[l]);
        else diff.push_back(wkr[l + 1] - wkr[l]), seg.push_back(P(wkr[l], wkr[r]));
        l = r;
    }
    for (int i = m; i <= n; i++) {
        for (auto t : add[i]) S[get<0>(t)][get<1>(t)].insert(get<2>(t));
        for (auto t : del[i]) {
            int a = get<0>(t), b = get<1>(t);
            S[a][b].erase(S[a][b].find(get<2>(t)));
        }
        if (ok[i]) {
            P tmp = f[i - m];
            for (auto t : pos) chkmax(tmp, P(g[i - t].first, i - t));
            for (int j = 0; j < diff.size(); j++) {
                int at = (i - seg[j].first) % diff[j];
                if (S[j][at].size()) tmp = max(tmp, *S[j][at].rbegin());
            }
            g[i] = tmp, g[i].first++;
            for (int j = 0; j < diff.size(); j++) {
                int l = i + seg[j].first, r = i + seg[j].second;
                if (l <= n) add[l].push_back(make_tuple(j, i % diff[j], P(g[i].first, i)));
                if (r < n) del[r + 1].push_back(make_tuple(j, i % diff[j], P(g[i].first, i)));
            }
        }
        f[i] = max(f[i - 1], P(g[i].first, i));
    }
    printf("%d\n", f[n].first);
    int nw = f[n].second, lst = n + 1;
    while (nw) {
        for (int i = nw - m + 1; i <= nw && i < lst; i++) 
            if (s[i] == '?') s[i] = t[i - (nw - m)];
        lst = nw - m + 1, nw = g[nw].second;
    }
    for (int i = 1; i <= n; i++) if (s[i] == '?') s[i] = 'a';
    puts(s + 1);
}