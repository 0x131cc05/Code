#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

typedef long long LL;

int ls[N * 128], rs[N * 128], sum[N * 128], ncnt;

int update(int rt, int l, int r, int pos, int x) {
    int nw = ++ncnt; ls[nw] = ls[rt], rs[nw] = rs[rt], sum[nw] = sum[rt] + x;
    if (l == r) return nw;
    int mid = ((LL)l + r) >> 1;
    if (pos <= mid) ls[nw] = update(ls[nw], l, mid, pos, x);
    else rs[nw] = update(rs[nw], mid + 1, r, pos, x);
    return nw;
}

int query(int rt, int rt1, int l, int r, int start, int end) {
    if (!rt) return 0;
    if (end < l || start > r || start > end) return 0;
    if (start <= l && r <= end) return sum[rt] - sum[rt1];
    int mid = ((LL)l + r) >> 1, res = 0;
    if (start <= mid) res += query(ls[rt], ls[rt1], l, mid, start, end);
    if (end > mid) res += query(rs[rt], rs[rt1], mid + 1, r, start, end);
    return res;
}

int st[18][N], st1[18][N], lg[N], L[N], R[N], stk[N], rt[N], num[N], n, rt1[N];

int get(int l, int r) {
    if (l > r) return 2e9;
    int len = lg[r - l + 1];
    return min(st[len][l], st[len][r - (1 << len) + 1]);
}

vector<int> tmp[N]; int Tl = 1e9, Tr = -1e9, ok[N];

void pre() {
    for (int i = 1; i <= n; i++) st[0][i] = st1[0][i] = num[i];
    for (int i = 1; i <= 17; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) 
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
        for (int j = 1 << i; j <= n; j++)
            st1[i][j] = min(st1[i - 1][j], st1[i - 1][j - (1 << i - 1)]);
    }
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    int top = 0; stk[top = 1] = 1;
    for (int i = 2; i <= n; i++) {
        while (top && num[stk[top]] > num[i]) R[stk[top]] = i, top--;
        stk[++top] = i; 
    }
    while (top) R[stk[top--]] = n + 1;
    stk[top = 1] = n;
    for (int i = n - 1; i >= 1; i--) {
        while (top && num[stk[top]] > num[i]) L[stk[top]] = i, top--;
        stk[++top] = i;
    }

    for (int i = 1; i <= n; i++) if (L[i] >= 1 && R[i] <= n) {
        if (get(L[i] + 1, i - 1) != num[i]) ok[i] = 1;
        int tl = num[i] + max(num[L[i]], num[R[i]]), tr = num[i] * 2 - 1;
        Tl = min(Tl, tl), Tr = max(Tr, tr + 1);
    }
    for (int i = 1; i <= n; i++) {
        rt[i] = rt[i - 1], rt1[i] = rt1[i - 1];
        if (ok[i] == 1) {
            int tl = num[i] + max(num[L[i]], num[R[i]]), tr = num[i] * 2 - 1;
            rt[i] = update(rt[i], Tl, Tr, tl, 1), rt[i] = update(rt[i], Tl, Tr, tr + 1, -1);
        } 
        rt1[i] = update(rt1[i], Tl, Tr, num[i], 1);
    }
}

int k;

bool check(int l, int r, int w) {
    if ((LL)get(l, r) * 2 > w) return false;
    int vl = l - 1, vr = r + 1;
    for (int i = 17; i >= 0; i--)
        if (vl + (1 << i) <= r && st[i][vl + 1] * 2 > w) vl += 1 << i;
    for (int i = 17; i >= 0; i--)
        if (vr - (1 << i) >= l && st1[i][vr - 1] * 2 > w) vr -= 1 << i;
    vl++, vr--;
    // cout << vl << ' ' << vr << endl;
    // cout << vl << ' ' << vr << ' ' << w << ' ' << num[vl] << ' ' << num[vr] << endl;
    assert(vl <= vr);
    int ct = query(rt1[r], rt1[l - 1], Tl, Tr, Tl, w / 2);
    if (vl < vr) ct += query(rt[vr - 1], rt[vl], Tl, Tr, Tl, w);
    // cout << ct << endl;
    if ((LL)min(get(l, vl - 1), get(vr + 1, r)) + max(num[vl], num[vr]) <= w) ct++;
    return ct >= k;   
}

int main() {
    // freopen("ex_C2.in", "r", stdin);
    int q, mx = 0; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]), Tl = min(Tl, num[i]), Tr = max(Tr, num[i]);
    mx = Tr, pre();
    // cout << Tl << ' ' << Tr << endl;
    while (q--) {
        int L, R; scanf("%d%d%d", &L, &R, &k);
        int l = 0, r = mx * 2, mid, res = -1;
        while (l <= r) {
            mid = ((LL)l + r) >> 1;
            if (check(L, R, mid)) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        printf("%d\n", res);
    }
}