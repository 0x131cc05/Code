#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int mod = 998244353;

int id[N], rk[N], ok[N];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) id[i] = i;
    for (int i = 1; i <= m; i++) {
        int op, u, v; scanf("%d%d%d", &op, &u, &v);
        if (op == 1) reverse(id + u, id + v + 1);
        else {
            static int tmp[N]; int ct = 0;
            for (int i = u; i <= v; i++) tmp[++ct] = id[i];
            for (int i = 1; i < u; i++) tmp[++ct] = id[i];
            for (int i = 1; i <= ct; i++) id[i] = tmp[i];
        } 
    }
    for (int i = 1; i <= n; i++) rk[id[i]] = i;
    int res = 1;
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(mx, i);
        if (mx <= rk[i]) ok[i] = 1;
    }
    int ct = 0;
    for (int i = 1; i < n; i++) {
        if (rk[id[i] + 1] < rk[id[i + 1] + 1]) {
            res = 2 * res % mod, ct++; 
        }
    }
    printf("%d\n", res);
}