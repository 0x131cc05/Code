#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int fa[51];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

struct SetAndSet {
    LL countandset(vector<int> A) {
        int n = A.size();
        LL all = (1ll << n) - 1;
        LL ans = 0;
        for (int i = 0; i < n; i++) fa[i] = i;
        function<void(int, int)> dfs = [&](int x, int ct) {
            if (x == 20) {
                LL w = 1;
                for (int i = 0; i < n; i++) if (fa[i] == i) w *= 2;
                w -= 2;
                if (ct & 1) ans -= w;
                else ans += w;
                return;
            }
            dfs(x + 1, ct);
            vector<int> lst(n);
            for (int i = 0; i < n; i++) lst[i] = fa[i];
            int hh = -1;
            for (int i = 0; i < n; i++) if (!(A[i] & (1 << x))) {
                if (hh != -1) fa[find(hh)] = find(i);
                hh = i;
            }
            if (hh == -1) return;
            dfs(x + 1, ct + 1);
            for (int i = 0; i < n; i++) fa[i] = lst[i];
        };
        dfs(0, 0);
        return ans;
    }
};
