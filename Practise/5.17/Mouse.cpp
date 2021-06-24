#include <bits/stdc++.h>
using namespace std;

const int N = 110;

struct point {
    double x, y;
    point(double x = 0, double y = 0): x(x), y(y) {}
    double operator * (point b) { return x * b.x + y * b.y; }
    point operator * (double d) { return point(x * d, y * d); }
    point operator + (point b) { return point(x + b.x, y + b.y); }
    point operator - (point b) { return point(x - b.x, y - b.y); }
};

double dist(point x) { return sqrt(x * x); }

vector<point> vec[N]; 

point closest(point p, point a, point b) {
    double t = (b - a) * (p - a) / dist(b - a);
    if (t < 0 || t > 1) {
        double A = dist(p - a), B = dist(p - b);
        return A < B ? a : b;
    } 
    return a + (b - a) * t;
}

point closest(point p, int id) {
    double dis = 1e18; point tar;
    for (int i = 0; i + 1 < vec[id].size(); i++) {
        point t = closest(p, vec[id][i], vec[id][i + 1]);
        double d = dist(t - p);
        if (d < dis) dis = d, tar = t;
    }
    return tar;
}

pair<point, point> closest1(int a, int b) {
    double dis = 1e18; point A, B;
    for (int i = 0; i + 1 < vec[a].size(); i++) {
        point t = closest(vec[a][i], b);
        double d = dist(vec[a][i] - t);
        if (d < dis) dis = d, A = vec[a][i], B = t;
    }
    return make_pair(A, B);
}

pair<point, point> closest(int a, int b) {
    auto A = closest1(a, b), B = closest1(b, a);
    if (dist(A.first - A.second) < dist(B.first - B.second)) return A;
    else return make_pair(B.second, B.first);
}

struct edge {
    int to, next; double w;
} e[N * N * 2];

int head[N], ecnt;

void adde(int from, int to, double w) {
    e[++ecnt] = { to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = { from, head[to], w }, head[to] = ecnt;
}

double dis[N]; int lst[N], vis[N], ncnt;

void Dijkstra(int s) {
    for (int i = 1; i <= ncnt; i++) dis[i] = 1e18;
    dis[s] = 0;
    priority_queue<pair<double, int>> q; 
    q.push(make_pair(0, s));
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue; vis[u] = 1;
        for (int i = head[u]; i; i = e[i].next)
            if (!vis[e[i].to] && dis[e[i].to] > dis[u] + e[i].w) {
                lst[e[i].to] = u, dis[e[i].to] = dis[u] + e[i].w;
                q.push(make_pair(-dis[e[i].to], e[i].to));
            }
    } 
}

pair<point, point> ed[N][N];

int main() {
    point ps, pt; scanf("%lf%lf%lf%lf", &ps.x, &ps.y, &pt.x, &pt.y);
    int n; scanf("%d", &n);
    ncnt = n + 2; int s = n + 1, t = s + 1;
    adde(s, t, dist(ps - pt));
    for (int i = 1; i <= n; i++) {
        int k; scanf("%d", &k);
        for (int j = 1; j <= k; j++) {
            point p; scanf("%lf%lf", &p.x, &p.y);
            vec[i].push_back(p);
        }
        for (int j = 1; j < k; j++) {
            if (vec[i][j].y < vec[i][0].y) 
                swap(vec[i][j], vec[i][0]);
        }
        point p = vec[i][0];
        sort(vec[i].begin() + 1, vec[i].end(), [&](point a, point b) {
            double ang1 = atan2(a.y - p.y, a.x - p.x);
            double ang2 = atan2(b.y - p.y, b.x - p.x);
            return ang1 < ang2;
        });
        vec[i].push_back(p);
    } 
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            auto t = closest(i, j);
            ed[i][j] = t, ed[j][i] = make_pair(t.second, t.first);
            adde(i, j, dist(t.first - t.second) - 20);
        }
    for (int i = 1; i <= n; i++) {
        point tp = closest(ps, i);
        ed[s][i] = make_pair(ps, tp), ed[i][s] = make_pair(tp, ps);
        adde(s, i, max(0., dist(tp - ps) - 10));
        tp = closest(pt, i); 
        ed[t][i] = make_pair(pt, tp), ed[i][t] = make_pair(tp, pt);
        adde(i, t, max(0., dist(pt - tp) - 10));
    }        
    Dijkstra(s);
    vector<int> path; vector<point> res;
    int cur = t;
    while (cur) path.push_back(cur), cur = lst[cur];
    reverse(path.begin(), path.end());
    for (int i = 0; i + 1 < path.size(); i++) {
        int u = path[i], v = path[i + 1];
        if (u <= n && v <= n) {
            point delta = ed[u][v].second - ed[u][v].first;
            double t = 10 / dist(delta);
            res.push_back(ed[u][v].first + delta * t), res.push_back(ed[u][v].second - delta * t);
        } else if (u > n && v > n) {
            res.push_back(u), res.push_back(v);
        } else {
            point delta = ed[u][v].second - ed[u][v].first;
            double t = 10 / dist(delta);
            if (u > n) {
                res.push_back(ed[u][v].first);
                if (t < 1) res.push_back(ed[u][v].second - delta * t);
                else res.push_back(ed[u][v].second);
            } else {
                if (t < 1) res.push_back(ed[u][v].first + delta * t);
                else res.push_back(ed[u][v].first);
                res.push_back(ed[u][v].second);
            }
        }
    }
    vector<point> fuck;
    for (auto t : res) 
        if (!fuck.size() || dist(fuck.back() - t) > 1e-3) fuck.push_back(t);
    printf("%d\n", fuck.size());
    for (auto t : fuck) printf("%.7lf %.7lf\n", t.x, t.y);
}
