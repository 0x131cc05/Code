#include <bits/stdc++.h>
using namespace std;

const int N = 10;

int num[N], buk[N], n, all, sa[N], id[N];

bool check(int i, int j) {
    int len = min(n - i + 1, n - j + 1);
    for (int t = 1; t <= len; t++) {
        if (num[i + t - 1] != num[j + t - 1]) return num[i + t - 1] < num[j + t - 1];
    }
    return i > j;
}

bool check() {
    for (int i = 1; i < n; i++) {
        if (!check(sa[i], sa[i + 1])) return false;
    }
    return true;
}

int res = 0;

void dfs(int cur, int mx) {
    if (cur == n + 1) {
        if (mx == all) {
            if (check()) {
                res++;
                // for (int i = 1; i <= n; i++) printf("%d ", num[i]);
                // puts("");
            }
        }
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (++buk[i] == 1) all++;
        num[cur] = i, dfs(cur + 1, max(mx, i));
        if (--buk[i] == 0) all--;
    }
}

int main() {
    int m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) sa[i] = i;
    for (int i = 1; i <= m; i++) {
        int op, u, v; scanf("%d%d%d", &op, &u, &v);
        if (op == 1) reverse(sa + u, sa + v + 1);
        else {
            static int tmp[N]; int ct = 0;
            for (int i = u; i <= v; i++) tmp[++ct] = sa[i];
            for (int i = 1; i < u; i++) tmp[++ct] = sa[i];
            for (int i = 1; i <= ct; i++) sa[i] = tmp[i];
        } 
    }
    for (int i = 1; i <= n; i++) id[sa[i]] = i;
    dfs(1, 0);
    printf("%d\n", res);
    
}