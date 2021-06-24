#include <bits/stdc++.h>
using namespace std;

const int N = 12010;

typedef long long LL;

int tree[N], r, c;

void upd(int x, int y) { for (; x < N; x += x & -x) tree[x] += y; }

int que(int x) {
    if (x < 0) return 0;
    int res = 0;
    for (; x; x -= x & -x) res += tree[x];
    return res;
}

int que(int l, int r) {
//    cout << "que: " << l << ' ' << r << endl;
    return que(r) - que(l - 1);
}

char s[N / 2][N];

int L[2][N], R[2][N], lft[N];

LL solve() {
//    cout << "-------------------" << endl;
//    for (int i = 1; i <= r; i++, puts("")) 
//        for (int j = 1; j <= c; j++) putchar(s[i][j]);
    memset(L, 0, sizeof(L)), memset(R, 0, sizeof(R));
    vector<int> del[N]; LL res = 0;
    for (int i = 1, cur = 1; i <= r; i += 2, cur ^= 1) {
        memset(L[cur], 0, sizeof(L[cur])), memset(R[cur], 0, sizeof(R[cur])), memset(tree, 0, sizeof(tree));
        for (int j = 1; j <= c; j++) del[j].clear();
        for (int j = 1; j <= c; j++) if (s[i][j] == 'x') {
            lft[j] = 0;
            if (s[i][j - 1] == '-') lft[j] = lft[j - 4] + 1;
            if (i != 1) {
                if (s[i - 1][j - 1] == '\\' || s[i - 1][j - 1] == '/') L[cur][j] = L[cur ^ 1][j - 2] + 1;
                if (s[i - 1][j + 1] == '\\' || s[i - 1][j + 1] == '/') R[cur][j] = R[cur ^ 1][j + 2] + 1;
            }
            int len = min(lft[j], L[cur][j]);
            if (len) res += que(j - len * 4, j);
            for (auto t : del[j]) upd(t, -1);
            del[j].clear();
            if (R[cur][j]) {
                upd(j, 1);
                if (j + R[cur][j] * 4 < N) del[j + R[cur][j] * 4].push_back(j);
            }
        }
    }
    return res;
}

int main() {
    scanf("%d%d\n", &r, &c), r = r * 2 - 1, c *= 2;
    for (int i = 1; i <= r; i++) gets(s[i] + 1);
    LL res = solve(); 
//    cout << res << endl;
    reverse(s + 1, s + r + 1);
    res += solve();
    printf("%lld\n", res);
}
