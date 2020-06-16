#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;

char A[N], B[N]; int n, m;

struct WEN {

int a, b, v;

bool operator < (const WEN &y) const {
    int A = a < b ? n + m - a : b, B = y.a < y.b ? n + m - y.a : y.b;
    return A < B;
}

} nw[N];

inline int calc(WEN a) {
    return a.a < a.b ? n + m - a.a : a.b;
}

inline WEN merge(WEN a, WEN b) {
    int t = max(a.a, b.a - a.b + a.a);
    return (WEN){ t, b.b + a.b - a.a - b.a + t, 0 };
}

int fa[N]; 

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

vector<int> buk[N];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%s%s", &n, &m, A + 1, B + 1), nw[0] = (WEN){ 0, 0, 0 };
        for (int i = 1; i <= n; i++) 
            nw[i] = (WEN){ A[i] == ')', A[i] == '(', 0 };
        for (int i = 1; i <= m; i++)
            nw[i + n] = (WEN){ B[i] == ')',  B[i] == '(', 0 };
        for (int i = 1; i <= n + m; i++) fa[i] = i;
        for (int i = 1; i <= n + m; i++) nw[i].v = calc(nw[i]), buk[nw[i].v].push_back(i);
        for (int i = n + m; i >= 0; i--) {
            while (buk[i].size()) {
                int t = buk[i].back(); buk[i].pop_back();
                if (i != nw[t].v) continue;
                int lst = find(t == n + 1 ? 0 : t - 1), tmp = nw[lst].v; fa[t] = lst;
                nw[lst] = merge(nw[lst], nw[t]), nw[lst].v = calc(nw[lst]);
                if (lst && tmp != nw[lst].v) buk[nw[lst].v].push_back(lst);
            }
        }
        printf("%d\n", nw[0].a + nw[0].b);
    }
}
