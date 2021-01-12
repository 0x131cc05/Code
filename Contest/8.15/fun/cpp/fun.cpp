#include "fun.h"

#include <vector>
#include <iostream>

using namespace std;

const int N = 100010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt;

void adde(int from, int to) {
    e[++ecnt] = (edge){ to, head[from] }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to] }, head[to] = ecnt; 
}

int mark[N];

int p, t;

void dfs(int u, int f, int d) {
    if (mark[u]) return;
    if (d >= t) {
        t = d, p = u;
    }
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) dfs(e[i].to, u, d + 1);
}

vector<int> createFunTour(int n, int Q) {
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            if (hoursRequired(i - 1, j - 1) == 1)
                adde(i, j);
        }
    dfs(1, 0, 0); vector<int> res; res.push_back(p - 1);
    for (int i = 1; i < n; i++) {
        int u = res.back() + 1;
        p = t = 0, dfs(u, 0, 0), mark[u] = 1, res.push_back(p - 1);
    }
    return res;
}
