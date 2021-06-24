#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt, ind[N];

inline void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt;
    ind[from]++, ind[to]++;
}

int check(int u, int rt, int f) {
    if (u == rt) return 1;
    if (ind[u] == 4) return 0;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f && check(e[i].to, rt, u)) return 1;
    return 0;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1, a, b; i <= m; i++)
        scanf("%d%d", &a, &b), adde(a, b);
    for (int i = 1; i <= n; i++) if (ind[i] & 1) return puts("No"), 0;
    int A = 0, B = 0, ct = 0;
    for (int i = 1; i <= n; i++) {
        if (ind[i] > 4) return puts("Yes"), 0;
        if (ind[i] == 4) ct++, A ? B = i : A = i;
    } 
    if (ct < 2) return puts("No"), 0;
    if (ct > 2) return puts("Yes"), 0;
    int ans = 0;
    for (int i = head[A]; i; i = e[i].next)
        ans += check(e[i].to, A, A);
    for (int i = head[B]; i; i = e[i].next)
        ans += check(e[i].to, B, B);
    puts(ans >= 2 ? "Yes" : "No");
}
