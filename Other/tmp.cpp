#include <bits/stdc++.h>
using namespace std;

char gc() {
    static char s[1000000], *p1 = s, *p2 = s;
    return p1 == p2 ? (p2 = (p1 = s) + fread(p1, 1, 1000000, stdin), p1 == p2 ? EOF : *p1++) : *p1++;
}

template<class T> void read(T &x) {
    x = 0; char c = gc();
    while (!isdigit(c)) c = gc();
    while (isdigit(c)) x = x * 10 + c - '0', c = gc();
}

template<class T, typename... Tail> void read(T &x, Tail&... tail) {
   read(x), read(tail...);
}

void print(int x) {
    if (x >= 10) print(x / 10);
    putchar(x % 10 + '0');
}

const int N = 5000010;

int dfsn, dfn[N], ed[N], n; vector<int> G[N];

void dfs(int u) {
    dfn[u] = ++dfsn;
    for (auto v : G[u]) dfs(v);
    ed[u] = dfsn;
}

int stk[N], top;

int main() {
    read(n);
    for (int i = 2, a; i <= n; i++) read(a), G[a].push_back(i);
    dfs(1);
    for (int i = 1; i <= n; i++) {
        while (top && (dfn[i] < dfn[stk[top]] || dfn[i] > ed[stk[top]])) top--;
        stk[++top] = i, print(top), puts("");
    }
}
