#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

typedef pair<int, int> P;

int rk[N * 2], first, n, R;

P case1(int pos) {
    // 最终会进入循环，循环节为 n
    if (first == 1) return P(1, 0);
    static int ct[3][N * 4]; memset(ct, 0, sizeof(ct));
    int touch = 0;
    for (int i = 1; i < n * 2; i++) {
        int t = i < pos ? i : i + 1;
        int type = (rk[i] < first) * 2;
        ct[type][(t + 1) / 2]++;
    }
    ct[1][(pos + 1) / 2]++;
    int tot = n;
    static int buk[3]; memset(buk, 0, sizeof(buk));
    for (int i = 1; i <= n * 3; i++) {
        if (i >= n * 2 && ct[1][1]) {
            int remain = R - (i - 1);
            touch += (remain + n - 1) / n;
            return P(n - (remain + n - 1) % n, touch);
        }
        int win = 0;
        for (int t = 2; t >= 0; t--) if (ct[t][1]) {
            win = t; break;
        }
        int lose = ct[1][1] + ct[2][1] * 2 - win;
        if (lose == 1) touch++;
        ct[lose][++tot]++, ct[lose][1]--;
        for (int t = 0; t < 3; t++) buk[t] += ct[t][i + 1];
        for (int t = 2; t >= 0; t--) if (buk[t]) {
            ct[t][1]++, buk[t]--; break;
        }
    }
    assert(0);
}

P case2(int pos) {
    // 最终会卡在某个大于 1 的位置
    static int ct[2][N]; memset(ct, 0, sizeof(ct));
    for (int i = 1; i < 2 * n; i++) {
        int t = i < pos ? i : i + 1;
        if (rk[i] > first) ct[0][(t + 1) / 2]++;
    }
    ct[1][(pos + 1) / 2]++;
    int touch = 0;
    int nw[2] = {0, 0}; int cur = 1, all = 0;
    while (233) {
        int tmp[2] = { nw[0] + ct[0][cur], nw[1] + ct[1][cur] };
        if (tmp[0] + tmp[1] >= 2) { // 有一个数需要留在当前位置
            int mx = tmp[1] ? 1 : 0, mn = tmp[0] ? 0 : 1;
            ct[0][cur] = ct[1][cur] = 0, nw[0] = tmp[0], nw[1] = tmp[1];
            if (cur != 1) nw[mn]--, ct[mn][cur]++;
            else nw[mx]--, ct[mx][cur]++;
        } else { // 如果当前位置为 1，则当前位会被换走
            if (cur != 1) ct[0][cur] = tmp[0], ct[1][cur] = tmp[1], nw[0] = nw[1] = 0;
            else ct[0][cur] = ct[1][cur] = 0, nw[0] = tmp[0], nw[1] = tmp[1];
        }
        if (cur == 1 && nw[1]) touch++;
        cur = cur == 1 ? n : cur - 1;
        if (cur == 1 && ++all == 3) 
            break;
    }
    for (int i = 2; i <= n; i++) if (ct[1][i])
        return P(i, touch);
    assert(0);
}

P getPos(int pos) {
    if (first <= n + 1) return case1(pos);
    return case2(pos);
}

P find(int l) {
    P res = getPos(l * 2);
    int r = n, mid, ok;
    while (l <= r) {
        mid = (l + r) >> 1;
        P t = getPos(mid * 2);
        if (res.second == t.second) l = mid + 1, ok = mid;
        else r = mid - 1;
    }
    return P(res.first, ok);
}

int main() {
    scanf("%d%d%d", &n, &R, &first);
    for (int i = 1; i < n * 2; i++) scanf("%d", &rk[i]);
    P ans(1e9, 0); int pos = 1;
    while (pos <= n) {
        P t = find(pos); 
        if (t.first <= ans.first) ans = P(t.first, pos);
        pos = t.second + 1;
    }
    int l = ans.second, r = n, mid, res = l;
    while (l <= r) {
        mid = (l + r) >> 1;
        P t = getPos(mid * 2);
        if (t.first == ans.first) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%d\n", res);
}