#include <bits/stdc++.h>
using namespace std;

const int N = 600010;

int ind[N], all[N], a[N * 2], b[N * 2], id[N * 2], ans[N * 2];

int main() {
    srand((long long)new char + time(0));
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &a[i], &b[i]), id[i] = i;
    }
    int res = 0;
    while (clock() <= 1800) {
        static int nw[N * 2];
        for (int i = 1; i <= m; i++) {
            int a = ::a[id[i]], b = ::b[id[i]];
            if (((ind[a] ^ 1) + (ind[b] ^ 1)) >= ind[a] + ind[b] + 2) ind[a] ^= 1, ind[b] ^= 1, nw[id[i]] = 1;
            else nw[id[i]] = 0;
        }
        int ct = 0;
        for (int i = 1; i <= n; i++) ct += ind[i], ind[i] = 0;
        if (ct > res) {
            res = ct;
            for (int i = 1; i <= m; i++) ans[i] = nw[i];
        }
        else if (ct == res) {
            // cout << ct << endl;
            // for (int i = 1; i <= m; i++) cout << nw[i] << ' ';
            // cout << endl;
            // for (int i = 1; i <= m; i++) cout << id[i] << ' ';
            // cout << endl;
            bool flag = true;
            for (int i = 1; i <= m; i++) if (ans[i] != nw[i]) {
                if (nw[i] < ans[i]) flag = false; 
                break;
            }
            if (flag) for (int i = 1; i <= m; i++) ans[i] = nw[i];
        }
        next_permutation(id + 1, id + m + 1);
    }
    // cout << res << endl;
    for (int i = 1; i <= m; i++) printf("%d", ans[i]);
}
