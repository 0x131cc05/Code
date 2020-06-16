#include <bits/stdc++.h>
using namespace std;

const int N = 510;
const int mod = 1e9 + 7;

typedef long long LL;

inline int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod) if (y & 1) res = (LL)res * x % mod;
    return res;
}


char s[N]; int val[16][8], tp[16], to[256], ncnt, m;

inline void Inc(int &x, int y) {
    x += y, x -= x >= mod ? mod : 0;
}

inline void Dec(int &x, int y) {
    x -= y, x += x < 0 ? mod : 0;
}

inline void andFWT(vector<int> &a, int len, int type) {
    for (int mid = 2; mid <= len; mid <<= 1)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++) 
                if (type) Inc(a[j], a[j + (mid >> 1)]);
                else Dec(a[j], a[j + (mid >> 1)]);
}

inline void orFWT(vector<int> &a, int len, int type) {
    for (int mid = 2; mid <= len; mid <<= 1)
        for (int i = 0; i < len; i += mid)
            for (int j = i; j < i + (mid >> 1); j++) 
                if (type) Inc(a[j + (mid >> 1)], a[j]);
                else Dec(a[j + (mid >> 1)], a[j]);
}

vector<int> solve(int l, int r) {
    if (l == r) {
        vector<int> res(1 << m, 0);
        for (int i = 0; i < 8; i++) if (to[(int)s[l]] == i || s[l] == '?') {
            int hh = 0;
            for (int j = 0; j < m; j++) if (val[j][i]) hh |= 1 << j;
            res[hh]++;
        }
        return res;
    }
    if (r - l + 1 == 3) return solve(l + 1, r - 1);
    int pos = -1;
    for (int i = l, layer = 0; i <= r; i++) {
        if (s[i] == '(') layer++;
        else if (s[i] == ')') layer--;
        if (!layer && (s[i] == '|' || s[i] == '&' || s[i] == '?')) {
            pos = i; break;
        }
    }
    if (pos == -1) return solve(l + 1, r - 1);
    vector<int> L = solve(l, pos - 1), R = solve(pos + 1, r), res(1 << m, 0);
    if (s[pos] != '&') {
        vector<int> tl = L, tr = R;
        orFWT(tl, 1 << m, 1), orFWT(tr, 1 << m, 1);
        for (int i = 0; i < 1 << m; i++) tl[i] = (LL)tl[i] * tr[i] % mod;
        orFWT(tl, 1 << m, 0), res = tl;
    }
    if (s[pos] != '|') {
        vector<int> tl = L, tr = R;
        andFWT(tl, 1 << m, 1), andFWT(tr, 1 << m, 1);
        for (int i = 0; i < 1 << m; i++) tl[i] = (LL)tl[i] * tr[i] % mod;
        andFWT(tl, 1 << m, 0);
        for (int i = 0; i < 1 << m; i++) Inc(res[i], tl[i]);
    }
    return res;
}

int main() {
    scanf("%s", s + 1); int n = strlen(s + 1), lst = 0; scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 4; j++) scanf("%d", &val[i][j]), val[i][j + 4] = val[i][j] ^ 1;
        scanf("%d", &tp[i]);
        if (tp[i]) lst |= 1 << i;
    }
    to['A'] = 0, to['B'] = 1, to['C'] = 2, to['D'] = 3, to['a'] = 4, to['b'] = 5, to['c'] = 6, to['d'] = 7;
    printf("%d\n", solve(1, n)[lst]);
}
