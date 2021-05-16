#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const int M = N * N * 2;
const double eps = 1e-10;

struct edge {
    int to, next; double w;
} e[M], e2[M];

int head[N], cur[N], ecnt;

void adde(int from, int to, double w) {
    e[++ecnt] = { to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = { from, head[to], w }, head[to] = ecnt;
}

void adde1(int from, int to, double w) {
    e[++ecnt] = { to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = { from, head[to], 0 }, head[to] = ecnt;
}

int dep[N];

bool BFS(int s, int t) {
    memset(dep, -1, sizeof(dep)), dep[s] = 0; queue<int> q; q.push(s);
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
    if (u == t || f < eps) return f;
    double res = 0, tmp;
    for (int &i = cur[u]; i; i = e[i].next)
        if (e[i].w && dep[e[i].to] == dep[u] + 1 && (tmp = DFS(e[i].to, min(f, e[i].w), t)) > eps) {
            res += tmp, e[i].w -= tmp, e[i ^ 1].w += tmp, f -= tmp;
            if (f < eps) break;
        }
    return res;
}

double dinic(int s, int t) {
    double res = 0;
    while (BFS(s, t)) memcpy(cur, head, sizeof(head)), res += DFS(s, 1e9, t);
    return res;
}

int from[M], to[M], w[M], rev[M];

int main() {
    int n, m; double v, a; scanf("%d%d%lf%lf", &n, &m, &v, &a);
    for (int i = 1; i <= m; i++) 
        scanf("%d%d%d", &from[i], &to[i], &w[i]);
    auto reset = [&]() {
        ecnt = 1, memset(head, 0, sizeof(head));
        for (int i = 1; i <= m; i++) adde(from[i], to[i], w[i]); 
    };
    reset(); double F = dinic(1, 3);
    reset(); double W = dinic(2, 3);
    reset(), adde1(n + 1, 1, 1e9), adde1(n + 1, 2, 1e9); double A = dinic(n + 1, 3);
    double F1 = A * a; F1 = min(F1, F), F1 = max(F1, A - W);
    reset(), adde1(n + 1, 1, F1), adde1(n + 1, 2, A - F1), dinic(n + 1, 3);
    memcpy(e2, e, sizeof(e)), ecnt = 1, memset(head, 0, sizeof(head));
    for (int i = 1; i <= m; i++) {
        if (e2[i * 2].w > w[i]) adde1(to[i], from[i], e[i * 2].w - w[i]), rev[i] = 1;
        else adde1(from[i], to[i], w[i] - e2[i * 2].w);
    } 
    adde1(n + 1, 1, F1), dinic(n + 1, 3);
    for (int i = 1; i <= m; i++) {
        double t1 = e[i * 2 + 1].w / v, t2 = e[i * 2].w;
        if (rev[i]) t1 = -t1, t2 = -t2;
        printf("%.10lf %.10lf\n", t1 + eps, t2 + eps);
    }
    printf("%.10lf\n", pow(F1, a) * pow(A - F1, 1 - a) / pow(v, a));
}