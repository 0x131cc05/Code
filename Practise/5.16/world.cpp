#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

int fa[N], sz[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}



int main() {
    int n, m; scanf("%d%d", &n, &m);
    
    for (int i = 1; i <= m; i++) {
        int x, y, a, b; scanf("%d%d%d%d", &x, &y, &a, &b);
    }
}