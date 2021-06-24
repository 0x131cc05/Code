#include <bits/stdc++.h>
using namespace std;

const int N = 50010;

typedef long long LL;

int tree[N], tot, tree1[N];

void upd(int x, int y) {
    for (; x; x -= x & -x) tree[x] = min(tree[x], y);
}

void upd1(int x, int y) {
    for (; x; x -= x & -x) tree1[x] = max(tree1[x], y);
}

int que(int x) {
    int res = 1e9;
    for (; x <= tot; x += x & -x) res = min(res, tree[x]);
    return res;
}

int que1(int x) {
    int res = -1e9;
    for (; x <= tot; x += x & -x) res = max(res, tree1[x]);
    return res;
}

int pre[N], pos[N];

int main() {
    freopen("divide.in", "r", stdin), freopen("divide.out", "w", stdout);
    vector<int> val;
    int n, k; scanf("%d%d", &n, &k);
    val.push_back(0);
    int l = 0, r = 0, mid, res = 2e9;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &pre[i]);
        if (pre[i] < 0) l += pre[i];
        else r += pre[i];
        pre[i] += pre[i - 1], val.push_back(pre[i]);
    }
    sort(val.begin(), val.end()), val.resize(unique(val.begin(), val.end()) - val.begin());
    tot = val.size();
    auto find = [&](LL x) {
        return lower_bound(val.begin(), val.end(), x) - val.begin() + 1;
    };
    for (int i = 1; i <= n; i++) pos[i] = find(pre[i]);
    while (l <= r) {
        mid = (l + r) >> 1;
        memset(tree, 0x3f, sizeof(tree)), memset(tree1, -0x3f, sizeof(tree1));
        upd(find(0), 0), upd1(find(0), 0);
        for (int i = 1; i <= n; i++) {
            int a = pos[i], b = find((LL)pre[i] - mid);
            upd(a, que(b) + 1), upd1(a, que1(b) + 1);
        }
        int lst = pos[n];
        if (que(lst) <= k && que1(lst) >= k) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%d\n", res);
}

