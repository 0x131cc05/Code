#include <bits/stdc++.h>
using namespace std;

const int N = 5010;

struct edge {
    int to, next; double w;
} e[N * 10];

int head[N], ecnt = 1;

inline void adde(int from, int to, double w) {
    e[++ecnt] = (edge){ to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], 0 }, head[to] = ecnt;
}

int dep[N];

inline bool BFS(int s, int t) {
    memset(dep, -1, sizeof(dep)), dep[s] = 0; queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].next)
            if (e[i].w > 1e-4 && dep[e[i].to] == -1) {
                dep[e[i].to] = dep[u] + 1, q.push(e[i].to);
                if (e[i].to == t) return true;
            }
    }
    return false;
}

double DFS(int u, double f, int t) {
    if (u == t || !f) return f;
    double res = 0, tmp;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].w > 1e-4 && dep[e[i].to] == dep[u] + 1 && (tmp = DFS(e[i].to, min(f, e[i].w), t)) > 1e-4) {
            res += tmp, e[i].w -= tmp, e[i ^ 1].w += tmp, f -= tmp;
            if (f < 1e-4) break;
        }
    return res;
}

inline double dinic(int s, int t) {
    double res = 0;
    while (BFS(s, t)) res += DFS(s, 1e9, t);
//    cout << "dinic: " << res << endl;
    return res;
}

int a[N], l[N], r[N], n, m, v[N], tmp[N], s, t;

inline bool check(double mid) {
    vector<double> pos;
    for (int i = 1; i <= n; i++) 
        pos.push_back(l[i]), pos.push_back(r[i] + mid);
    memset(head, 0, sizeof(head)), ecnt = 1, s = n + 1, t = n + 2; int ncnt = n + 2; double all = 0;
    for (int i = 1; i <= n; i++) adde(s, i, a[i]), all += a[i];
    sort(pos.begin(), pos.end()), pos.resize(unique(pos.begin(), pos.end()) - pos.begin());
    for (int i = 0; i + 1 < pos.size(); i++) {
        double L = pos[i], R = pos[i + 1]; vector<int> p;
        for (int j = 1; j <= n; j++) 
            if (l[j] <= L + 1e-4 && r[j] + mid >= R - 1e-4) p.push_back(j); 
        for (int j = 1; j <= m; j++) 
            tmp[j] = ++ncnt, adde(ncnt, t, (m - j + 1) * (R - L) * (v[j] - v[j - 1]));
        for (auto t : p) 
            for (int j = 1; j <= m; j++) 
                adde(t, tmp[j], (R - L) * (v[j] - v[j - 1]));
    }
    return dinic(s, t) >= all - 1e-4;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d%d%d", &a[i], &l[i], &r[i]);
        for (int i = 1; i <= m; i++) scanf("%d", &v[i]);
        sort(v + 1, v + m + 1);
//        cout << "fuck: " << check(0.5) << endl;
        double L = 0, R = 1e5, mid, res = -1;
        for (int i = 1; i <= 50; i++) {
            mid = (L + R) / 2;
            if (check(mid)) res = mid, R = mid;
            else L = mid;
        }
        printf("%.3lf\n", res);
    }
}
