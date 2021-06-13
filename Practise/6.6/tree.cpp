#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

typedef long long LL;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt;
    e[++ecnt] = { from, head[to] }, head[to] = ecnt;
}

int dep[N], buk[N], w[N], tmp[N];

void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    tmp[u] = buk[w[u]];
    // for (int i = 1; i <= w[u]; i++) tmp[u] += buk[i];
    buk[w[u]]++;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) 
            dfs(e[i].to, u);
    buk[w[u]]--;
}

template<class T> void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

int main() {
    freopen("tree2.in", "r", stdin);
    int n; read(n);
    for (int i = 1, a; i <= n; i++) read(w[i]);
    for (int i = 1, a, b; i < n; i++) 
        read(a), read(b), adde(a, b);
    dep[0] = -1, dfs(1, 0); vector<int> fuck;
    for (int i = 1; i <= n; i++) fuck.push_back(dep[i] - tmp[i]);
    sort(fuck.begin(), fuck.end(), [&](int a, int b) {
        return a > b;
    });
    // cout << fuck.back() << endl;
    LL tot = 0;
    ifstream fin("tree2.ans");
    LL wkr; fin >> wkr;
    for (int i = 1; i <= n; i++) {
        LL t; fin >> t; tot += fuck[i - 1];
        cout << wkr - (t + (LL)i * (n - i)) - tot << endl;
    }
}