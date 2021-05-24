#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

typedef pair<int, int> P;
typedef long long LL;

struct edge {
    int to, next, w;
} e[N * 2];

int head[N], ecnt = 1;

void adde(int from, int to, int w) {
    e[++ecnt] = { to, head[from], w }, head[from] = ecnt;
}

int A, B, n;

void dfs1(int u, int f) {
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            if (e[i].to <= n) A += e[i].w;
            else B += e[i].w;
            dfs1(e[i].to, u); 
        }
}

vector<P> tmp;

void dfs2(int u, int f, int wA, int wB) {
    tmp.push_back(P(wA, wB));
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            int tA = 0, tB = 0;
            if (u <= n) tA += e[i ^ 1].w; else tB += e[i ^ 1].w;
            if (e[i].to <= n) tA -= e[i].w; else tB -= e[i].w;
            dfs2(e[i].to, u, wA + tA, wB + tB);
        }
}

int fa[N], sz[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int from[N], to[N], w1[N], w2[N], fk[N], cir[N], stk[N];

int nwA[N], nwB[N];

struct item {
    int A, B, id; double k;
    bool operator < (const item &b) const {
        return k < b.k;
    }
};

vector<item> wkr;

void process(vector<P> tmp, int id) { // y = A + kB
    sort(tmp.begin(), tmp.end(), [](P a, P b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
    auto chk = [&](int a, int b, int c) {
        return (double)(tmp[c].first - tmp[b].first) / (tmp[b].second - tmp[c].second) <= (double)(tmp[b].first - tmp[a].first) / (tmp[a].second - tmp[b].second);
    };
    int top = 1; stk[top = 1] = 0;
    for (int i = 1; i < tmp.size(); i++) {
        if (tmp[i].second == tmp[i - 1].second) continue;
        while (top >= 2 && chk(stk[top - 1], stk[top], i)) top--;
        stk[++top] = i;
    }
    nwA[id] = tmp[stk[1]].first, nwB[id] = tmp[stk[1]].second;
    for (int i = 2; i <= top; i++) {
        double k = (tmp[stk[i]].first - tmp[stk[i - 1]].first) / (double)(tmp[stk[i - 1]].second - tmp[stk[i]].second);
        wkr.push_back({ tmp[stk[i]].first, tmp[stk[i]].second, id, k });
    }
}

int main() {
    freopen("world.in", "r", stdin), freopen("world.out", "w", stdout);
    int m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n * 2; i++) sz[i] = 1, fa[i] = i;
    for (int i = 1; i <= m; i++) {
        int x, y, a, b; scanf("%d%d%d%d", &x, &y, &a, &b), y += n;
        from[i] = x, to[i] = y, w1[i] = a, w2[i] = b;
        int fx = find(x), fy = find(y);
        if (fx == fy) fk[i] = 1;
        else fa[fx] = fy, sz[fy] += sz[fx], adde(x, y, b), adde(y, x, a);
    }
    for (int i = 1; i <= m; i++) if (fk[i]) {
        int u = from[i], v = to[i];
        cir[find(u)] = 1;
        vector<P> tmp;
        A = 0, B = 0, dfs1(u, 0);
        if (u <= n) tmp.push_back(P(A + w1[i], B)); else tmp.push_back(P(A, B + w1[i]));
        A = 0, B = 0, dfs1(v, 0);
        if (v <= n) tmp.push_back(P(A + w2[i], B)); else tmp.push_back(P(A, B + w2[i]));
        process(tmp, find(u));
    }
    for (int i = 1; i <= n * 2; i++) if (fa[i] == i && !cir[i]) {
        A = 0, B = 0, dfs1(i, 0), tmp.clear(), dfs2(i, 0, A, B);
        process(tmp, i);
    }
    sort(wkr.begin(), wkr.end());
    LL sumA = 0, sumB = 0, res = 1e18;
    for (int i = 1; i <= n * 2; i++) sumA += nwA[i], sumB += nwB[i];
    res = min(res, sumA * sumB);
    for (int i = 0; i < wkr.size(); i++) {
        int a = wkr[i].A, b = wkr[i].B, id = wkr[i].id;
        sumA -= nwA[id], sumB -= nwB[id], nwA[id] = a, nwB[id] = b;
        sumA += nwA[id], sumB += nwB[id], res = min(res, sumA * sumB);
    }
    printf("%lld\n", res);
}
