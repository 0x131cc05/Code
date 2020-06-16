#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

int fa[21][N];

int find(int x, int layer) {
    return fa[layer][x] == x ? x : fa[layer][x] = find(fa[layer][x], layer); 
}

void merge(int x, int y, int layer) {
    int fx = find(x, layer), fy = find(y, layer);
    if (fx != fy) {
        fa[layer][fy] = fx;
        if (layer) merge(x, y, layer - 1), merge(x + (1 << layer - 1), y + (1 << layer - 1), layer - 1);
    }
}

char s[N]; int res[N];

template<class T> inline void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c -'0', c = getchar();
}

int main() {
    scanf("%s", s + 1); int n = strlen(s + 1), m; scanf("%d", &m);
    for (int layer = 0; layer <= 20; layer++)
        for (int i = 1; i <= n; i++) fa[layer][i] = i;
    for (int i = 1; i <= m; i++) {
        int a, b, l; read(a), read(b), read(l);
        if (a > b) swap(a, b);
        for (int i = 20; i >= 0; i--)
            if (l & (1 << i)) 
                merge(a, b, i), a += 1 << i, b += 1 << i;
    }
    for (int i = 1; i <= n; i++) if (s[i] != '?')
        res[find(i, 0)] = s[i] - '0';
    for (int i = 1; i <= n; i++) res[i] = res[find(i, 0)];
    for (int i = 1; i <= n; i++) printf("%d", res[i]);
}
