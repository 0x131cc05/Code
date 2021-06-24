#include <bits/stdc++.h>
using namespace std;

const int N = 2010;
const int mod = 1e9 + 9;
const int inv2 = (mod + 1) / 2;

typedef pair<int, int> P;
typedef long long LL;

struct edge {
    int to, next, w;
} e[N * 30];

int head[N], ecnt;

void adde(int from, int to, int w) {
    e[++ecnt] = { to, head[from], w }, head[from] = ecnt;
    e[++ecnt] = { from, head[to], w }, head[to] = ecnt;
}

int dis[N], vis[N], n;

void Dijkstra(int s) {
    memset(dis, 0x3f, sizeof(dis)), dis[s] = 0;
    priority_queue<P> q; q.push(P(0, s));
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].next)
            if (dis[e[i].to] > dis[u] + e[i].w) 
                dis[e[i].to] = dis[u] + e[i].w, q.push(P(-dis[e[i].to], e[i].to));
    }
}

vector<int> G[N], p;

int fuck[N][N];

void build() {
    for (int i = 1; i <= n; i++)
        for (int j = head[i]; j; j = e[j].next)
            if (dis[e[j].to] == dis[i] + e[j].w) {
                if (fuck[i][e[j].to]) continue;
                fuck[i][e[j].to] = 1;
                G[i].push_back(e[j].to);
                // cout << i << " push_back " << e[j].to << endl;
            }
                
    for (int i = 1; i <= n; i++) p.push_back(i);
    sort(p.begin(), p.end(), [&](int a, int b) {
        return dis[a] > dis[b];
    });
}

void get(vector<int> &dp, int to) {
    dp = vector<int>(n + 1), dp[to] = 1;
    for (auto t : p) 
        for (auto v : G[t]) dp[t] = (dp[t] + dp[v]) % mod;
}

vector<int> g[N], f;

int work(int s, int t) {
    f.resize(n + 1), f[s] = mod - 1;
    // for (auto t : p) cout << t << ' ';
    // cout << endl;
    reverse(p.begin(), p.end());
    for (int i = 0; i < p.size(); i++)
        for (int j = i + 1; j < p.size(); j++) {
            int w = g[p[j]][p[i]]; w = (LL)w * w % mod;
            f[p[j]] = (f[p[j]] + (LL)f[p[i]] * (mod - w)) % mod;
        }
    int res = f[t];
    for (auto v : G[s]) if (v == t) {
        res++; break;
    }
    return (LL)res * inv2 % mod;
}

template<class T> void read(T &x) {
    x = 0; char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
}

template<class T, typename... Tail> void read(T &x, Tail&... tail) {
    read(x), read(tail...);
}

int main() {
    int m, s, t; read(n, m, s, t);
    for (int i = 1, a, b, c; i <= m; i++) 
        read(a, b, c), adde(a, b, c);
    Dijkstra(s), build();
    for (int i = 1; i <= n; i++) get(g[i], i);
    // cout << g[2][1] << endl;
    printf("%d\n", work(s, t));
    return 0;
}