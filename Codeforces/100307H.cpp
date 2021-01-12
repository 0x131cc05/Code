#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

int st[18][N], lg[N], num[N], pre[N], p[32];

map<int, vector<int>> mp;

int count(int x, int l, int r) {
    return upper_bound(mp[x].begin(), mp[x].end(), r) - lower_bound(mp[x].begin(), mp[x].end(), l);
}

int get(int l, int r) {
    int len = lg[r - l + 1];
    return st[len][l] & st[len][r - (1 << len) + 1];
}

int main() {
    freopen("hack.in", "r", stdin), freopen("hack.out", "w", stdout);
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]), st[0][i] = num[i], pre[i] = num[i] ^ pre[i - 1];
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= 17; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st[i][j] = st[i - 1][j] & st[i - 1][j + (1 << i - 1)];
    for (int i = 1; i <= n; i++) mp[pre[i]].push_back(i);
    LL res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 31; j++) {
            p[j] = max(p[j], i - 1);
            while (p[j] < n && (get(i, p[j] + 1) & (1 << j))) p[j]++;
        }
        vector<int> tmp;
        for (int j = 0; j < 31; j++) tmp.push_back(p[j]);
        tmp.push_back(n), sort(tmp.begin(), tmp.end());
        for (int lst = i, t = 0; t < tmp.size(); t++) {
            if (lst > tmp[t]) continue;
            int hh = get(i, tmp[t]);
            res += count(hh ^ pre[i - 1], lst, tmp[t]), lst = tmp[t] + 1;
        }
    }
    printf("%lld\n", res);
}