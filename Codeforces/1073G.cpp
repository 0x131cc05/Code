#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef long long LL;

int x[N], y[N], c[N], h[N], m = 127, rk[N], sa[N], len;

void sort() {
    fill(c + 1, c + m + 1, 0);
    for (int i = 1; i <= len; i++) c[x[i]]++;
    for (int i = 1; i <= m; i++) c[i] += c[i - 1];
    for (int i = len; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
}

void SA(char s[]) {
    for (int i = 1; i <= len; i++) x[i] = s[i], y[i] = i;
    sort();
    for (int k = 1, num = 0; k <= len; k <<= 1, num = 0) {
        for (int i = len; i >= len - k + 1; i--) y[++num] = i;
        for (int i = 1; i <= len; i++) if (sa[i] > k) y[++num] = sa[i] - k;
        sort(), memcpy(y, x, sizeof(x)), num = x[sa[1]] = 1;
        for (int i = 2; i <= len; i++)
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
        if (num == len) break; m = num;
    }
}

int st[18][N], st1[18][N], lg[N], stk[N], L[N], R[N];

int Min(int a, int b) {
    return h[a] < h[b] ? a : b;
}

void get(char s[]) {
    for (int i = 1; i <= len; i++) rk[sa[i]] = i;
    for (int i = 2; i <= len; i++) lg[i] = lg[i >> 1] + 1;
    for (int i = 1, k = 0; i <= len; i++) if (rk[i] != 1) {
        if (k) k--;
        while (s[sa[rk[i] - 1] + k] == s[i + k]) k++;
        h[rk[i]] = k, st[0][rk[i]] = st1[0][rk[i]] = rk[i];
    }
    for (int i = 1; i < 18; i++)
        for (int j = 1; j + (1 << i) - 1 <= len; j++) 
            st[i][j] = Min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]), st1[i][j] = Min(st1[i - 1][j + (1 << i - 1)], st1[i - 1][j]);
    int top = 1; stk[top] = 2;
    for (int i = 3; i <= len; i++) {
        while (top && h[stk[top]] > h[i]) R[stk[top--]] = i - 1;
        stk[++top] = i;
    }
    while (top) R[stk[top--]] = len;
    stk[top = 1] = len;
    for (int i = len - 1; i >= 2; i--) {
        while (top && h[stk[top]] >= h[i]) L[stk[top--]] = i + 1;
        stk[++top] = i;
    }
    while (top) L[stk[top--]] = 2;
}

int get(int l, int r) {
    int len = lg[r - l + 1];
    return Min(st[len][l], st[len][r - (1 << len) + 1]);
}

int get1(int l, int r) {
    int len = lg[r - l + 1];
    return Min(st1[len][r - (1 << len) + 1], st1[len][l]);
}

int T[2][N];

void upd(int t, int x, int y) {
    for (; x <= len; x += x & -x) T[t][x] += y;
}

int que(int t, int x) {
    int res = 0;
    for (; x; x -= x & -x) res += T[t][x];
    return res;
}

int que(int t, int l, int r) {
    return que(t, r) - que(t, l - 1); 
}

char s[N];

int main() {
    int q; scanf("%d%d%s", &len, &q, s + 1), SA(s), get(s);
    while (q--) {
        int A, B; scanf("%d%d", &A, &B);
        vector<int> a, b, c;
        for (int i = 1, t; i <= A; i++) scanf("%d", &t), t = rk[t], a.push_back(t), c.push_back(t), upd(0, t, 1);
        for (int i = 1, t; i <= B; i++) scanf("%d", &t), t = rk[t], b.push_back(t), c.push_back(t), upd(1, t, 1);
        sort(c.begin(), c.end());
        LL res = 0;
        for (int i = 0; i + 1 < c.size(); i++) {
            int tl = c[i], tr = c[i + 1];
            if (tl == tr) { res += len - sa[tl] + 1; continue; } 
            int p = get(tl + 1, tr), l = L[get1(tl + 1, tr)], r = R[p];
            res += (LL)que(0, l - 1, p - 1) * que(1, p, r) * h[p];
            res += (LL)que(1, l - 1, p - 1) * que(0, p, r) * h[p];
        }
        for (auto t : a) upd(0, t, -1);
        for (auto t : b) upd(1, t, -1);
        printf("%lld\n", res);
    }
}

