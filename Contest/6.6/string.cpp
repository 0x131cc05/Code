#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast")

const int N = 1000010;

int fa[20][N], sz[20][N];

int find(int x, int layer) {
    return fa[layer][x] == x ? x : fa[layer][x] = find(fa[layer][x], layer); 
}

inline void merge(int x, int y, int layer) {
    int fy = find(y, layer), fx = find(x, layer);
    if (fy != fx) {
        if (sz[fy] > sz[fx]) swap(fy, fx);
        fa[layer][fy] = fx;
//        if (layer) merge(x, y, layer - 1), merge(x + (1 << layer - 1), y + (1 << layer - 1), layer - 1);
    }
}

char s[N]; int res[N];

inline char gc() {
    static char buf[1000000], *p1, *p2;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

template<class T> inline void read(T &x) {
    x = 0; char c = gc();
    while (c < '0' || c > '9') c = gc();
    while ('0' <= c && c <= '9') x = x * 10 + c -'0', c = gc();
}

int lg[N];

int main() {
    scanf("%s", s + 1); int n = strlen(s + 1), m; scanf("%d", &m);
    for (int layer = 0; layer <= 19; layer++)
        for (int i = 1; i <= n; i++) fa[layer][i] = i;
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= m; i++) {
        int a, b, l; read(a), read(b), read(l);
        merge(a, b, lg[l]), merge(a + l - (1 << lg[l]), b + l - (1 << lg[l]), lg[l]);
    }
    for (int i = 19; i >= 1; i--) 
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            int f = find(j, i);
            if (f != j) merge(j, f, i - 1), merge(j + (1 << i - 1), f + (1 << i - 1), i - 1);
        }
    for (int i = 1; i <= n; i++) if (s[i] != '?')
        res[find(i, 0)] = res[i] = s[i] - '0';
    for (int i = 1; i <= n; i++) if (s[i] == '?') res[i] = res[find(i, 0)];
    for (int i = 1; i <= n; i++) printf("%d", res[i]);
}
