#include <bits/stdc++.h>
using namespace std;

const int N = 2510;
const double eps = 1e-9;

struct edge {
    int to, next; double w;
} e[N * 10];

int cur[N], head[N], ecnt;

void adde(int from, int to, double w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], 0 }, head[to] = ecnt;
}

int dep[N];

bool BFS(int s, int t) {
    memset(dep, -1, sizeof(dep)), dep[s] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next)
            if (e[i].w > eps && dep[e[i].to] == -1) {
                dep[e[i].to] = dep[u] + 1, q.push(e[i].to);
                if (e[i].to == t) return true;
            }
    }
    return false;
}

double DFS(int u, double f, int t) {
    if (u == t || f <= eps) return f;
    double tmp = 0, res = 0;
    for (int &i = cur[u]; i; i = e[i].next)
        if (e[i].w > eps && dep[e[i].to] == dep[u] + 1 && (tmp = DFS(e[i].to, min(f, e[i].w), t)) > eps) {
            res += tmp, f -= tmp, e[i].w -= tmp, e[i ^ 1].w += tmp;
            if (f < eps) break;
        }
    return res;
}

double dinic(int s, int t) {
    double res = 0;
    while (BFS(s, t)) memcpy(cur, head, sizeof(head)), res += DFS(s, 1e9, t);
    return res;
}

int G[55][55], id[55][55], n, s, t, ncnt;

void init() {
    ncnt = n;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) id[i][j] = ++ncnt;
    s = ++ncnt, t = ++ncnt; 
}

bool solve(double x) {
    memset(head, 0, sizeof(head)), ecnt = 1;
    for (int i = 1; i <= n; i++) adde(s, i, 199 * x);
    double all = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) 
            adde(i, id[i][j], 1e9), adde(j, id[i][j], 1e9), adde(id[i][j], t, G[i][j] + 2 * x), all += G[i][j] + 2 * x;
    double res = dinic(s, t);
    return res < all - eps;
}

struct RabbitWorking {
    double getMaximum(vector<string> profit) {
        n = profit.size();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) G[i][j] = profit[i - 1][j - 1] - '0';
        init();
        double l = 0, r = 1.5, res = 0;
        for (int i = 1; i <= 60; i++) {
            double mid = (l + r) / 2;
            if (solve(mid)) res = mid, l = mid;
            else r = mid;
        }
        return res;
    }
};

// int main() {
//     RabbitWorking solver;
//     cout << solver.getMaximum({ "06390061", 
//   "60960062", 
//   "39090270", 
//   "96900262", 
//   "00000212", 
//   "00222026", 
//   "66761201", 
//   "12022610" });
// }