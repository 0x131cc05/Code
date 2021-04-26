#include <bits/stdc++.h>
using namespace std;

map<int, int> mp;

const int N = 200010;

struct edge {
    int to, next;
} e[N * 2];

int head[N], ecnt, ind[N];

void adde(int from, int to) {
    e[++ecnt] = { to, head[from] }, head[from] = ecnt, ind[to]++, ind[from]--;
}

vector<int> res;

int vis[N];

void dfs(int u) {
    for (int &i = head[u]; i; i = e[i].next) if (!vis[i]) 
        vis[i] = 1, dfs(e[i].to);
    res.push_back(u);
}

int fa[N], ncnt;

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

char s[N][5], A[N], B[N];

int id(char a, char b) {
    int t = (int)a * 255 + b;
    if (mp.count(t)) return mp[t];
    ncnt++, A[ncnt] = a, B[ncnt] = b;
    return mp[t] = ncnt;
}

int from[N], to[N];

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s[i] + 1);
        from[i] = id(s[i][1], s[i][2]), to[i] = id(s[i][2], s[i][3]), adde(to[i], from[i]);
    }
    for (int i = 1; i <= ncnt; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) fa[find(from[i])] = find(to[i]);
    int ct = 0;
    for (int i = 1; i <= ncnt; i++) if (i == fa[i]) ct++;
    if (ct > 1) return puts("NO"), 0;
    int a = 0, b = 0;
    for (int i = 1; i <= ncnt; i++) {
        if (ind[i] == 1 && !a) a = i, ind[i] = 0;
        if (ind[i] == -1 && !b) b = i, ind[i] = 0;
    }
    for (int i = 1; i <= ncnt; i++) if (ind[i]) return puts("NO"), 0;
    dfs(max(1, b));
    puts("YES");
    putchar(A[res[0]]);
    for (auto t : res) putchar(B[t]);
}