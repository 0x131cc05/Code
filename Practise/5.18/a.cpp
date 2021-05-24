#include <bits/stdc++.h>
using namespace std;

const int N = 300010;

int num[N], op[N], l[N], r[N];

typedef long long LL;

struct item {
    int r, k, id;
};

vector<item> q[N];

LL tree[N]; int n;

void upd(int x, int y) {
    for (; x <= n; x += x & -x) tree[x] += y;
}

LL que(int x) {
    LL res = 0;
    for (; x; x -= x & -x) res += tree[x];
    return res; 
} 

int L[N], stk[N], suf[N], lg[N], st[19][N]; LL ans[N];

int get(int l, int r) {
    int len = lg[r - l + 1];
    return max(st[len][l], st[len][r - (1 << len) + 1]);
}

int main() {
    freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
    int m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]), st[0][i] = num[i];
    for (int i = 1; i <= 18; i++) 
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    for (int i = n; i >= 1; i--) suf[i] = max(suf[i], suf[i + 1]);
    for (int i = 1; i <= m; i++) 
        scanf("%d%d%d", &op[i], &l[i], &r[i]);
    if (m <= 2000) {
        for (int i = 1; i <= m; i++) {
            if (op[i] == 1) {
                for (int j = l[i]; j < r[i]; j++)
                    num[j] = max(num[j], num[j + 1]);
            } else {
                int mx = 0; LL res = 0;
                for (int j = l[i]; j <= r[i]; j++) 
                    if (num[j] > mx) res += num[j], mx = num[j];
                printf("%lld\n", res);
            }
        }
        return 0;
    } 
    int ct = 0;
    for (int i = 1; i <= m; i++) {
        if (op[i] == 1) { ct++; continue; }
        ans[i] = get(l[i], min(n, l[i] + ct));
        int tl = l[i] + ct + 1, tr = r[i] + ct;
        tr = min(tr, n);
        if (tl > tr) { continue; }
        q[tr].push_back({ l[i], 1, i }), q[tl - 1].push_back({ l[i], -1, i });
    }
    int top = 1; stk[top] = n;
    for (int i = n - 1; i >= 1; i--) {
        while (top && num[i] > num[stk[top]]) L[stk[top--]] = i + 1;
        stk[++top] = i;
    }
    while (top) L[stk[top--]] = 1;
    for (int i = 1; i <= n; i++) {
        upd(L[i], num[i]);
        for (auto t : q[i]) ans[t.id] += t.k * que(t.r);
    }
    for (int i = 1; i <= m; i++) 
        if (op[i] == 2) printf("%lld\n", ans[i]);
}