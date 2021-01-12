#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

int num[N], n, ans[N], ans1[N];

int mx[18][N], mn[18][N], lg[N];

inline int Max(const int &a, const int &b) {
    return num[a] > num[b] ? a : b;
}

inline int Min(const int &a, const int &b) {
    return num[a] < num[b] ? a : b;
}

inline int getmx(int l, int r) {
    int len = lg[r - l + 1];
    return Max(mx[len][l], mx[len][r - (1 << len) + 1]);
}

inline int getmn(int l, int r) {
    int len = lg[r - l + 1];
    return Min(mn[len][l], mn[len][r - (1 << len) + 1]);
}

inline void preST() {
    for (int i = 1; i <= n; i++) mx[0][i] = mn[0][i] = i;
    for (int i = 1; i < 18; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            mx[i][j] = Max(mx[i - 1][j], mx[i - 1][j + (1 << i - 1)]);
            mn[i][j] = Min(mn[i - 1][j], mn[i - 1][j + (1 << i - 1)]);
        }
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
}

typedef pair<int, int> P;

P res1[N], res2[N];

inline void solve() {
    static int up[N], top1, down[N], top2, tmp[N]; 
    memset(tmp, 0, sizeof(tmp));
    set<int> s, A, B; s.insert(n + 2), A.insert(n + 2), B.insert(n + 2);
    static int fk[N], tp1, fk2[N], tp2;
    fk[0] = fk2[0] = n + 1;
    for (int i = n; i >= 1; i--) {
        while (top1 && num[up[top1]] < num[i]) {
            if (++tmp[up[top1]] == 2) s.insert(up[top1]);
            A.insert(up[top1]), top1--;
        }   
        while (top2 && num[down[top2]] > num[i]) {
            if (++tmp[down[top2]] == 2) s.insert(down[top2]);
            B.insert(down[top2]), top2--;
        }
        while (tp1 && num[fk[tp1]] <= num[i]) tp1--;
        while (tp2 && num[fk2[tp2]] >= num[i]) tp2--;
        up[++top1] = down[++top2] = fk[++tp1] = fk2[++tp2] = i;
        int pos = max(fk[tp1 - 1], fk2[tp2 - 1]);
        ans[i] = *s.upper_bound(pos); 
        ans1[i] = min(*A.upper_bound(fk[tp1 - 1]), *B.upper_bound(fk2[tp2 - 1]));
    }
    for (int i = n; i >= 1; i--) {
        res1[i] = P(i, ans[i]), res2[i] = P(i, ans1[i]);
        if (i == n) continue;
        if (res1[i + 1].second < res1[i].second) res1[i] = res1[i + 1];
        if (res2[i + 1].second < res2[i].second) res2[i] = res2[i + 1];
    }
}

int main() {
    int q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    preST(), solve();
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        if (res1[l].second <= r) {
            vector<int> ans = {res1[l].first, res1[l].second}; puts("4");
            ans.push_back(getmn(ans[0], ans[1])), ans.push_back(getmx(ans[0], ans[1])), sort(ans.begin(), ans.end());
            for (auto t : ans) printf("%d ", t);
            puts("");
        } else if (res2[l].second <= r) {
            printf("3\n%d ", res2[l].first);
            int A = getmn(res2[l].first, res2[l].second), B = getmx(res2[l].first, res2[l].second);
            printf("%d %d\n", (num[A] == num[res2[l].first] || num[A] == num[res2[l].second]) ? B : A, res2[l].second);
        } else puts("0");
    }
    return 0;
}
