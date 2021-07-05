#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef long long LL;

int x[N], y[N], c[N], sa[N], rk[N], height[N], m, n;

char s[N];

void sort() {
    for (int i = 1; i <= m; i++) c[i] = 0;
    for (int i = 1; i <= n; i++) c[x[i]]++;
    for (int i = 1; i <= m; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
}

void build() { // s[0] = ' '
    m = 127;
    for (int i = 1; i <= n; i++) 
        x[i] = s[i], y[i] = i;
    sort();
    for (int k = 1, num = 0; k <= n; k <<= 1) {
        for (int i = n; i >= n - k + 1; i--) y[++num] = i;
        for (int i = 1; i <= n; i++) if (sa[i] > k)
            y[++num] = sa[i] - k;
        sort(), memcpy(y, x, sizeof(x)), num = x[sa[1]] = 1;
        for (int i = 2; i <= n; i++) 
            x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? num : ++num;
        if (n == num) break;
        m = num, num = 0;
    }
}

void getHeight() {
    for (int i = 1; i <= n; i++) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i++) if (rk[i] != 1) {
        k = max(k - 1, 0);
        int lst = sa[rk[i] - 1];
        while (lst + k <= n && i + k <= n && s[lst + k] == s[i + k]) k++;
        height[rk[i]] = k;
    }
}

int mn[19][N], lg[N], R[N], nxt[26][N];

void buildRMQ() {
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    for (int i = 2; i <= n; i++) mn[0][i] = height[i];
    for (int i = 1; i <= 18; i++)
        for (int j = 2; j + (1 << i) - 1 <= n; j++)
            mn[i][j] = min(mn[i - 1][j], mn[i - 1][j + (1 << i - 1)]);
}

int LCP(int a, int b) {
    if (a == b) return n;
    if (a > b) swap(a, b);
    int len = lg[b - a];
    return min(mn[len][a + 1], mn[len][b - (1 << len) + 1]);
}

LL calc(int l, int r) {
    return (LL)(l + r) * (r - l + 1) / 2;
}

int main() {
    freopen("function.in", "r", stdin), freopen("function.out", "w", stdout);
    scanf("%s", s + 1), n = strlen(s + 1);
    build(), getHeight(), buildRMQ();
    R[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        if (s[i] == s[i + 1]) R[i] = R[i + 1] + 1;
        else R[i] = 1;
    }
    for (int i = 0; i < 26; i++) nxt[i][n + 1] = n + 1;
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < 26; j++) nxt[j][i] = nxt[j][i + 1];
        nxt[s[i] - 'a'][i] = i;
    }
    int q; scanf("%d", &q);
    while (q--) {
        int l, r; cin >> l >> r;
        if (l + R[l] - 1 >= r) {
            int len = r - l + 1;
            printf("%lld\n", (LL)len * (len + 1) / 2);
        } else {
            LL res = r - l + 1;
            LL tmp = R[l];
            res += tmp * (tmp - 1) / 2;
            int c = s[l] - 'a', t = R[l];
            for (int i = nxt[c][l + t]; i <= r; i = nxt[c][i + 1]) {
                if (min(R[i], t) >= r - i + 1) {
                    res += (LL)(r - i + 1) * (r - i + 2) / 2;
                    break;
                }
                if (R[i] != t) {
                    if (R[i] < t) {
                        res += (LL)R[i] * (R[i] + 1) / 2;
                        i = i + R[i] - 1;
                    } else {
                        if (i + R[i] - 1 >= r) {
                            int remain = r - i + 1;
                            if (remain >= t) res += (LL)t * (remain - t), remain = t;
                            res += (LL)remain * (remain + 1) / 2;
                            break;
                        }
                        res += (LL)t * (R[i] - t);
                        i = i + R[i] - t - 1;
                    }
                    continue;
                }
                res += min(r - i + 1, LCP(rk[l], rk[i]));
            }
            printf("%lld\n", res);
        }
    }
}