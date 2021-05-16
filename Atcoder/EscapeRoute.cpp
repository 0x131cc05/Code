#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> P;

const int N = 110;
const int M = N * N;

struct edge {
    int to, next; LL t, c;
} e[M * 2];

int head[N], ecnt;

void adde(int from, int to, LL t, LL c) {
    e[++ecnt] = (edge){ to, head[from], t, c }, head[from] = ecnt;
    e[++ecnt] = (edge){ from, head[to], t, c }, head[to] = ecnt;
}

LL dis[N], S; int vis[N];

void Dijkstra1(LL t, int s) {
    memset(dis, 0x3f, sizeof(dis)), memset(vis, 0, sizeof(vis)), dis[s] = 0;
    priority_queue<P> q; q.push(P(0, s));
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue; vis[u] = 1;
        for (int i = head[u]; i; i = e[i].next)
            if (dis[u] + e[i].t + t <= e[i].c && dis[u] + e[i].t < dis[e[i].to]) 
                dis[e[i].to] = dis[u] + e[i].t, q.push(P(-dis[e[i].to], e[i].to));
    }
}

LL dis2[N];

void Dijkstra2(LL t, int s) {
    memset(dis2, 0x3f, sizeof(dis2)), memset(vis, 0, sizeof(vis)), dis2[s] = 0;
    priority_queue<P> q; q.push(P(0, s));
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue; vis[u] = 1;
        for (int i = head[u]; i; i = e[i].next) 
            if (t - dis2[u] <= e[i].c && dis2[u] + e[i].t < dis2[e[i].to]) 
                dis2[e[i].to] = dis2[u] + e[i].t, q.push(P(-dis2[e[i].to], e[i].to));
    }
}

P Depart(LL t1, LL t2, int u, int v) { // u -> t2 -> t1 -> v
    if (dis[v] + t1 >= S || t2 - dis2[u] < 0) return P(-1, -1);
    return P(t2 - dis2[u], dis2[u] + dis[v] + t1 - t2);
} // (max start time, min cost)

vector<P> fuck[N][N];

int G[N][N]; 
LL terminal[N][N], depart[N][N], wkr[N][N];

void Floyd(int n) {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
}

vector<LL> calculate_necessary_time(int n, int m, LL S, int q, vector<int> A, vector<int> B, 
    vector<LL> L, vector<LL> C, vector<int> U, vector<int> V, vector<LL> T) {
    auto init = [](vector<int> &v) { for (auto &t : v) t++; };
    init(A), init(B), init(U), init(V), ::S = S;
    for (int i = 0; i < m; i++) adde(A[i], B[i], L[i], C[i]);
    memset(depart, -1, sizeof(depart));
    auto process = [&](int u, int v, LL t1, LL t2) {
        if (t2 < 0) return;
        Dijkstra1(t1, v), Dijkstra2(t2, u);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) if (i != j) {
                P res = Depart(t1, t2, i, j);
                depart[i][j] = max(depart[i][j], res.first);
                if (res.first >= 0) fuck[i][j].push_back(res);
            }
    };
    for (int i = 1; i <= n; i++) depart[i][i] = 1e18;
    for (int i = 0; i < m; i++) {
        process(A[i], B[i], C[i], C[i] - L[i]);
        process(B[i], A[i], C[i], C[i] - L[i]); 
    }
    memset(terminal, 0x3f, sizeof(terminal));
    for (int i = 1; i <= n; i++) {
        Dijkstra1(0, i);
        for (int j = 1; j <= n; j++) terminal[i][j] = dis[j], G[i][j] = dis[j] < S ? 1 : 1e8;
    }
    for (int i = 1; i <= n; i++) G[i][i] = 0;
    Floyd(n), memset(wkr, 0x3f, sizeof(wkr));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) if (G[i][j] < 1e7)
            for (int k = 1; k <= n; k++) if (terminal[j][k] < 1e17)
                wkr[i][k] = min(wkr[i][k], G[i][j] * S + terminal[j][k]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) if (i != j) {
            sort(fuck[i][j].begin(), fuck[i][j].end());
            vector<P> tmp;
            for (auto t : fuck[i][j]) 
                if (!tmp.size() || t.first != tmp.back().first) {
                    while (tmp.size() && tmp.back().second >= t.second) tmp.pop_back();
                    tmp.push_back(t);
                }
            fuck[i][j] = tmp;
        }
    vector<LL> res;
    for (int i = 0; i < q; i++) {
        int u = U[i], v = V[i]; LL s = T[i], ans = 1e18;
        auto pos = lower_bound(fuck[u][v].begin(), fuck[u][v].end(), P(s, 0));
//        for (auto t : fuck[u][v]) cout << t.first << ", " << t.second << ' ';
//        cout << endl;
        if (pos != fuck[u][v].end()) {
//            cout << "fuck: " << pos->second << endl;
            res.push_back(pos->second); continue;
        }
        for (int j = 1; j <= n; j++) if (s <= depart[u][j]) 
            ans = min(ans, S + wkr[j][v] - s);
        res.push_back(ans);
    }
    return res;
}

int main() {
    int n, m, q; LL s; scanf("%d%d%lld%d", &n, &m, &s, &q);
    vector<int> A, B, U, V; vector<LL> L, C, T;
    for (int i = 1; i <= m; i++) {
        int a, b; LL l, c; scanf("%d%d%lld%lld", &a, &b, &l, &c);
        A.push_back(a), B.push_back(b), L.push_back(l), C.push_back(c);
    }
    for (int i = 1; i <= q; i++) {
        int u, v; LL t; scanf("%d%d%lld", &u, &v, &t);
        U.push_back(u), V.push_back(v), T.push_back(t);
    }
    auto res = calculate_necessary_time(n, m, s, q, A, B, L, C, U, V, T);
    for (auto t : res) printf("%lld\n", t);
}
