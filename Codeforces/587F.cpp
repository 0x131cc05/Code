#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int SZ = 450;

typedef pair<int, int> P;

int x[N], y[N], c[N], m = 127, rk[N], height[N], sa[N];

inline void sort(int len) {
    for (int i = 1; i <= m; i++) c[i] = 0;
    for (int i = 1; i <= len; i++) c[x[i]]++;
    for (int i = 1; i <= m; i++) c[i] += c[i - 1];
    for (int i = len; i >= 1; i--) sa[c[x[y[i]]]--] = y[i]; 
}

inline void SA(char s[], int len) {
    for (int i = 1; i <= len; i++) y[i] = i, x[i] = s[i];
    sort(len);
    for (int k = 1, num = 0; k <= len; k <<= 1, num = 0) {
        for (int i = len; i >= len - k + 1; i--) y[++num] = i;
        for (int i = 1; i <= len; i++) if (sa[i] > k) y[++num] = sa[i] - k;
        sort(len), memcpy(y, x, sizeof(x)), num = x[sa[1]] = 1;
        for (int i = 2; i <= len; i++) 
            x[i] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? num : ++num;
    }
}

int st[18][N], lg[N];

inline void get(char s[], int len) {
    for (int i = 1; i <= len; i++) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= len; i++) {
        if (rk[i] == 1) continue; if (k) k--;
        int at = sa[rk[i] - 1];
        while (at + k <= len && i + k <= len && s[at + k] == s[i + k]) k++;
        height[rk[i]] = k;
    }
    for (int i = 1; i <= len; i++) st[0][i] = height[i];
    for (int i = 1; i <= 17; i++)
        for (int j = 1; j + (1 << i) - 1 <= len; j++)
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
    for (int i = 2; i <= len; i++) lg[i] = lg[i >> 1] + 1;
}

inline int LCP(int l, int r) {
    if (l == r) return 1e9;
    int len = lg[r - l + 1];
    return min(st[len][l], st[len][r - (1 << len) + 1]);
}

inline P find(int pos, int len, int n) {
    int l = 1, r = pos, L, R, mid;
    while (l <= r) {
        if (LCP(mid = (l + r) >> 1, pos) >= len) L = mid, r = mid - 1;
        else l = mid + 1;
    }
    l = pos + 1, r = n;
    while (l <= r) {
        if (LCP(pos, mid = (l + r) >> 1) >= len) R = mid, l = mid + 1;
        else r = mid - 1;
    }
    return P(L, R);
}

struct block {

int num[N], tag[SZ], belong[N], n;

inline void pre(int len) {
    n = len;
    for (int i = 1; i <= n; i++)
        belong[i] = (i + SZ - 1) / SZ; 
}

inline int query(int x) {
    return num[x] + tag[belong[x]];
}

inline void update(int l, int r) {
    int x = belong[l], y = belong[r];
    for (int i = x + 1; i < y; i++) tag[i]++;
    for (int i = l; i <= min(r, x * SZ); i++) num[i]++;
    if (x != y) for (int i = (y - 1) * SZ + 1; i <= r; i++) num[i]++;
}

} T;

int appear[N], len[N], L[N], R[N], ct[N][SZ], sum[N], id[N], fuck, A[N], ans[N];

char s[N], tmp[N]; vector<int> zjk[N];

struct tcurts {
    int id, k, w;
};

vector<tcurts> q[N];

int main() {
    int n, m; scanf("%d%d", &n, &m); int tp = 0; vector<int> wkr;
    for (int i = 1; i <= n; i++) {
        scanf("%s", tmp + 1), len[i] = strlen(tmp + 1), appear[i] = tp + 1;
        for (int j = 1; j <= len[i]; j++) s[++tp] = tmp[j];
        if (i != n) s[++tp] = '$';
        if (len[i] > SZ) wkr.push_back(i), id[i] = ++fuck;
    }
    SA(s, tp), get(s, tp), T.pre(tp);
    for (int i = 1; i <= n; i++) {
        P res = find(rk[appear[i]], len[i], tp);
        L[i] = res.first, R[i] = res.second;
    }
    for (auto t : wkr) {
        for (int i = 1; i <= tp; i++) sum[i] = 0;
        for (int i = 1; i <= len[t]; i++) sum[rk[appear[t] + i - 1]]++;
        for (int i = 1; i <= tp; i++) sum[i] += sum[i - 1];
        for (int i = 1; i <= n; i++) ct[i][id[t]] = sum[R[i]] - sum[L[i] - 1];
    }
    for (int i = 1; i <= m; i++) {
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        q[r].push_back((tcurts){ i, k, 1 }), q[l - 1].push_back((tcurts){ i, k, -1 });
    }
    for (int i = 1; i <= n; i++) {
        T.update(L[i], R[i]);
        for (auto t : wkr) A[t] += ct[i][id[t]];
        for (auto t : q[i]) {
            int k = t.k, res = A[k];
            if (!id[k]) for (int i = 1; i <= len[k]; i++) 
                res += T.query(rk[appear[k] + i - 1]);
            ans[t.id] += res * t.w;
        } 
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}
