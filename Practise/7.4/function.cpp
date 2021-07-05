#include <bits/stdc++.h>
using namespace std;

const int N = 50010;

typedef long long LL;

int x[N], y[N], c[N], sa[N], rk[N], height[N], m, n;

void sort() {
    for (int i = 1; i <= m; i++) c[i] = 0;
    for (int i = 1; i <= n; i++) c[x[i]]++;
    for (int i = 1; i <= m; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
}

void build(string s) { // s[0] = ' '
    n = (int)s.size() - 1, m = 127;
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

void getHeight(string s) {
    for (int i = 1; i <= n; i++) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i++) if (rk[i] != 1) {
        k = max(k - 1, 0);
        int lst = sa[rk[i] - 1];
        while (lst + k <= n && i + k <= n && s[lst + k] == s[i + k]) k++;
        height[rk[i]] = k;
    }
}

int mn[19][N], lg[N];

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

int main() {
    freopen("function.in", "r", stdin), freopen("function.out", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    string s; cin >> s; s.insert(s.begin(), ' ');
    build(s), getHeight(s), buildRMQ();
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        LL res = r - l + 1;
        int t = rk[l];
        for (int i = l + 1; i <= r; i++) if (s[i] == s[l])
            res += min(r - i + 1, LCP(t, rk[i]));
        cout << res << endl;
    }
}