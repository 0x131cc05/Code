#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

typedef long long LL;

struct edge {
    int to, next, w;
} e[N * 2], e2[N * 2];

int head[N], ecnt;

void adde(int from, int to, int w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], w }, head[to] = ecnt;
}

LL mx; int pos, fuck[N], mn, fa[N], dep;

void find(int u, int f, int remain, int mn) {
    bool flag = true;
    if (remain <= 0 || !mn) return;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) 
            flag = false, find(e[i].to, u, remain - 1, min(mn, e[i].w)), fuck[e[i].to] = i;
    if (flag) {
        LL tmp = (LL)mn * remain;
        if (remain > dep || (remain == dep && tmp > mx)) 
            mx = tmp, pos = u, ::mn = mn, dep = remain;
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n, k; scanf("%d%d", &n, &k), ecnt = 0;
        for (int i = 1; i <= n; i++) head[i] = 0;
        static int A[N], B[N];
        for (int i = 2; i <= n; i++) scanf("%d", &A[i]);
        for (int i = 2; i <= n; i++) scanf("%d", &B[i]), adde(A[i], i, B[i]);
        for (int i = 1; i <= ecnt; i++) e2[i] = e[i];
        int l = 1, r = 1e9, mid, ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1; LL res = 0; 
            for (int i = 1; i <= ecnt; i++) e[i] = e2[i];
            while (233) {
                dep = mx = 0, find(1, 0, mid + 1, 1e9);
                // cout << "find: " << pos << ' ' << mx << endl;
                if (!mx) break;
                res += mx;
                if (res >= k) break;
                int nw = pos;
                while (nw != 1) 
                    e[fuck[nw]].w -= mn, nw = A[nw];
            }
            // cout << res << endl;
            if (res >= k) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        printf("%d\n", ans);
    }
}